#include "flApplication.h"
#include "flEngine.h"
#include "flInit.h"

namespace flEngine
{
  Application* Application::m_pApplication = nullptr;

  class flPIMPL_CLASS(Application)
  {
  public:
    flPIMPL_CLASS(Application)::flPIMPL_CLASS(Application)()
    {
      flEngine::Initialize();
    }
  };

  flPIMPL_IMPL(Application);

  bool Application::OnStartup()  { return true; }
  bool Application::OnShutdown() { return false; }

  void Application::OnPreUpdate() {}
  void Application::OnPreRender() {}

  void Application::OnPostUpdate() {}
  void Application::OnPostRender() {}
  
  Application& Application::Get() { return *m_pApplication; }

  Application::Application()
  {
    // TODO: Assert only 1 application created
    m_pApplication = this;
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