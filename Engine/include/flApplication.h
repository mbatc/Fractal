#pragma once

#include "flModule.h"
#include "flRef.h"

namespace flEngine
{
  namespace Platform {
    struct Event;
    class Window;
  }

  namespace Graphics {
    class API;
  }

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
  class flEXPORT Application : public ApplicationBehaviour
  {
    flPIMPL_DEF(Application);

    friend class FractalEntryHandler;

  public:
    template<typename T, typename... Args>
    void AddModule(Args&&... args) {
      AddModule(flNew T(std::forward<Args>(args)...), typeid(T).name());
    }

    template<typename T>
    T* GetModule() {
      return (T*)GetModule(typeid(T).name());
    }

    /**
     * @brief Close the application.
     */
    void Close();

    /**
     * @brief Returns a pointer to the applications main window.
     */
    Platform::Window * GetMainWindow();
    Platform::Window const * GetMainWindow() const;

    /**
     * @brief Returns a pointer to the applications graphics API.
     */
    Graphics::API * GetGraphicsAPI();
    Graphics::API const * GetGraphicsAPI() const;

    /**
     * @brief Get the global Application instance.
     **/
    static Application& Get();

  protected:
    Application(char const * graphicsAPIName);

  private:
    void AddModule(Module *pSystem, char const *name);
    Module *GetModule(char const *name);

    int Run(); // Application entry point
  };
}
