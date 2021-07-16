#include "flEventQueue.h"
#include "ctPool.h"
#include <mutex>

static ctPool<Fractal::IEventQueue*> _eventQueues;
static std::mutex _eventQueueLock;

namespace Fractal
{
  namespace Impl
  {
    EventQueue::EventQueue()
    {
      _eventQueueLock.lock();
      m_queueID = _eventQueues.Add(0);
      _eventQueues[m_queueID] = this;
      _eventQueueLock.unlock();
    }

    EventQueue::~EventQueue()
    {
      Clear();
      _eventQueueLock.lock();
      _eventQueues.erase(m_queueID);
      _eventQueueLock.unlock();
    }

    void EventQueue::SetFilter(EventType type)
    {
      m_eventFilter = type;
    }

    void EventQueue::SetFilter(bool (*FilterFunc)(Event*, void*), void* pUserData)
    {
      m_FilterFunc = FilterFunc;
      m_pFilterUserData = pUserData;
    }

    bool EventQueue::PeekEvent(Event* pEvent) const
    {
      if (m_events.size() == 0)
        return false;
      memcpy(pEvent, &m_events.front(), sizeof(Event));
      return true;
    }

    bool EventQueue::NextEvent(Event* pEvent)
    {
      if (m_hasLastEvent)
      {
        Event_Destroy(&m_lastEvent);
        m_hasLastEvent = false;
      }

      if (!PeekEvent(pEvent))
        return false;

      PeekEvent(&m_lastEvent);
      m_hasLastEvent = true;

      m_events.pop_front();
      return true;
    }

    bool EventQueue::PostEvent(Event* pEvent)
    {
      if ((pEvent->type & m_eventFilter) == 0 || (m_FilterFunc && !m_FilterFunc(pEvent, m_pFilterUserData)))
        return false;

      if (m_EventHandler)
      {
        m_EventHandler(pEvent, m_pHandlerUserData);
      }
      else
      {
        m_events.emplace_back();
        memcpy(&m_events.back(), pEvent, sizeof(Event));
      }

      return true;
    }

    void EventQueue::SetEventCallback(flIN void(*EventHandler)(Event*, void*), void* pUserData)
    {
      m_EventHandler = EventHandler;
      m_pHandlerUserData = pUserData;
    }

    int64_t EventQueue::GetEventCount() const
    {
      return m_events.size();
    }

    void EventQueue::Clear()
    {
      Event e;
      while (NextEvent(&e));
    }
  }
}

flEXPORT bool flCCONV Fractal_PostGlobalEvent(flIN Fractal::Event* pEvent)
{
  bool wasReceived = false;
  _eventQueueLock.lock();
  for (Fractal::IEventQueue* pQueue : _eventQueues)
    wasReceived |= pQueue->PostEvent(pEvent);
  _eventQueueLock.unlock();
  return wasReceived;
}
