#include "platform/flPlatform_EventQueue.h"
#include "atPool.h"
#include <type_traits>

using namespace flEngine::Platform;

// TODO: Add thread-safety features

class flEngine::Platform::Impl_EventQueue;

static atPool<Impl_EventQueue*> _eventQueues;

namespace flEngine
{
  namespace Platform
  {
    class Impl_EventQueue
    {
    public:
      Impl_EventQueue()
      {
        m_queueID = _eventQueues.Add(0);
        _eventQueues[m_queueID] = this;
      }

      ~Impl_EventQueue()
      {
        Clear();
        _eventQueues.erase(m_queueID);
      }

      void SetFilter(EventType type)
      {
        m_eventFilter = type;
      }

      void SetFilter(bool (*FilterFunc)(Event *))
      {
        m_FilterFunc = FilterFunc;
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
        if ((pEvent->type & m_eventFilter) == 0 || (m_FilterFunc && !m_FilterFunc(pEvent)))
          return false;

        m_events.emplace_back();
        memcpy(&m_events.back(), pEvent, sizeof(Event));
        return true;
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
      bool (*m_FilterFunc)(Event *) = nullptr;
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
  for (Impl_EventQueue *pQueue : _eventQueues)
    wasReceived |= pQueue->PostEvent(pEvent);
  return wasReceived;
}

// Forward calls to implementation

void EventQueue::SetFilter(flIN EventType type)
{
  flIMPL->SetFilter(type);
}

void EventQueue::SetFilter(flIN bool (*FilterFunc)(Event *))
{
  flIMPL->SetFilter(FilterFunc);
}

bool EventQueue::PeekEvent(flOUT Event *pEvent) const
{
  return flIMPL->PeekEvent(pEvent);
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
