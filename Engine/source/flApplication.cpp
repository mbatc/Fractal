#include "platform/flEventQueue.h"
#include "input/flInputs.h"
#include "flApplication.h"
#include "flInit.h"
#include "flRef.h"
#include <functional>
#include "ctVector.h"
#include "ctString.h"
#include "ctKeyValue.h"

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
    flPIMPL_CLASS(Application)::flPIMPL_CLASS(Application)()
    {
      // Initialize Fractal
      flEngine::Initialize();

      m_pSystemEvents = flNew EventQueue;
      m_pSystemEvents->SetEventCallback([](Event *pEvent, void *pUserData) {
        ((Impl_Application*)pUserData)->HandleEvent(pEvent);
      }, this);
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
          return false;
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

    Application* m_pApp = nullptr;
    EventQueue* m_pSystemEvents = nullptr;
    bool m_isRunning = true;
    ctVector<ctKeyValue<ctString, Ref<SubSystem>>> m_subSystems;
  };

  flPIMPL_IMPL(Application);

  void Application::Close()
  {
    Impl()->m_isRunning = false;
  }
  
  Application& Application::Get() { return *_pApplication; }

  Application::Application()
  {
    _pApplication = this;

    Impl()->m_pApp = this;
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
    }

    Impl()->Shutdown();
    return 0;
  }
}