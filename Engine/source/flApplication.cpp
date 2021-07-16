#include "flApplication.h"
#include "flIWindow.h"
#include "flITask.h"
#include "flAPI.h"

#include "flEventQueue.h"
#include "flThreads.h"
#include "flInputs.h"
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
  namespace Impl
  {
    // The main application instance
    typedef void (*EventFunc)(Event*, void*);

    static Application* _pApplication = nullptr;

    Application::Application(char const* graphicsAPIName)
    {
    }

    void Application::HandleEvent(Event* pEvent)
    {
      if (_pApplication->Dispatch(pEvent))
        for (int64_t i = m_subSystems.size() - 1; i >= 0; --i)
          if (!m_subSystems[i].m_val->Dispatch(pEvent))
            break;
    }

    template<typename ReturnT, typename... Args>
    bool Application::InvokeBehaviour(ReturnT(IApplicationBehaviour::* func)(Args...), Args&& ... args)
    {
      (m_pApp->*func)(args...);
      for (int64_t i = 0; i < m_subSystems.size(); ++i)
        (m_subSystems[i].m_val->*func)(args...);
      return true;
    }

    bool Application::Startup()
    {
      if (!OnStartup())
        return false;
      for (int64_t i = 0; i < m_subSystems.size(); ++i)
        if (!m_subSystems[i].m_val->OnStartup())
          return false;
      return true;
    }

    void Application::Shutdown()
    {
      InvokeBehaviour(&IApplicationBehaviour::OnShutdown);
    }

    void Application::PreUpdate()
    {
      InvokeBehaviour(&IApplicationBehaviour::OnPreUpdate);
    }

    void Application::Update()
    {
      InvokeBehaviour(&IApplicationBehaviour::OnUpdate);
    }

    void Application::PostUpdate()
    {
      InvokeBehaviour(&IApplicationBehaviour::OnPostUpdate);
    }

    void Application::PreRender()
    {
      InvokeBehaviour(&IApplicationBehaviour::OnPreRender);
    }

    void Application::Render()
    {
      Fractal_GetMainWindow()->GetRenderTarget()->Bind();
      Fractal_GetMainWindow()->GetRenderTarget()->Clear();
      InvokeBehaviour(&IApplicationBehaviour::OnRender);
    }

    void Application::PostRender()
    {
      InvokeBehaviour(&IApplicationBehaviour::OnPostRender);
    }

    void Application::BeginFrame()
    {
      m_frameStartTime = HighResClock();
    }

    void Application::EndFrame()
    {
      uint64_t frameDuration = HighResClock() - m_frameStartTime;
      int64_t millis = frameDuration / 1000000ull;
      if (millis < 16)
        Sleep(millis - 16);
    }

    void Application::ProcessQueuedTasks()
    {
      uint64_t allocatedTime = 1000000; // 1 ms
      uint64_t start = HighResClock();
      while (HighResClock() - start < allocatedTime && m_pTaskQueue->HasNext())
        m_pTaskQueue->RunNext();
    }

    void Application::Close()
    {
      m_isRunning = false;
    }

    ITask* Application::EnqueueTask(flIN ITask* pTask)
    {
      if (Fractal_GetThreadID() == MainThreadID())
        pTask->DoTask();
      else
        _pApplication->m_pTaskQueue->Add(pTask);

      return pTask;
    }

    int64_t Application::Await(flIN ITask* pTask)
    {
      return EnqueueTask(pTask)->Await();
    }

    int64_t Application::MainThreadID()
    {
      return _pApplication->m_mainThreadID;
    }

    Application::Application(char const* graphicsAPIName)
    {
      // Set the global application ptr
      _pApplication = this;

      // Initialize Fractal
      Initialize();

      flInfo("Initialising Application");
      m_pTaskQueue = MakeRef(Fractal_CreateTaskQueue(), false);
      m_mainThreadID = Fractal_GetThreadID();

      flInfo("Initialising Event System");
      m_pSystemEvents = MakeRef<IEventQueue>();
      m_pSystemEvents->SetEventCallback([](Event* pEvent, void* pUserData)
        {
          ((Application*)pUserData)->HandleEvent(pEvent);
        }, this);

      flInfo("Creating main window");
      // Create the applications main window and graphics API
      m_pMainWindow = MakeRef(Fractal_CreateWindow("Main Window", WindowFlag_Default, WindowDisplayMode_Windowed), false);

      flInfo("Creating Graphics API (%s)", graphicsAPIName);
      RenderTargetOptions opts;
      opts.sampleCount = 4; // Enable multisampling
      m_pGraphics = MakeRef(Fractal_CreateAPI(graphicsAPIName, m_pMainWindow.Get(), &opts), false);

      char cwd[1024] = { 0 };
      GetCurrentDirectoryA(1024, cwd);
      flInfo("CWD '%s", cwd);
    }

    void Application::AddModule(Module* pSystem, char const* name)
    {
      if (GetModule(name) == nullptr)
        m_subSystems.emplace_back(name, MakeRef(pSystem, true));

    }

    Module* Application::GetModule(char const* name)
    {
      for (auto& kvp : m_subSystems)
        if (kvp.m_key.compare(name))
          return kvp.m_val;
      return nullptr;
    }

    int Application::Run()
    {
      if (!Startup())
      {
        Shutdown();
        return 1; // Startup failed
      }

      while (m_isRunning)
      {
        BeginFrame();

        Inputs::Update(); // Push input events

        PreUpdate();
        Update();
        PostUpdate();

        Fractal_GetMainWindow()->GetRenderTarget()->Clear();

        PreRender();
        Render();
        PostRender();

        ProcessQueuedTasks();

        Fractal_GetMainWindow()->GetRenderTarget()->Swap();

        EndFrame();
      }

      Shutdown();
      return 0;
    }

    API* Application::GetGraphicsAPI() const
    {
      return m_pGraphics;
    }

    IWindow* Application::GetMainWindow() const
    {
      return m_pMainWindow;
    }
  }
}

extern "C" {
  /**
   * @brief Returns a pointer to the applications main window.
   */
  flEXPORT Fractal::IWindow* Fractal_GetMainWindow()
  {
    return Fractal::Impl::_pApplication->GetMainWindow();
  }

  /**
   * @brief Returns a pointer to the applications graphics API.
   */
  flEXPORT Fractal::API* Fractal_GetGraphicsAPI()
  {
    return Fractal::Impl::_pApplication->GetGraphicsAPI();
  }

  /**
   * @brief Get the global Application instance.
   **/
  flEXPORT Fractal::IApplication* Fractal_GetApplication()
  {
    return Fractal::Impl::_pApplication;
  }
}
