#include "input\flKeyboard.h"
#include "input\flInputDeviceServer.h"
#include "platform\flEventQueue.h"

using namespace flEngine;
using namespace flEngine::Input;

Keyboard::Keyboard()
  : InputDevice(KC_Count, 0)
{}

bool Keyboard::GetKeyDown(flIN KeyCode key) const
{
  return GetButton(key)->IsDown();
}

bool Keyboard::GetKeyPressed(flIN KeyCode key) const
{
  return GetButton(key)->IsPressed();
}

bool Keyboard::GetKeyReleased(flIN KeyCode key) const
{
  return GetButton(key)->IsReleased();
}
