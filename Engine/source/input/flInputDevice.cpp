#include "input/flInputDevice.h"
#include "atHashMap.h"
#include "atVector.h"
#include "atString.h"
#include "atPool.h"
#include <time.h>

using namespace flEngine::Input;

static atPool<InputDevice*> _devices;

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

static atVector<atString> _emptyNames;

template<typename T> class _flInputSet
{
public:
  void Construct(int64_t count)
  {
    m_nameToInput.Clear();
    m_inputs.clear();
    m_inputs.resize(count);
  }

  T* Get(const int64_t &idx)
  {
    InputMapping *pMapping = GetMapping(idx);
    return pMapping ? &pMapping->input : nullptr;
  }

  T* Get(const atString &name)
  {
    InputMapping *pMapping = GetMapping(GetIndex(name));
    return pMapping ? &pMapping->input : nullptr;
  }

  bool AddName(const int64_t &idx, const atString &name)
  {
    InputMapping *pMapping = GetMapping(idx);
    if (!pMapping || !m_nameToInput.TryAdd(name))
      return false;

    pMapping->names.push_back(name);
    return true;
  }

  bool RemoveName(const atString &name)
  {
    InputMapping* pMapping = GetMapping(GetIndex(name));
    if (!pMapping)
      return false;
    for (int64_t i = 0; i < pMapping->names.size(); ++i)
      pMapping->names.erase(i);
    return true;
  }

  const atVector<atString>& GetNames(const int64_t &idx) const
  {
    const InputMapping *pMapping = GetMapping(idx);
    return pMapping ? pMapping->names : _emptyNames;
  }

  int64_t GetIndex(const atString &name) const
  {
    return m_nameToInput.GetOr(name, -1);
  }

  int64_t GetCount() const
  {
    return m_inputs.size();
  }

protected:
  struct InputMapping
  {
    T input;
    atVector<atString> names;
  };

  InputMapping* GetMapping(const int64_t &index)
  {
    return index < 0 || index >= m_inputs.size() ? nullptr : &m_inputs[index];
  }

  const InputMapping* GetMapping(const int64_t &index) const
  {
    return index < 0 || index >= m_inputs.size() ? nullptr : &m_inputs[index];
  }

  atVector<InputMapping> m_inputs;
  atHashMap<atString, int64_t> m_nameToInput;
};

namespace flEngine
{
  namespace Input
  {
    class flPIMPL_CLASS(InputDevice)
    {
    public:
      void Construct(InputDevice *pDevice, int64_t buttonCount, int64_t analogCount, InputDeviceServer *pServer)
      {
        m_pDevice = pDevice;
        m_deviceID = _devices.Add(pDevice);
        m_buttons.Construct(buttonCount);
        m_analogs.Construct(analogCount);
        m_pServer = pServer ? pServer : InputDeviceServer::Create();
      }

      ~flPIMPL_CLASS(InputDevice)()
      {
        _devices.erase(m_deviceID);
      }

      int64_t            m_deviceID = -1;
      InputDevice       *m_pDevice  = nullptr;
      InputDeviceServer *m_pServer  = nullptr;

      _flInputSet<InputDevice::Button> m_buttons;
      _flInputSet<InputDevice::Analog> m_analogs;
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
  return flIMPL->m_buttons.GetCount();
}

int64_t InputDevice::GetAnalogCount() const
{
  return flIMPL->m_analogs.GetCount();
}

InputDevice::Button* InputDevice::GetButton(flIN int64_t index)
{
  return flIMPL->m_buttons.Get(index);
}

InputDevice::Button* InputDevice::GetButton(flIN const char *name)
{
  return flIMPL->m_buttons.Get(name);
}

InputDevice::Analog* InputDevice::GetAnalog(flIN int64_t index)
{
  return flIMPL->m_analogs.Get(index);
}

InputDevice::Analog* InputDevice::GetAnalog(flIN const char *name)
{
  return flIMPL->m_analogs.Get(name);
}

const InputDevice::Button* InputDevice::GetButton(flIN int64_t index) const
{
  return flIMPL->m_buttons.Get(index);
}

const InputDevice::Button* InputDevice::GetButton(flIN const char *name) const
{
  return flIMPL->m_buttons.Get(name);
}

const InputDevice::Analog* InputDevice::GetAnalog(flIN int64_t index) const
{
  return flIMPL->m_analogs.Get(index);
}

const InputDevice::Analog* InputDevice::GetAnalog(flIN const char *name) const
{
  return flIMPL->m_analogs.Get(name);
}

bool InputDevice::AddButtonName(flIN int64_t index, flIN const char *name)
{
  return flIMPL->m_buttons.AddName(index, name);
}

bool InputDevice::AddAnalogName(flIN int64_t index, flIN const char *name)
{
  return flIMPL->m_analogs.AddName(index, name);
}

bool InputDevice::RemoveButtonName(flIN const char *name)
{
  return flIMPL->m_buttons.RemoveName(name);
}

bool InputDevice::RemoveAnalogName(flIN const char *name)
{
  return flIMPL->m_analogs.RemoveName(name);
}

int64_t InputDevice::GetButtonNameCount(flIN int64_t index) const
{
  return flIMPL->m_buttons.GetNames(index).size();
}

const char* InputDevice::GetButtonName(flIN int64_t buttonIndex, flIN int64_t nameIndex) const
{
  if (nameIndex >= GetButtonNameCount(buttonIndex) || nameIndex < 0)
    return nullptr;
  return flIMPL->m_buttons.GetNames(buttonIndex)[nameIndex];
}

int64_t InputDevice::GetAnalogNameCount(flIN int64_t index) const
{
  return flIMPL->m_analogs.GetNames(index).size();
}

const char* InputDevice::GetAnalogName(flIN int64_t buttonIndex, flIN int64_t nameIndex) const
{
  if (nameIndex >= GetAnalogNameCount(buttonIndex) || nameIndex < 0)
    return nullptr;
  return flIMPL->m_buttons.GetNames(buttonIndex)[nameIndex];
}

int64_t InputDevice::GetButtonIndex(flIN const char *name) const
{
  return flIMPL->m_buttons.GetIndex(name);
}

int64_t InputDevice::GetAnalogIndex(flIN const char *name) const
{
  return flIMPL->m_analogs.GetIndex(name);
}

void InputDevice::Update()
{
  OnUpdate();

  flIMPL->m_pServer->Lock(); // Lock to stop new events from being received

  int64_t id          = 0;
  int64_t timestamp   = 0;
  bool    pressed     = false;
  int64_t updateClock = clock();

  // Update buttons
  int64_t buttonCount = flIMPL->m_buttons.GetCount();
  for (int64_t i = 0; i < buttonCount; ++i)
  {
    Button *pButton = flIMPL->m_buttons.Get(i);
    pButton->m_pressed  = false;
    pButton->m_released = false;

    if (pButton->m_down) // If the button is down, update the down time
      pButton->m_downTime = updateClock;
  }

  // Update analogs
  int64_t analogCount = flIMPL->m_analogs.GetCount();
  for (int64_t i = 0; i < analogCount; ++i)
  {
    Analog *pAnalog = flIMPL->m_analogs.Get(i);

    pAnalog->m_lastValue     = pAnalog->m_value;
    pAnalog->m_lastValueTime = pAnalog->m_valueTime;
    pAnalog->m_valueTime     = updateClock;
  }

  // Receive button events
  while (flIMPL->m_pServer->GetEvent(&id, &pressed, &timestamp))
  {
    Button *pButton = GetButton(id);

    pButton->m_down = pressed;
    if (pressed)
    {
      pButton->m_pressed     = true;
      pButton->m_pressedTime = timestamp;
    }
    else
    {
      pButton->m_released     = true;
      pButton->m_releasedTime = timestamp;
    }
  }

  // Receive analog events
  float value    = 0;
  bool  addValue = false;
  while (flIMPL->m_pServer->GetEvent(&id, &value, &addValue, &timestamp))
  {
    Analog *pAnalog = GetAnalog(id);

    pAnalog->m_value     = addValue ? pAnalog->m_value + value : value;
    pAnalog->m_valueTime = timestamp;
  }

  flIMPL->m_pServer->Unlock();
}

int64_t InputDevice::GetRegisteredDeviceCount()
{
  return _devices.size();
}

InputDevice* InputDevice::GetRegisteredDevice(flIN int64_t index)
{
  return _devices[index];
}

void InputDevice::OnUpdate() {}
