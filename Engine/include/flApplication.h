#ifndef fl_Application_h__
#define fl_Application_h__

#include "flInterface.h"

namespace flEngine
{
  class flPIMPL_CLASS(Application);

  /**
   * @brief The Application class is used to implement your client application.
   * 
   * Using the Engines provided entry point ensures all the subsystems are
   * correctly initialized before entering your application.
   * 
   * After implementing a subclass of Application, you need to include 
   * flEntryPoint.h in a source file and implement the flEngine::CreateApplication().
   * 
   * This class is a singleton and only 1 instance of an Application subclass should be
   * created at any time. You should not instantiate a subclass of Application in your
   * client app. Fractal will handle the lifetime of the application class using the
   * flEngine::CreateApplication() function you implement.
   * 
   **/
  class flEXPORT Application : public Interface
  {
    flPIMPL_DEF(Application);

    friend class FractalEntryHandler;

  public:
    /**
     * @brief Perform startup tasks.
     * 
     * This function is called when the application starts, after the engine has been initialized.
     *
     * You can override this function to implement any extra functionality your application needs.
   **/
    virtual bool OnStartup();

    /**
     * @brief Perform shutdown tasks.
     *
     * This function is called when the application is closing, before the engine is shutdown.
     *
     * You can override this function to implement any extra functionality your application needs.
     **/
    virtual bool OnShutdown();

    /**
     * @brief Perform pre-update tasks.
     * 
     * This function is called each frame before the main update step in the engine.
     *
     * You can override this function to implement any extra functionality your application needs.
     **/
    virtual void OnPreUpdate();

    /**
     * @brief Perform pre-render tasks.
     *
     * This function is called each frame before the main render step in the engine.
     *
     * You can override this function to implement any extra functionality your application needs.
     **/
    virtual void OnPreRender();

    /**
     * @brief Perform post-update tasks.
     *
     * This function is called each frame before the main update step in the engine.
     *
     * You can override this function to implement any extra functionality your application needs.
     **/
    virtual void OnPostUpdate();

    /**
     * @brief Perform post-render tasks.
     *
     * This function is called each frame after the main render step in the engine.
     * 
     * You can override this function to implement any extra functionality your application needs.
     **/
    virtual void OnPostRender();

    /**
     * @brief This function indicates if the engine should close the application.
     * 
     * You must implement this function to tell the engine when it needs to close.
     **/
    virtual bool IsRunning() = 0;

    /**
     * @brief Get the global Application instance.
     **/
    static Application& Get();

  protected:
    Application();

  private:
    int Run(); // Application entry point

    // The application instance
    static Application* m_pApplication;
  };
}

#endif // fl_Application_h__
