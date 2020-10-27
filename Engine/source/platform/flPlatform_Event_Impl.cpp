#include "flPlatform_Event_Impl.h"

using namespace flEngine::Platform;

flEngine::Platform::Impl_Event::Impl_Event(const int64_t &id, const int64_t &type, const NativeEvent &_event)
  : m_eventID(id)
  , m_eventType(type)
  , m_rawEvent(_event)
{}

int64_t Impl_Event::GetEventID() const
{
  return m_eventID;
}

int64_t Impl_Event::GetEventType() const
{
  return m_eventType;
}

const NativeEvent* Impl_Event::GetNativeEvent() const
{
  return &m_rawEvent;
}
