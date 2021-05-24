#include "platform/flEventQueue.h"
#include "platform/flWindow.h"
#include "threads/flThreads.h"
#include "graphics/flAPI.h"
#include "input/flInputs.h"
#include "flApplication.h"
#include "flInit.h"
#include "flRef.h"

#include "ctVector.h"
#include "ctString.h"
#include "ctKeyValue.h"

#include <functional>

typedef  void (*EventFunc)(flEngine::Platform::Event*, void*);

using namespace flEngine::Platform;

namespace flEngine
{
  // The main application instance
  static Application* _pApplication = nullptr;

  class Impl_Application;

  class flPIMPL_CLASS(Application)
  {
  public:
    void Construct(Application *pApp, char const * graphicsAPIName)
    {
      // Initialize Fractal
      flEngine::Initialize();

      m_pApp = pApp;

      m_pSystemEvents = MakeRef<EventQueue>();
      m_pSystemEvents->SetEventCallback([](Event *pEvent, void *pUserData) {
        ((Impl_Application *)pUserData)->HandleEvent(pEvent);
        }, this);

      // Create the applications main window and graphics API
      m_pMainWindow = MakeRef<Window>("Main Window", Window::Flag_Default, Window::DM_Windowed);
      m_pGraphics   = MakeRef(Graphics::API::Create(graphicsAPIName, m_pMainWindow.Get()), false);
    }

    void HandleEvent(Event* pEvent)
    {
      if (m_pApp->Dispatch(pEvent))
        for (int64_t i = m_subSystems.size() - 1; i >= 0; --i)
          if (!m_subSystems[i].m_val->Dispatch(pEvent))
            break;
    }

    template<typename ReturnT, typename... Args>
    bool InvokeBehaviour(ReturnT(ApplicationBehaviour:: *func)(Args...), Args&&... args)
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
      InvokeBehaviour(&ApplicationBehaviour::OnRender);
    }

    void PostRender()
    {
      InvokeBehaviour(&ApplicationBehaviour::OnPostRender);
    }

    // Application state
    Application* m_pApp      = nullptr;
    bool         m_isRunning = true;

    // Core components of an application
    Ref<Graphics::API> m_pGraphics     = nullptr;
    Ref<Window>        m_pMainWindow   = nullptr;
    Ref<EventQueue>    m_pSystemEvents = nullptr;

    // Custom application sub systems
    ctVector<ctKeyValue<ctString, Ref<SubSystem>>> m_subSystems;
  };

  flPIMPL_IMPL(Application);

  void Application::Close()
  {
    Impl()->m_isRunning = false;
  }

  Platform::Window *flEngine::Application::GetMainWindow()
  {
    return Impl()->m_pMainWindow.Get();
  }

  Platform::Window const * flEngine::Application::GetMainWindow() const
  {
      return Impl()->m_pMainWindow.Get();
  }

  Graphics::API *flEngine::Application::GetGraphicsAPI()
  {
    return Impl()->m_pGraphics.Get();
  }

  Graphics::API const *flEngine::Application::GetGraphicsAPI() const
  {
    return Impl()->m_pGraphics.Get();
  }
  
  Application& Application::Get() { return *_pApplication; }

  Application::Application(char const *graphicsAPIName)
  {
    // Set the global application ptr
    _pApplication = this;

    // Construct the application implementation
    Impl()->Construct(this, graphicsAPIName);
  }

  void Application::AddSubSystem(SubSystem *pSystem, char const *name)
  {
    if (GetSubSystem(name) == nullptr)
      Impl()->m_subSystems.emplace_back(name, MakeRef(pSystem, true));
  }

  SubSystem* Application::GetSubSystem(char const *name)
  {
    for (auto &kvp : Impl()->m_subSystems)
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
      Inputs::Update(); // Push input events

      Impl()->PreUpdate();
      Impl()->Update();
      Impl()->PostUpdate();

      Impl()->PreRender();
      Impl()->Render();
      Impl()->PostRender();

      Threads::Sleep(1);
    }

    Impl()->Shutdown();
    return 0;
  }
}