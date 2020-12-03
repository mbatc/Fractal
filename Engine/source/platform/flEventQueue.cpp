#include "platform/flEventQueue.h"
#include "atPool.h"
#include <mutex>

using namespace flEngine;
using namespace flEngine::Platform;

// TODO: Add thread-safety features

class flEngine::Platform::Impl_EventQueue;

static atPool<Impl_EventQueue*> _eventQueues;
static std::mutex _eventQueueLock;

namespace flEngine
{
  namespace Platform
  {
    class Impl_EventQueue
    {
    public:
      Impl_EventQueue()
      {
        _eventQueueLock.lock();
        m_queueID = _eventQueues.Add(0);
        _eventQueues[m_queueID] = this;
        _eventQueueLock.unlock();
      }

      ~Impl_EventQueue()
      {
        Clear();
        _eventQueueLock.lock();
        _eventQueues.erase(m_queueID);
        _eventQueueLock.unlock();
      }

      void SetFilter(EventType type)
      {
        m_eventFilter = type;
      }

      void SetFilter(bool (*FilterFunc)(Event *, void *), void *pUserData)
      {
        m_FilterFunc = FilterFunc;
        m_pFilterUserData = pUserData;
      }

      bool PeekEvent(Event *pEvent)
      {
        if (m_events.size() == 0)
          return false;
        memcpy(pEvent, &m_events.front(), sizeof(Event));
        return true;
      }

      bool NextEvent(Event *pEvent)
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

      bool PostEvent(Event *pEvent)
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

      void SetEventCallback(flIN void(*EventHandler)(Event *, void *), void *pUserData)
      {
        m_EventHandler = EventHandler;
        m_pHandlerUserData = pUserData;
      }

      int64_t GetEventCount() const
      {
        return m_events.size();
      }

      void Clear()
      {
        Event e;
        while (NextEvent(&e));
      }

    protected:
      // Queue info
      int64_t m_queueID = -1;

      // Event data
      atVector<Event> m_events;
      Event m_lastEvent = { 0 };
      bool m_hasLastEvent = false;

      // Filtering
      EventType m_eventFilter = E_Type_All;
      bool(*m_FilterFunc)(Event *, void *) = nullptr;
      void *m_pFilterUserData = nullptr;

      // Event handler callback
      void(*m_EventHandler)(Event *, void *) = nullptr;
      void *m_pHandlerUserData = nullptr;
    };
  }
}

// Implement PIMPL idiom
flPIMPL_IMPL(EventQueue)

// Help macro to access the implementation
#define flIMPL flPIMPL(EventQueue)

bool EventQueue::PostGlobalEvent(flIN Event *pEvent)
{
  bool wasReceived = false;
  _eventQueueLock.lock();
  for (Impl_EventQueue *pQueue : _eventQueues)
    wasReceived |= pQueue->PostEvent(pEvent);
  _eventQueueLock.unlock();
  return wasReceived;
}

// Forward calls to implementation

void EventQueue::SetFilter(flIN EventType type)
{
  flIMPL->SetFilter(type);
}

void EventQueue::SetFilter(flIN bool (*FilterFunc)(Event *, void *), void *pUserData)
{
  flIMPL->SetFilter(FilterFunc, pUserData);
}

bool EventQueue::PeekEvent(flOUT Event *pEvent) const
{
  return flIMPL->PeekEvent(pEvent);
}

void EventQueue::SetEventCallback(flIN void(*EventHandler)(Event *, void *), void *pUserData)
{
  flIMPL->SetEventCallback(EventHandler, pUserData);
}

bool EventQueue::NextEvent(flOUT Event *pEvent)
{
  return flIMPL->NextEvent(pEvent);
}

bool EventQueue::PostEvent(flIN Event *pEvent)
{
  return flIMPL->PostEvent(pEvent);
}

int64_t EventQueue::GetEventCount() const
{
  return flIMPL->GetEventCount();
}

void EventQueue::Clear()
{
  flIMPL->Clear();
}
