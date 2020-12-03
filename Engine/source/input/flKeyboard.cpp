#include "input\flKeyboard.h"
#include "input\flInputDeviceServer.h"
#include "platform\flEventQueue.h"

using namespace flEngine;
using namespace flEngine::Input;

class _GlobalKeyboardServer : public InputDeviceServer
{
public:
  _GlobalKeyboardServer()
  {
    m_events.SetFilter(Platform::E_Type_Keyboard);
    m_events.SetEventCallback(
      [](Platform::Event *pEvent, void *pUserData)
      {
        _GlobalKeyboardServer *pServer = (_GlobalKeyboardServer*)pUserData;

        if (pEvent->id == Platform::E_Kbd_KeyState) // Send the keyboard events
          pServer->SendEvent(pEvent->kbdState.keyCode, pEvent->kbdState.isDown);
      },
      this);
  }

  static _GlobalKeyboardServer* Create()
  {
    return flNew _GlobalKeyboardServer;
  }

protected:
  Platform::EventQueue m_events;
};

Keyboard::Keyboard()
  : InputDevice(KC_Count, 0, _GlobalKeyboardServer::Create())
{}

bool Keyboard::GetKeyDown(KeyCode key) const
{
  return GetButton(key)->IsDown();
}

bool Keyboard::GetKeyPressed(KeyCode key) const
{
  return GetButton(key)->IsPressed();
}

bool Keyboard::GetKeyReleased(KeyCode key) const
{
  return GetButton(key)->IsReleased();
}
