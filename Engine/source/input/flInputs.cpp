#include "input/flInputs.h"

using namespace flEngine;
using namespace flEngine::Input;

static Mouse _defaultMouse;
static Keyboard _defaultKeyboard;

static Mouse *_pActiveMouse = &_defaultMouse;
static Keyboard *_pActiveKeyboard = &_defaultKeyboard;

namespace flEngine
{
  class flPIMPL_CLASS(Inputs)
  {
  public:
    Mouse m_mouse;
    Keyboard m_keyboard;
  };
}

flPIMPL_IMPL(Inputs)

#define flIMPL flPIMPL(Inputs)

Mouse* Inputs::GetMouse()
{
  return &flIMPL->m_mouse;
}

Keyboard* Inputs::GetKeyboard()
{
  return &flIMPL->m_keyboard;
}

void Inputs::Update()
{
  int64_t deviceCount = InputDevice::GetRegisteredDeviceCount();
  for (int64_t i = 0; i < deviceCount; ++i)
    InputDevice::GetRegisteredDevice(i)->Update();
}

Mouse* Inputs::GetActiveMouse()
{
  return _pActiveMouse;
}

Keyboard* Inputs::GetActiveKeyboard()
{
  return _pActiveKeyboard;
}

void Inputs::SetActiveMouse(Mouse *pMouse)
{
  _pActiveMouse = pMouse ? pMouse : &_defaultMouse;
}

void Inputs::SetActiveKeyboard(Keyboard *pKeyboard)
{
  _pActiveKeyboard = pKeyboard ? pKeyboard : &_defaultKeyboard;
}
