#ifndef fl_Input_Mouse_h__
#define fl_Input_Mouse_h__

#include "../math/flMath.h"
#include "flInputDevice.h"

namespace flEngine
{
  namespace Input
  {
    enum MouseButton
    {
      MB_Left,
      MB_Right,
      MB_Middle,
      MB_Count,
      MB_Extended = MB_Count,
      MB_ExtendedCount = 16,
    };

    enum MouseAxis
    {
      MA_XPos,
      MA_YPos,
      MA_HScroll,
      MA_VScroll,
      MA_Count,
    };

    class flEXPORT Mouse : public InputDevice
    {
    public:
      Mouse();

      bool GetDown(MouseButton button) const;
      bool GetPressed(MouseButton button) const;
      bool GetReleased(MouseButton button) const;

      float GetX() const;
      float GetY() const;

      float GetXDelta() const;
      float GetYDelta() const;

      float GetScrollH() const;
      float GetScrollV() const;

      float GetScrollHDelta() const;
      float GetScrollVDelta() const;

      Math::flVec2F GetPosition() const;
      Math::flVec2F GetPositionDelta() const;

      Math::flVec2F GetScroll() const;
      Math::flVec2F GetScrollDelta() const;

      static void EventHandler(Platform::Event *pEvent, void *pUserData);

    protected:
      void OnUpdate() override;
    };
  }
}

#endif // fl_Input_Mouse_h__
