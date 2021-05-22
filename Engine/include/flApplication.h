#pragma once

#include "flSubSystem.h"
#include "flRef.h"

namespace flEngine
{
  namespace Platform {
    struct Event;
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
    void AddSubSystem(Args&&... args) {
      AddSubSystem(flNew T(std::forward<Args>(args)...), typeid(T).name());
    }

    template<typename T>
    Ref<T> GetSubSystem() {
      return MakeRef(GetSubSystem(typeid(T).name()), true);
    }

    /**
     * @brief Close the application.
     */
    void Close();

    /**
     * @brief Get the global Application instance.
     **/
    static Application& Get();

  protected:
    Application();

  private:
    void AddSubSystem(SubSystem *pSystem, char const *name);
    SubSystem *GetSubSystem(char const *name);

    int Run(); // Application entry point
  };
}
