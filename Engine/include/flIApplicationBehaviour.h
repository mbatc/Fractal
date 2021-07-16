#pragma once

#include "flEventDispatcher.h"

namespace Fractal
{
  class flEXPORT IApplicationBehaviour : public EventDispatcher
  {
  public:
    /**
     * @brief Perform startup tasks.
     *
     * This function is called when the application starts, after the engine has been initialized.
     *
     * You can override this function to implement any extra functionality your application needs.
    **/
    virtual bool OnStartup() = 0;

    /**
     * @brief Perform shutdown tasks.
     *
     * This function is called when the application is closing, before the engine is shutdown.
     *
     * You can override this function to implement any extra functionality your application needs.
     **/
    virtual void OnShutdown() = 0;

    /**
     * @brief Perform shutdown tasks.
     *
     * This function is called each frame during the main update step in the engine.
     *
     * You can override this function to implement any extra functionality your application needs.
     **/
    virtual void OnUpdate() = 0;

    /**
     * @brief Perform shutdown tasks.
     *
     * This function is called each frame during the main render step in the engine.
     *
     * You can override this function to implement any extra functionality your application needs.
     **/
    virtual void OnRender() = 0;

    /**
     * @brief Perform pre-update tasks.
     *
     * This function is called each frame before the main update step in the engine.
     *
     * You can override this function to implement any extra functionality your application needs.
     **/
    virtual void OnPreUpdate() = 0;

    /**
     * @brief Perform pre-render tasks.
     *
     * This function is called each frame before the main render step in the engine.
     *
     * You can override this function to implement any extra functionality your application needs.
     **/
    virtual void OnPreRender() = 0;

    /**
     * @brief Perform post-update tasks.
     *
     * This function is called each frame before the main update step in the engine.
     *
     * You can override this function to implement any extra functionality your application needs.
     **/
    virtual void OnPostUpdate() = 0;

    /**
     * @brief Perform post-render tasks.
     *
     * This function is called each frame after the main render step in the engine.
     *
     * You can override this function to implement any extra functionality your application needs.
     **/
    virtual void OnPostRender() = 0;
  };
}