#include "input/flInputDevice.h"
#include "atHashMap.h"
#include "atVector.h"
#include "atString.h"

using namespace flEngine::Input;

bool InputDevice::Button::IsPressed() const
{
  return m_down && !m_lastDown;
}

bool InputDevice::Button::IsReleased() const
{
  return !m_down && m_lastDown;
}

bool InputDevice::Button::IsDown() const
{
  return m_down;
}

void InputDevice::Button::Set(bool down)
{
  m_lastDown = m_down;
  m_down = down;
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

void InputDevice::Analog::SetValue(float newValue)
{
  m_lastValue = m_value;
  m_value = newValue;
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
      void Construct(int64_t buttonCount, int64_t analogCount)
      {
        m_buttons.Construct(buttonCount);
        m_analogs.Construct(analogCount);
      }

      _flInputSet<InputDevice::Button> m_buttons;
      _flInputSet<InputDevice::Analog> m_analogs;
    };
  }
}

flPIMPL_IMPL(InputDevice)

#define flIMPL flPIMPL(InputDevice)

InputDevice::InputDevice(flIN int64_t buttonCount, flIN int64_t analogCount)
{
  flIMPL->Construct(buttonCount, analogCount);
}

int64_t InputDevice::GetButtonCount() const
{
  return flIMPL->m_buttons.GetCount();
}

int64_t InputDevice::GetAnalogCount() const
{
  return flIMPL->m_analogs.GetCount();
}

InputDevice::Button* InputDevice::GetButton(int64_t index)
{
  return flIMPL->m_buttons.Get(index);
}

InputDevice::Button* InputDevice::GetButton(const char *name)
{
  return flIMPL->m_buttons.Get(name);
}

InputDevice::Analog* InputDevice::GetAnalog(int64_t index)
{
  return flIMPL->m_analogs.Get(index);
}

InputDevice::Analog* InputDevice::GetAnalog(const char *name)
{
  return flIMPL->m_analogs.Get(name);
}

const InputDevice::Button* InputDevice::GetButton(int64_t index) const
{
  return flIMPL->m_buttons.Get(index);
}

const InputDevice::Button* InputDevice::GetButton(const char *name) const
{
  return flIMPL->m_buttons.Get(name);
}

const InputDevice::Analog* InputDevice::GetAnalog(int64_t index) const
{
  return flIMPL->m_analogs.Get(index);
}

const InputDevice::Analog* InputDevice::GetAnalog(const char *name) const
{
  return flIMPL->m_analogs.Get(name);
}

bool InputDevice::AddButtonName(int64_t index, const char *name)
{
  return flIMPL->m_buttons.AddName(index, name);
}

bool InputDevice::AddAnalogName(int64_t index, const char *name)
{
  return flIMPL->m_analogs.AddName(index, name);
}

bool InputDevice::RemoveButtonName(const char *name)
{
  return flIMPL->m_buttons.RemoveName(name);
}

bool InputDevice::RemoveAnalogName(const char *name)
{
  return flIMPL->m_analogs.RemoveName(name);
}

int64_t InputDevice::GetButtonNameCount(int64_t index) const
{
  return flIMPL->m_buttons.GetNames(index).size();
}

const char* InputDevice::GetButtonName(int64_t buttonIndex, int64_t nameIndex) const
{
  if (nameIndex >= GetButtonNameCount(buttonIndex) || nameIndex < 0)
    return nullptr;
  return flIMPL->m_buttons.GetNames(buttonIndex)[nameIndex];
}

int64_t InputDevice::GetAnalogNameCount(int64_t index) const
{
  return flIMPL->m_analogs.GetNames(index).size();
}

const char* InputDevice::GetAnalogName(int64_t buttonIndex, int64_t nameIndex) const
{
  if (nameIndex >= GetAnalogNameCount(buttonIndex) || nameIndex < 0)
    return nullptr;
  return flIMPL->m_buttons.GetNames(buttonIndex)[nameIndex];
}

int64_t InputDevice::GetButtonIndex(const char *name) const
{
  return flIMPL->m_buttons.GetIndex(name);
}

int64_t InputDevice::GetAnalogIndex(const char *name) const
{
  return flIMPL->m_analogs.GetIndex(name);
}
