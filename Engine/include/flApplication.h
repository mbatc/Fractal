#ifndef fl_Application_h__
#define fl_Application_h__

#include "flInterface.h"

namespace flEngine
{
  class flPIMPL_CLASS(Application);

  class flEXPORT Application : public Interface
  {
    flPIMPL_DEF(Application);

    friend class FractalEntryHandler;

  public:
    virtual bool OnStartup();
    virtual bool OnShutdown();

    virtual void OnPreUpdate();
    virtual void OnPreRender();

    virtual void OnPostUpdate();
    virtual void OnPostRender();

    virtual bool IsRunning() = 0;

    static Application& Get();

  protected:
    Application();

  private:
    int Run();

    static Application* m_pApplication;
  };
}

#endif // fl_Application_h__
