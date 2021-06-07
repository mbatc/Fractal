#pragma once

#include "flComponent.h"

namespace flEngine
{
  namespace Scene
  {
    class flEXPORT NodeBehaviour : public Component
    {
      FL_IMPLEMENT_COMPONENT(NodeBehaviour, "NodeBehaviour", Component)

    public:
      virtual void OnUpdate();
      virtual void OnPreUpdate();
      virtual void OnPostUpdate();

      virtual void OnRender();
      virtual void OnPreRender();
      virtual void OnPostRender();
    };
  }
}
