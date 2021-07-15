#pragma once

#include "flModule.h"
#include "flRef.h"

namespace Fractal
{
  struct Event;

  class IWindow;
  class ITask;
  class API;

  class Impl_Application;

  /**
   * @brief The Application class is used to implement your client application.
   *
   * Using the Engines provided entry point ensures all the subsystems are
   * correctly initialized before entering your application.
   *
   * After implementing a subclass of Application, you need to include
   * flEntryPoint.h in a source file and implement the Fractal::CreateApplication().
   *
   * This class is a singleton and only 1 instance of an Application subclass should be
   * created at any time. You should not instantiate a subclass of Application in your
   * client app. Fractal will handle the lifetime of the application class using the
   * Fractal::CreateApplication() function you implement.
   *
   **/
  class flEXPORT Application : public ApplicationBehaviour
  {
    flPIMPL_DEF(Application);

    friend class FractalEntryHandler;

  public:
    template<typename T, typename... Args>
    void AddModule(Args&& ... args) {
      AddModule(flNew T(std::forward<Args>(args)...), typeid(T).name());
    }

    template<typename T>
    T* GetModule() {
      return (T*)GetModule(typeid(T).name());
    }

    /**
     * @brief Close the application.
     */
    virtual void Close() = 0;

    virtual int Run() = 0;
    
    virtual void AddModule(Module* pSystem, char const* name) = 0;

    virtual Module* GetModule(char const* name) = 0;
  };
}

extern "C" {
  /**
   * @brief Returns a pointer to the applications main window.
   */
  flEXPORT Fractal::IWindow* flCCONV Fractal_GetMainWindow();

  /**
   * @brief Returns a pointer to the applications graphics API.
   */
  flEXPORT Fractal::API* flCCONV Fractal_GetGraphicsAPI();

  /**
   * @brief Get the global Application instance.
   **/
  flEXPORT Fractal::Application* flCCONV Fractal_GetApplication();

  /**
   * @brief Get the ID of the applications main thread.
   */
  flEXPORT int64_t flCCONV Fractal_Application_MainThreadID();

  /**
   * @brief Await the completion of a task.
   *
   * The task will be executed on the main thread. If this function is
   * called from the applications main thread, the task will be executed
   * immediately.
   *
   * @param [in] pTask The task to execute.
   */
  flEXPORT Fractal::ITask* flCCONV Fractal_Application_EnqueueTask(flIN Fractal::ITask* pTask);

  /**
   * @brief Await the completion of a task.
   *
   * The task will be executed on the main thread. If this function is
   * called from the applications main thread, the task will be executed
   * immediately.
   *
   * @param [in] pTask The task to execute.
   *
   * @return The result returned by the task.
   */
  flEXPORT int64_t flCCONV Fractal_Application_Await(flIN Fractal::ITask* pTask);
}
