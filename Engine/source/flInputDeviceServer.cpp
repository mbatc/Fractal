#include "flInputDeviceServer.h"
#include "flThreads.h"
#include "ctVector.h"
#include <time.h>

struct _flButtonEvent
{
  bool    pressed;
  int64_t id;
  int64_t timestamp;
};

struct _flAnalogEvent
{
  bool    addValue;
  float   value;
  int64_t id;
  int64_t timestamp;
};

namespace Fractal
{
  class Impl_InputDeviceServer
  {
  public:
    ctVector<_flButtonEvent> m_buttonEvents;
    ctVector<_flAnalogEvent> m_analogEvents;
    RecursiveMutex  m_lock;
  };

  flPIMPL_IMPL(InputDeviceServer);

  InputDeviceServer::InputDeviceServer() {}

  InputDeviceServer* InputDeviceServer::Create()
  {
    return flNew InputDeviceServer;
  }

  void InputDeviceServer::Lock()
  {
    Impl()->m_lock.lock();
  }

  void InputDeviceServer::Unlock()
  {
    Impl()->m_lock.unlock();
  }

  bool InputDeviceServer::GetEvent(flOUT int64_t* pButtonID, flOUT bool* pValue, flOUT int64_t* pTimestamp)
  {
    Lock();
    if (Impl()->m_buttonEvents.size() <= 0)
    {
      Unlock();
      return false;
    }

    _flButtonEvent evnt = Impl()->m_buttonEvents.front();
    Impl()->m_buttonEvents.pop_front();

    if (pValue)
      *pValue = evnt.pressed;
    if (pButtonID)
      *pButtonID = evnt.id;
    if (pTimestamp)
      *pTimestamp = evnt.timestamp;
    Unlock();
    return true;
  }

  bool InputDeviceServer::GetEvent(flOUT int64_t* pAnalogID, flOUT float* pValue, flOUT bool* pAddValue, flOUT int64_t* pTimestamp)
  {
    Lock();
    if (Impl()->m_analogEvents.size() <= 0)
    {
      Unlock();
      return false;
    }

    _flAnalogEvent evnt = Impl()->m_analogEvents.front();
    Impl()->m_analogEvents.pop_front();

    if (pValue)
      *pValue = evnt.value;
    if (pAnalogID)
      *pAnalogID = evnt.id;
    if (pTimestamp)
      *pTimestamp = evnt.timestamp;
    Unlock();
    return true;
  }

  void InputDeviceServer::SendEvent(flIN int64_t buttonID, flIN bool pressed, flIN int64_t timestamp)
  {
    Lock();
    _flButtonEvent evnt;
    evnt.id = buttonID;
    evnt.pressed = pressed;
    evnt.timestamp = timestamp < 0 ? clock() : timestamp;
    Impl()->m_buttonEvents.push_back(evnt);
    Unlock();
  }

  void InputDeviceServer::SendEvent(flIN int64_t analogID, flIN float value, flIN bool addValue, flIN int64_t timestamp)
  {
    Lock();
    _flAnalogEvent evnt;
    evnt.id = analogID;
    evnt.value = value;
    evnt.addValue = addValue;
    evnt.timestamp = timestamp < 0 ? clock() : timestamp;
    Impl()->m_analogEvents.push_back(evnt);
    Unlock();
  }
}
