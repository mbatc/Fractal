#pragma once

#include "../flInterface.h"
#include "../flSubSystem.h"

namespace flEngine
{
  namespace GUI
  {
    class Panel;

    class Impl_GUISystem;

    class flEXPORT GUISystem : public SubSystem
    {
      flPIMPL_DEF(GUISystem);

    public:
      GUISystem();

      template<typename T, typename... Args>
      void Open(Args&&... args)
      {
        Open(MakeRef(flNew T(std::forward<Args>(args)...), false).Get());
      }

      virtual void OnUpdate() override;
      virtual void OnRender() override;

      virtual bool OnKeyState(Platform::Event* pEvent) override;
      virtual bool OnMouseState(Platform::Event* pEvent) override;
      virtual bool OnMouseScroll(Platform::Event* pEvent) override;

    protected:
      void Open(Panel *pPanel);
    };
  }
}
