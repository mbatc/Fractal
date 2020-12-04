#ifndef fl_Input_Keyboard_h__
#define fl_Input_Keyboard_h__

#include "flInputDevice.h"
#include "../platform/flEvent.h"

namespace flEngine
{
  namespace Input
  {
    /**
     * @brief Supported keyboard key codes.
     */
    enum KeyCode
    {
      KC_Unknown,         ///< An unknown key code
      KC_Equals,          ///< The '=' key
      KC_Apostraphe,      ///< The '`' key
      KC_OpenSqrBracket,  ///< The '[' key
      KC_CloseSqrBracket, ///< The ']' key
      KC_Period,          ///< The '.' key
      KC_Comma,           ///< The ',' key
      KC_ForwardSlash,    ///< The '/' key
      KC_BackSlash,       ///< The '\' key
      KC_Tab,             ///< The Tab key
      KC_Shift,           ///< Any Shift key
      KC_LShift,          ///< The left Shift key
      KC_RShift,          ///< The right Shift key
      KC_Control,         ///< Any Control key
      KC_LControl,        ///< The left Control key
      KC_RControl,        ///< The right Control key
      KC_Return,          ///< The Enter/Return key
      KC_Backspace,       ///< The Backspace key
      KC_LAlt,            ///< The left Alt key
      KC_RAlt,            ///< The right Alt key
      KC_PageDown,        ///< The Page Down key
      KC_PageUp,          ///< The Page Up key
      KC_Left,            ///< The Left arrow key
      KC_Right,           ///< The Right arrow key
      KC_Up,              ///< The Up arrow key
      KC_Down,            ///< The Down arrow key

      KC_Numpad0,         ///< The num-pad 0 key
      KC_Numpad1,         ///< The num-pad 1 key
      KC_Numpad2,         ///< The num-pad 2 key
      KC_Numpad3,         ///< The num-pad 3 key
      KC_Numpad4,         ///< The num-pad 4 key
      KC_Numpad5,         ///< The num-pad 5 key
      KC_Numpad6,         ///< The num-pad 6 key
      KC_Numpad7,         ///< The num-pad 7 key
      KC_Numpad8,         ///< The num-pad 8 key
      KC_Numpad9,         ///< The num-pad 9 key

      KC_F1,              ///< The F1 key
      KC_F2,              ///< The F2 key
      KC_F3,              ///< The F3 key
      KC_F4,              ///< The F4 key
      KC_F5,              ///< The F5 key
      KC_F6,              ///< The F6 key
      KC_F7,              ///< The F7 key
      KC_F8,              ///< The F8 key
      KC_F9,              ///< The F9 key
      KC_F10,             ///< The F10 key
      KC_F11,             ///< The F11 key
      KC_F12,             ///< The F12 key

      KC_0 = 48,          ///< The '0' key (also mapped to ASCII '0')
      KC_1,               ///< The '1' key (also mapped to ASCII '1')
      KC_2,               ///< The '2' key (also mapped to ASCII '2')
      KC_3,               ///< The '3' key (also mapped to ASCII '3')
      KC_4,               ///< The '4' key (also mapped to ASCII '4')
      KC_5,               ///< The '5' key (also mapped to ASCII '5')
      KC_6,               ///< The '6' key (also mapped to ASCII '6')
      KC_7,               ///< The '7' key (also mapped to ASCII '7')
      KC_8,               ///< The '8' key (also mapped to ASCII '8')
      KC_9,               ///< The '9' key (also mapped to ASCII '9')

      KC_PauseBreak,      ///< The Pause Break key
      KC_Escape,          ///< The Escape key
      KC_Space,           ///< The Space Bar key
      KC_Home,            ///< The Home key
      KC_End,             ///< The End key
      KC_Delete,          ///< The Delete key
      KC_Insert,          ///< The Insert key

      KC_A = 65,          ///< The 'A' key (also mapped to ASCII 'A')
      KC_B,               ///< The 'B' key (also mapped to ASCII 'B')
      KC_C,               ///< The 'C' key (also mapped to ASCII 'C')
      KC_D,               ///< The 'D' key (also mapped to ASCII 'D')
      KC_E,               ///< The 'E' key (also mapped to ASCII 'E')
      KC_F,               ///< The 'F' key (also mapped to ASCII 'F')
      KC_G,               ///< The 'G' key (also mapped to ASCII 'G')
      KC_H,               ///< The 'H' key (also mapped to ASCII 'H')
      KC_I,               ///< The 'I' key (also mapped to ASCII 'I')
      KC_J,               ///< The 'J' key (also mapped to ASCII 'J')
      KC_K,               ///< The 'K' key (also mapped to ASCII 'K')
      KC_L,               ///< The 'L' key (also mapped to ASCII 'L')
      KC_M,               ///< The 'M' key (also mapped to ASCII 'M')
      KC_N,               ///< The 'N' key (also mapped to ASCII 'N')
      KC_O,               ///< The 'O' key (also mapped to ASCII 'O')
      KC_P,               ///< The 'P' key (also mapped to ASCII 'P')
      KC_Q,               ///< The 'Q' key (also mapped to ASCII 'Q')
      KC_R,               ///< The 'R' key (also mapped to ASCII 'R')
      KC_S,               ///< The 'S' key (also mapped to ASCII 'S')
      KC_T,               ///< The 'T' key (also mapped to ASCII 'T')
      KC_U,               ///< The 'U' key (also mapped to ASCII 'U')
      KC_V,               ///< The 'V' key (also mapped to ASCII 'V')
      KC_W,               ///< The 'W' key (also mapped to ASCII 'W')
      KC_X,               ///< The 'X' key (also mapped to ASCII 'X')
      KC_Y,               ///< The 'Y' key (also mapped to ASCII 'Y')
      KC_Z,               ///< The 'Z' key (also mapped to ASCII 'Z')

      KC_Alt,             ///< Any 'Alt' key
      KC_PrintScreen,     ///< The print screen key
      KC_NumLock,         ///< The Num-Lock key
      KC_ScrollLock,      ///< The Scroll-Lock key
      KC_Minus,           ///< The '-' key
      KC_NumpadMinus,     ///< The num-pad '-' key
      KC_NumpadDecimal,   ///< The num-pad '.' key
      KC_NumpadMultiply,  ///< The num-pad '*' key
      KC_NumpadDivide,    ///< The num-pad '/' key
      KC_NumpadAdd,       ///< The num-pad '+' key
      KC_VolumeUp,        ///< The Volume Up media key
      KC_VolumeDown,      ///< The Volume Down media key
      KC_Mute,            ///< The Mute media key
      KC_PlayPause,       ///< The Play/Pause media key
      KC_NextTrack,       ///< The Next track media key
      KC_PrevTrack,       ///< The Previous track media key
      KC_Stop,            ///< The Stop media key
      KC_Quote,           ///< The ''' key
      KC_SemiColon,       ///< The ';' key
      KC_CapsLock,        ///< The Caps Lock key

      KC_Count            ///< The number of key codes
    };

    /**
    * @brief An input device interface for to the keyboard.
    *
    *
    * This input device, by default, receives global keyboard events from the
    * OS. Creating an instance of this class will allow you to query any keyboard
    * inputs received by a Window created by Fractal Engine.
    */
    class flEXPORT Keyboard : public InputDevice
    {
    public:
      Keyboard();

      /**
       * @brief Get the 'Down' state of a key.
       *
       * A key is 'Down' when the it is pressed and held i.e. if a key is pressed,
       * it will be down until it is released.
       *
       * @param [in] key The KeyCode of the key to check.
       *
       * @return True if the key specified is down, otherwise false.
       */
      bool GetKeyDown(flIN KeyCode key) const;

      /**
       * @brief Get the 'Pressed' state of a key.
       *
       * A key is 'Pressed' when the its state goes from Up to Down.
       *
       * @param [in] key The KeyCode of the key to check.
       *
       * @return True if the key specified is pressed, otherwise false.
       */
      bool GetKeyPressed(flIN KeyCode key) const;

      /**
       * @brief Get the 'Released' state of a key.
       *
       * A key is 'Released' when the its state goes from Down to Up.
       *
       * @param [in] key The KeyCode of the key to check.
       *
       * @return True if the key specified is released, otherwise false.
       */
      bool GetKeyReleased(flIN KeyCode key) const;

      /**
       * @brief The default Keyboard event handler.
       *
       * This is the default event handler that can be used to forward system keyboard
       * events to a keyboards InputDeviceServer.
       *
       * @param [in]  pEvent       The event to handle.
       * @param [out] pInputServer A pointer to an InputDeviceServer.
       */
      static void EventHandler(flIN Platform::Event *pEvent, flIN void *pInputServer);
    };
  }
}

#endif // fl_Input_Mouse_h__
