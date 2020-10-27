#include "flPlatform_EventQueue_Impl.h"
#include "atPool.h"

using namespace flEngine::Platform;

// TODO: Add thread-safety features

static atPool<EventQueue*> _eventQueues;

EventQueue* EventQueue::Create() { return flNew Impl_EventQueue; }

bool EventQueue::PostGlobalEvent(Event *pEvent)
{
  bool wasReceived = false;
  for (EventQueue *pQueue : _eventQueues)
    wasReceived |= pQueue->PostEvent(pEvent);
  return wasReceived;
}

flEngine::Platform::Impl_EventQueue::Impl_EventQueue()
{
  m_queueID = _eventQueues.Add(this);
}

flEngine::Platform::Impl_EventQueue::~Impl_EventQueue()
{
  _eventQueues.erase(m_queueID);
}

void flEngine::Platform::Impl_EventQueue::SetFilter(EventType type)
{
  m_eventFilter = type;
}

bool flEngine::Platform::Impl_EventQueue::PeekEvent(Event **ppEvent)
{
  if (m_events.size() == 0)
    return false;

  *ppEvent = m_events.front();
  (*ppEvent)->IncRef(); // add reference for the caller
  return true;
}

bool flEngine::Platform::Impl_EventQueue::NextEvent(Event **ppEvent)
{
  if (m_events.size() == 0)
    return false;

  // Don't decrement the reference as we are handing it off to the caller
  *ppEvent = m_events.front();
  m_events.pop_front();
  return true;
}

bool flEngine::Platform::Impl_EventQueue::PostEvent(Event *pEvent)
{
  if ((pEvent->GetEventType() & m_eventFilter) == 0)
    return false;

  pEvent->IncRef(); // take a reference and add it to the queue
  m_events.push_back(pEvent);
  return true;
}
