#include "input/flInputDeviceServer.h"
#include "threads/flThreads.h"
#include "atVector.h"
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

namespace flEngine
{
  namespace Input
  {
    class flPIMPL_CLASS(InputDeviceServer)
    {
    public:
      atVector<_flButtonEvent> m_buttonEvents;
      atVector<_flAnalogEvent> m_analogEvents;
      Threads::RecursiveMutex  m_lock;
    };
  }
}

using namespace flEngine;
using namespace flEngine::Input;

flPIMPL_IMPL(InputDeviceServer)

#define flIMPL flPIMPL(InputDeviceServer)

InputDeviceServer::InputDeviceServer() {}

InputDeviceServer* InputDeviceServer::Create()
{
  return flNew InputDeviceServer;
}

void InputDeviceServer::Lock()
{
  flIMPL->m_lock.lock();
}

void InputDeviceServer::Unlock()
{
  flIMPL->m_lock.unlock();
}

bool InputDeviceServer::GetEvent(flOUT int64_t *pButtonID, flOUT bool *pValue, flOUT int64_t *pTimestamp)
{
  Lock();
  if (flIMPL->m_buttonEvents.size() <= 0)
  {
    Unlock();
    return false;
  }

  _flButtonEvent evnt = flIMPL->m_buttonEvents.front();
  flIMPL->m_buttonEvents.pop_front();

  if (pValue)     *pValue     = evnt.pressed;
  if (pButtonID)  *pButtonID  = evnt.id;
  if (pTimestamp) *pTimestamp = evnt.timestamp;
  Unlock();
  return true;
}

bool InputDeviceServer::GetEvent(flOUT int64_t *pAnalogID, flOUT float *pValue, flOUT bool *pAddValue, flOUT int64_t *pTimestamp)
{
  Lock();
  if (flIMPL->m_analogEvents.size() <= 0)
  {
    Unlock();
    return false;
  }

  _flAnalogEvent evnt = flIMPL->m_analogEvents.front();
  flIMPL->m_analogEvents.pop_front();

  if (pValue)     *pValue = evnt.value;
  if (pAnalogID)  *pAnalogID = evnt.id;
  if (pTimestamp) *pTimestamp = evnt.timestamp;
  Unlock();
  return true;
}

void InputDeviceServer::SendEvent(flIN int64_t buttonID, flIN bool pressed, flIN int64_t timestamp)
{
  Lock();
  _flButtonEvent evnt;
  evnt.id        = buttonID;
  evnt.pressed   = pressed;
  evnt.timestamp = timestamp < 0 ? clock() : timestamp;
  flIMPL->m_buttonEvents.push_back(evnt);
  Unlock();
}

void InputDeviceServer::SendEvent(flIN int64_t analogID, flIN float value, flIN bool addValue, flIN int64_t timestamp)
{
  Lock();
  _flAnalogEvent evnt;
  evnt.id        = analogID;
  evnt.value     = value;
  evnt.addValue  = addValue;
  evnt.timestamp = timestamp < 0 ? clock() : timestamp;
  flIMPL->m_analogEvents.push_back(evnt);
  Unlock();
}
