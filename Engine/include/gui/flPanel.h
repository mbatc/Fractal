#pragma once

#include "../flInterface.h"

namespace flEngine
{
  namespace GUI
  {
    class flPIMPL_CLASS(Panel);

    class flEXPORT Panel : public Interface
    {
      flPIMPL_DEF(Panel);

    public:
      Panel(char const *name);

      void Update();

      Math::Vec2F Position();

      Math::Vec2F Size();

      virtual void OnGUI();
    };
  }
}