#pragma once

#include "flComponent.h"

namespace Fractal
{
  /**
   * @brief The base class for a behavior component.
   *
   * This component provides an interface to implement scene behavior.
   */
  class flEXPORT NodeBehaviour : public Component
  {
    FL_IMPLEMENT_COMPONENT(NodeBehaviour, "NodeBehaviour", Component)

  public:
    /**
     * @brief Called on the Update step.
     */
    virtual void OnUpdate();

    /**
     * @brief Called before the update step.
     */
    virtual void OnPreUpdate();

    /**
     * @brief Called after the Update step.
     */
    virtual void OnPostUpdate();

    /**
     * @brief Called on the Render step.
     */
    virtual void OnRender();

    /**
     * @brief Called before the Render step.
     */
    virtual void OnPreRender();

    /**
     * @brief Called after the Render step.
     */
    virtual void OnPostRender();
  };
}
