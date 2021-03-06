#include "flEventQueue.h"
#include "flWindow.h"
#include "flThreads.h"
#include "flAPI.h"
#include "flInputs.h"
#include "flApplication.h"
#include "flInit.h"
#include "flRef.h"
#include "flWindowRenderTarget.h"
#include "flLog.h"
#include "flTime.h"

#include "ctVector.h"
#include "ctString.h"
#include "ctKeyValue.h"
#include "ctTimespan.h"

#include <windows.h>
#include <functional>

namespace Fractal
{
// The main application instance
  typedef void (*EventFunc)(Event*, void*);

  static Application* _pApplication = nullptr;

  class Impl_Application
  {
  public:
    void Construct(Application* pApp, char const* graphicsAPIName)
    {
      // Initialize Fractal
      Initialize();

      flInfo("Initialising Application");
      m_pApp = pApp;
      m_taskQueue = MakeRef<TaskQueue>();
      m_mainThreadID = GetThreadID();

      flInfo("Initialising Event System");
      m_pSystemEvents = MakeRef<EventQueue>();
      m_pSystemEvents->SetEventCallback([](Event * pEvent, void* pUserData)
      {
        ((Impl_Application*)pUserData)->HandleEvent(pEvent);
      }, this);

      flInfo("Creating main window");
      // Create the applications main window and graphics API
      m_pMainWindow = MakeRef<Window>("Main Window", Window::Flag_Default, Window::DM_Windowed);

      flInfo("Creating Graphics API (%s)", graphicsAPIName);
      RenderTargetOptions opts;
      opts.sampleCount = 4; // Enable multisampling
      m_pGraphics = MakeRef(API::Create(graphicsAPIName, m_pMainWindow.Get(), &opts), false);

      char cwd[1024] = {0};
      GetCurrentDirectoryA(1024, cwd);
      flInfo("CWD '%s", cwd);
    }

    void HandleEvent(Event* pEvent)
    {
      if (m_pApp->Dispatch(pEvent))
        for (int64_t i = m_subSystems.size() - 1; i >= 0; --i)
          if (!m_subSystems[i].m_val->Dispatch(pEvent))
            break;
    }

    template<typename ReturnT, typename... Args>
    bool InvokeBehaviour(ReturnT(ApplicationBehaviour:: *func)(Args...), Args&& ... args)
    {
      (m_pApp->*func)(args...);
      for (int64_t i = 0; i < m_subSystems.size(); ++i)
        (m_subSystems[i].m_val->*func)(args...);
      return true;
    }

    bool Startup()
    {
      if (!m_pApp->OnStartup())
        return false;
      for (int64_t i = 0; i < m_subSystems.size(); ++i)
        if (!m_subSystems[i].m_val->OnStartup())
          return false;
      return true;
    }

    void Shutdown()
    {
      InvokeBehaviour(&ApplicationBehaviour::OnShutdown);
    }

    void PreUpdate()
    {
      InvokeBehaviour(&ApplicationBehaviour::OnPreUpdate);
    }

    void Update()
    {
      InvokeBehaviour(&ApplicationBehaviour::OnUpdate);
    }

    void PostUpdate()
    {
      InvokeBehaviour(&ApplicationBehaviour::OnPostUpdate);
    }

    void PreRender()
    {
      InvokeBehaviour(&ApplicationBehaviour::OnPreRender);
    }

    void Render()
    {
      GetMainWindow()->GetRenderTarget()->Bind();
      GetMainWindow()->GetRenderTarget()->Clear();
      InvokeBehaviour(&ApplicationBehaviour::OnRender);
    }

    void PostRender()
    {
      InvokeBehaviour(&ApplicationBehaviour::OnPostRender);
    }

    void BeginFrame()
    {
      m_frameStartTime = HighResClock();
    }

    void EndFrame()
    {
      uint64_t frameDuration = HighResClock() - m_frameStartTime;
      int64_t millis = frameDuration / 1000000ull;
      if (millis < 16)
        Sleep(millis - 16);
    }

    void ProcessQueuedTasks()
    {
      uint64_t allocatedTime = 1000000; // 1 ms
      uint64_t start = HighResClock();
      while (HighResClock() - start < allocatedTime && m_taskQueue->HasNext())
        m_taskQueue->RunNext();
    }

    // Application state
    Application* m_pApp      = nullptr;
    bool         m_isRunning = true;

    // Core components of an application
    Ref<API>        m_pGraphics     = nullptr;
    Ref<Window>     m_pMainWindow   = nullptr;
    Ref<EventQueue> m_pSystemEvents = nullptr;

    int64_t m_mainThreadID = 0;
    Ref<TaskQueue> m_taskQueue; // The applications task queue. These are executed on the main thread

    // Custom application sub systems
    ctVector<ctKeyValue<ctString, Ref<Module>>> m_subSystems;

    uint64_t m_frameStartTime;
  };

  flPIMPL_IMPL(Application);

  void Application::Close()
  {
    Impl()->m_isRunning = false;
  }

  Task* Application::EnqueueTask(flIN Task* pTask)
  {
    Application *pApp = GetApplication();
    if (GetThreadID() == MainThreadID())
      pTask->DoTask();
    else
      pApp->Impl()->m_taskQueue->Add(pTask);

    return pTask;
  }

  int64_t Application::Await(flIN Task* pTask)
  {
    return EnqueueTask(pTask)->Await();
  }

  int64_t Application::MainThreadID()
  {
    return GetApplication()->Impl()->m_mainThreadID;
  }

  Application::Application(char const* graphicsAPIName)
  {
    // Set the global application ptr
    _pApplication = this;

    // Construct the application implementation
    Impl()->Construct(this, graphicsAPIName);
  }

  void Application::AddModule(Module* pSystem, char const* name)
  {
    if (GetModule(name) == nullptr)
      Impl()->m_subSystems.emplace_back(name, MakeRef(pSystem, true));
  }

  Module* Application::GetModule(char const* name)
  {
    for (auto& kvp : Impl()->m_subSystems)
      if (kvp.m_key.compare(name))
        return kvp.m_val;
    return nullptr;
  }

  int Application::Run()
  {
    if (!Impl()->Startup())
    {
      Impl()->Shutdown();
      return 1; // Startup failed
    }

    while (Impl()->m_isRunning)
    {
      Impl()->BeginFrame();

      Inputs::Update(); // Push input events

      Impl()->PreUpdate();
      Impl()->Update();
      Impl()->PostUpdate();

      GetMainWindow()->GetRenderTarget()->Clear();
      Impl()->PreRender();
      Impl()->Render();
      Impl()->PostRender();

      Impl()->ProcessQueuedTasks();

      GetMainWindow()->GetRenderTarget()->Swap();

      Impl()->EndFrame();
    }

    Impl()->Shutdown();
    return 0;
  }
  
  Window * GetMainWindow()
  {
    return GetApplication()->Impl()->m_pMainWindow;
  }

  API * GetGraphicsAPI()
  {
    return GetApplication()->Impl()->m_pGraphics;
  }

  Application * GetApplication()
  {
    return _pApplication;
  }
}