#pragma once

#include "flIEventQueue.h"

namespace Fractal
{
  namespace Impl
  {
    class EventQueue : public IEventQueue
    {
      FRACTAL_DEFAULT_INTERFACE;

    public:
      EventQueue();
      ~EventQueue();

      virtual void SetFilter(EventType type) override;
      virtual void SetFilter(bool (*FilterFunc)(Event*, void*), void* pUserData) override;
      virtual bool PeekEvent(Event* pEvent) const override;
      virtual bool NextEvent(Event* pEvent) override;
      virtual bool PostEvent(Event* pEvent) override;
      virtual void SetEventCallback(flIN void(*EventHandler)(Event*, void*), void* pUserData) override;
      virtual int64_t GetEventCount() const override;
      virtual void Clear() override;

    protected:
      // Queue info
      int64_t m_queueID = -1;

      // Event data
      ctVector<Event> m_events;
      Event m_lastEvent = { 0 };
      bool m_hasLastEvent = false;

      // Filtering
      EventType m_eventFilter = E_Type_All;
      bool(*m_FilterFunc)(Event*, void*) = nullptr;
      void* m_pFilterUserData = nullptr;

      // Event handler callback
      void(*m_EventHandler)(Event*, void*) = nullptr;
      void* m_pHandlerUserData = nullptr;
    };
  }
}