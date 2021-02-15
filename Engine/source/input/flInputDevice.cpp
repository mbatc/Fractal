#include "input/flInputDevice.h"
#include "ctHashMap.h"
#include "ctVector.h"
#include "ctString.h"
#include "ctPool.h"
#include <time.h>

using namespace flEngine::Input;

static ctVector<InputDevice*> _devices;

bool InputDevice::Button::IsPressed() const
{
  return m_pressed;
}

bool InputDevice::Button::IsReleased() const
{
  return m_released;
}

bool InputDevice::Button::IsDown() const
{
  return m_down;
}

float InputDevice::Analog::GetValue() const
{
  return m_value;
}

float InputDevice::Analog::GetDelta() const
{
  return m_value - m_lastValue;
}

bool InputDevice::Analog::HasChanged() const
{
  return m_value != m_lastValue;
}

static ctVector<ctString> _emptyNames;

namespace flEngine
{
  namespace Input
  {
    class flPIMPL_CLASS(InputDevice)
    {
    public:
      void Construct(InputDevice *pDevice, int64_t buttonCount, int64_t analogCount, InputDeviceServer *pServer)
      {
        // Setup buttons
        m_buttons.resize(buttonCount);
        m_analogs.resize(analogCount);

        // Setup device and server
        m_pDevice = pDevice;
        m_pServer = pServer ? pServer : InputDeviceServer::Create();
        _devices.push_back(pDevice);
      }

      ~flPIMPL_CLASS(InputDevice)()
      {
        _devices.erase(ctIndexOf(_devices.begin(), _devices.end(), m_pDevice));

        if (m_pServer)
          m_pServer->DecRef();
      }

      InputDevice       *m_pDevice  = nullptr;
      InputDeviceServer *m_pServer  = nullptr;

      ctVector<InputDevice::Button> m_buttons;
      ctVector<InputDevice::Analog> m_analogs;
    };
  }
}

flPIMPL_IMPL(InputDevice)

#define flIMPL flPIMPL(InputDevice)

InputDevice::InputDevice(flIN int64_t buttonCount, flIN int64_t analogCount, flIN InputDeviceServer *pServer)
{
  flIMPL->Construct(this, buttonCount, analogCount, pServer);
}

void InputDevice::SetServer(flIN InputDeviceServer *pServer)
{
  pServer->IncRef();
  flIMPL->m_pServer->DecRef();
  flIMPL->m_pServer = pServer;
}

InputDeviceServer* InputDevice::GetServer() const
{
  return flIMPL->m_pServer;
}

int64_t InputDevice::GetButtonCount() const
{
  return flIMPL->m_buttons.size();
}

int64_t InputDevice::GetAnalogCount() const
{
  return flIMPL->m_analogs.size();
}

InputDevice::Button* InputDevice::GetButton(flIN int64_t index)
{
  return index < 0 || index >= GetButtonCount() ? nullptr : &flIMPL->m_buttons[index];
}

InputDevice::Analog* InputDevice::GetAnalog(flIN int64_t index)
{
  return index < 0 || index >= GetAnalogCount() ? nullptr : &flIMPL->m_analogs[index];
}

const InputDevice::Button* InputDevice::GetButton(flIN int64_t index) const
{
  return index < 0 || index >= GetButtonCount() ? nullptr : &flIMPL->m_buttons[index];
}

const InputDevice::Analog* InputDevice::GetAnalog(flIN int64_t index) const
{
  return index < 0 || index >= GetAnalogCount() ? nullptr : &flIMPL->m_analogs[index];
}


void InputDevice::Update()
{
  flIMPL->m_pServer->Lock(); // Lock to stop new events from being received

  int64_t id          = 0;
  int64_t timestamp   = 0;
  bool    pressed     = false;
  int64_t updateClock = clock();

  // Update buttons
  for (Button &button : flIMPL->m_buttons)
  {
    button.m_pressed  = false;
    button.m_released = false;

    if (button.m_down) // If the button is down, update the down time
      button.m_downTime = updateClock;
  }

  // Update analogs
  for (Analog &analog : flIMPL->m_analogs)
  {
    analog.m_lastValue     = analog.m_value;
    analog.m_lastValueTime = analog.m_valueTime;
    analog.m_valueTime     = updateClock;
  }

  // Receive button events
  while (flIMPL->m_pServer->GetEvent(&id, &pressed, &timestamp))
  {
    Button *pButton = GetButton(id);

    if (pButton)
    {
      pButton->m_down = pressed;
      if (pressed)
      {
        pButton->m_pressed = true;
        pButton->m_pressedTime = timestamp;
      }
      else
      {
        pButton->m_released = true;
        pButton->m_releasedTime = timestamp;
      }
    }
  }

  // Receive analog events
  float value    = 0;
  bool  addValue = false;
  while (flIMPL->m_pServer->GetEvent(&id, &value, &addValue, &timestamp))
  {
    Analog *pAnalog = GetAnalog(id);

    if (pAnalog)
    {
      pAnalog->m_value = addValue ? pAnalog->m_value + value : value;
      pAnalog->m_valueTime = timestamp;
    }
  }

  flIMPL->m_pServer->Unlock();

  OnPostUpdate();
}

int64_t InputDevice::GetRegisteredDeviceCount()
{
  return _devices.size();
}

InputDevice* InputDevice::GetRegisteredDevice(flIN int64_t index)
{
  return _devices[index];
}

void InputDevice::OnPreUpdate()  { /*No Default behavior*/ }
void InputDevice::OnPostUpdate() { /*No Default behavior*/ }
