#pragma once

#include "flEventDispatcher.h"

namespace Fractal
{
  class flEXPORT ApplicationBehaviour : public EventDispatcher
  {
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
    virtual void OnShutdown();

    /**
     * @brief Perform shutdown tasks.
     *
     * This function is called each frame during the main update step in the engine.
     *
     * You can override this function to implement any extra functionality your application needs.
     **/
    virtual void OnUpdate();

    /**
     * @brief Perform shutdown tasks.
     *
     * This function is called each frame during the main render step in the engine.
     *
     * You can override this function to implement any extra functionality your application needs.
     **/
    virtual void OnRender();

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
  };
}