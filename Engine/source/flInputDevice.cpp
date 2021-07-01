#include "flInputDevice.h"
#include "ctHashMap.h"
#include "ctVector.h"
#include "ctString.h"
#include "ctPool.h"
#include "flRef.h"
#include <time.h>

namespace Fractal
{
  static ctVector<InputDevice *> _devices;
  static ctVector<ctString> _emptyNames;

  class Impl_InputDevice
  {
  public:
    void Construct(InputDevice *pDevice, int64_t buttonCount, int64_t analogCount, InputDeviceServer *pServer)
    {
      // Setup buttons
      m_buttons.resize(buttonCount);
      m_analogs.resize(analogCount);

      // Setup device and server
      m_pDevice = pDevice;
      m_pServer = pServer ? MakeRef(pServer, true) : MakeRef(InputDeviceServer::Create(), false);
      _devices.push_back(pDevice);
    }

    ~Impl_InputDevice()
    {
      _devices.erase(ctIndexOf(_devices.begin(), _devices.end(), m_pDevice));

      if (m_pServer)
        m_pServer->DecRef();
    }

    InputDevice *m_pDevice = nullptr;
    Ref<InputDeviceServer> m_pServer = nullptr;

    ctVector<InputDevice::Button> m_buttons;
    ctVector<InputDevice::Analog> m_analogs;
  };

  flPIMPL_IMPL(InputDevice);

    InputDevice::InputDevice(flIN int64_t buttonCount, flIN int64_t analogCount, flIN InputDeviceServer *pServer)
  {
    Impl()->Construct(this, buttonCount, analogCount, pServer);
  }

  void InputDevice::SetServer(flIN InputDeviceServer *pServer)
  {
    Impl()->m_pServer = MakeRef(pServer, true);
  }

  InputDeviceServer const *InputDevice::GetServer() const
  {
    return Impl()->m_pServer.Get();
  }

  InputDeviceServer *InputDevice::GetServer()
  {
    return Impl()->m_pServer.Get();
  }

  int64_t InputDevice::GetButtonCount() const
  {
    return Impl()->m_buttons.size();
  }

  int64_t InputDevice::GetAnalogCount() const
  {
    return Impl()->m_analogs.size();
  }

  InputDevice::Button *InputDevice::GetButton(flIN int64_t index)
  {
    return index < 0 || index >= GetButtonCount() ? nullptr : &Impl()->m_buttons[index];
  }

  InputDevice::Analog *InputDevice::GetAnalog(flIN int64_t index)
  {
    return index < 0 || index >= GetAnalogCount() ? nullptr : &Impl()->m_analogs[index];
  }

  const InputDevice::Button *InputDevice::GetButton(flIN int64_t index) const
  {
    return index < 0 || index >= GetButtonCount() ? nullptr : &Impl()->m_buttons[index];
  }

  const InputDevice::Analog *InputDevice::GetAnalog(flIN int64_t index) const
  {
    return index < 0 || index >= GetAnalogCount() ? nullptr : &Impl()->m_analogs[index];
  }


  void InputDevice::Update()
  {
    Impl()->m_pServer->Lock(); // Lock to stop new events from being received

    int64_t id = 0;
    int64_t timestamp = 0;
    bool    pressed = false;
    int64_t updateClock = clock();

    // Update buttons
    for (Button &button : Impl()->m_buttons)
    {
      button.m_pressed = false;
      button.m_released = false;

      if (button.m_down) // If the button is down, update the down time
        button.m_downTime = updateClock;
    }

    // Update analogs
    for (Analog &analog : Impl()->m_analogs)
    {
      analog.m_lastValue = analog.m_value;
      analog.m_lastValueTime = analog.m_valueTime;
      analog.m_valueTime = updateClock;
    }

    // Receive button events
    while (Impl()->m_pServer->GetEvent(&id, &pressed, &timestamp))
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
    float value = 0;
    bool  addValue = false;
    while (Impl()->m_pServer->GetEvent(&id, &value, &addValue, &timestamp))
    {
      Analog *pAnalog = GetAnalog(id);

      if (pAnalog)
      {
        pAnalog->m_value = addValue ? pAnalog->m_value + value : value;
        pAnalog->m_valueTime = timestamp;
      }
    }

    Impl()->m_pServer->Unlock();

    OnPostUpdate();
  }

  int64_t InputDevice::GetRegisteredDeviceCount()
  {
    return _devices.size();
  }

  InputDevice *InputDevice::GetRegisteredDevice(flIN int64_t index)
  {
    return _devices[index];
  }

  void InputDevice::OnPreUpdate() { /*No Default behavior*/ }
  void InputDevice::OnPostUpdate() { /*No Default behavior*/ }

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
}
