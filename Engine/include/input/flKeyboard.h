#ifndef fl_Input_Keyboard_h__
#define fl_Input_Keyboard_h__

#include "flInputDevice.h"

namespace flEngine
{
  namespace Input
  {
    enum KeyCode
    {
      KC_Unknown,
      KC_Equals,
      KC_Apostraphe,
      KC_OpenSqrBracket,
      KC_CloseSqrBracket,
      KC_Period,
      KC_Comma,
      KC_ForwardSlash,
      KC_BackSlash,
      KC_Tab,
      KC_Shift,
      KC_LShift,
      KC_RShift,
      KC_Control,
      KC_LControl,
      KC_RControl,
      KC_Return,
      KC_Backspace,
      KC_LAlt,
      KC_RAlt,
      KC_PageDown,
      KC_PageUp,
      KC_Left,
      KC_Right,
      KC_Up,
      KC_Down,

      KC_Numpad0,
      KC_Numpad1,
      KC_Numpad2,
      KC_Numpad3,
      KC_Numpad4,
      KC_Numpad5,
      KC_Numpad6,
      KC_Numpad7,
      KC_Numpad8,
      KC_Numpad9,

      KC_F1,
      KC_F2,
      KC_F3,
      KC_F4,
      KC_F5,
      KC_F6,
      KC_F7,
      KC_F8,
      KC_F9,
      KC_F10,
      KC_F11,
      KC_F12,

      KC_0 = 48,
      KC_1,
      KC_2,
      KC_3,
      KC_4,
      KC_5,
      KC_6,
      KC_7,
      KC_8,
      KC_9,

      KC_PauseBreak,
      KC_Escape,
      KC_Space,
      KC_Delete,
      KC_Home,
      KC_Insert,
      KC_End,

      KC_A = 65,
      KC_B,
      KC_C,
      KC_D,
      KC_E,
      KC_F,
      KC_G,
      KC_H,
      KC_I,
      KC_J,
      KC_K,
      KC_L,
      KC_M,
      KC_N,
      KC_O,
      KC_P,
      KC_Q,
      KC_R,
      KC_S,
      KC_T,
      KC_U,
      KC_V,
      KC_W,
      KC_X,
      KC_Y,
      KC_Z,

      KC_Alt,
      KC_Menu,
      KC_PrintScreen,
      KC_NumLock,
      KC_ScrollLock,
      KC_Back,
      KC_Clear,
      KC_Select,
      KC_Execute,
      KC_Print,
      KC_Help,
      KC_Jump,
      KC_Minus,
      KC_Play,
      KC_Subtract,
      KC_Zoom,
      KC_Separator,
      KC_VolumeUp,
      KC_VolumeDown,
      KC_Mute,
      KC_PlayPause,
      KC_NextTrack,
      KC_PrevTrack,
      KC_Stop,
      KC_Quote,
      KC_SemiColon,
      KC_CapsLock,

      KC_Count
    };

    class flEXPORT Keyboard : public InputDevice
    {
    public:
      Keyboard();

      bool GetKeyDown(KeyCode key) const;
      bool GetKeyPressed(KeyCode key) const;
      bool GetKeyReleased(KeyCode key) const;

      static void EventHandler(Platform::Event *pEvent, void *pUserData);
    };
  }
}

#endif // fl_Input_Mouse_h__
