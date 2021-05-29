#pragma once

#include "../flApplicationBehaviour.h"

namespace flEngine
{
  namespace GUI
  {
    class GUISystem;

    class flPIMPL_CLASS(Panel);

    class flEXPORT Panel : public ApplicationBehaviour
    {
      flPIMPL_DEF(Panel);

    public:
      Panel(GUISystem *pGUI, char const *name);

      void Update();

      Math::Vec2F Position();

      Math::Vec2F Size();

      Math::Vec2F ContentAreaSize();

      virtual void OnGUI();

      GUISystem * GetGUI();

      GUISystem const *GetGUI() const;
    };
  }
}