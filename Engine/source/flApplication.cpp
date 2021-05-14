#include "platform/flEventQueue.h"
#include "flApplication.h"
#include "flEngine.h"
#include "flInit.h"
#include <functional>

typedef  void (*EventFunc)(flEngine::Platform::Event*, void*);

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

      m_pSystemEvents = flNew Platform::EventQueue;
      m_pSystemEvents->SetEventCallback([](Platform::Event *pEvent, void *pUserData) {
        ((Impl_Application*)pUserData)->HandleEvent(pEvent);
      }, this);
    }

    void HandleEvent(Platform::Event* pEvent)
    {
      if (m_pApp->OnEvent(pEvent))
      {
        // TODO: Forward the event
      }
    }

    Platform::EventQueue* m_pSystemEvents = nullptr;
    Application* m_pApp = nullptr;
  };

  flPIMPL_IMPL(Application);

  bool Application::OnStartup()  { return true; }
  bool Application::OnShutdown() { return false; }

  void Application::OnPreUpdate() {}
  void Application::OnPreRender() {}

  void Application::OnPostUpdate() {}
  void Application::OnPostRender() {}
  
  bool Application::OnEvent(flIN Platform::Event* pEvent) { ctUnused(pEvent); return true; }

  Application& Application::Get() { return *_pApplication; }

  Application::Application()
  {
    Impl()->m_pApp = this;
  }

  int Application::Run()
  {
    while (IsRunning())
    {
      OnPreUpdate();
      OnPostUpdate();

      OnPreRender();
      OnPostRender();
    }

    return 0;
  }
}