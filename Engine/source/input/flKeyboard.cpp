#include "input\flKeyboard.h"

using namespace flEngine::Input;

Keyboard::Keyboard()
  : InputDevice(KC_Count, 0)
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
