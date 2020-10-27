#ifndef flPlatform_EventQueue_Impl_h__
#define flPlatform_EventQueue_Impl_h__

#include "flPlatform_EventQueue.h"
#include "atVector.h"

namespace flEngine
{
  namespace Platform
  {
    class Impl_EventQueue : public EventQueue
    {
    public:
      Impl_EventQueue();
      ~Impl_EventQueue();

      virtual void SetFilter(EventType type) override;
      virtual bool PeekEvent(Event **ppEvent) override;
      virtual bool NextEvent(Event **ppEvent) override;
      virtual bool PostEvent(Event *pEvent) override;

    protected:
      atVector<Event*> m_events;
      int64_t m_queueID = -1;
      EventType m_eventFilter = E_Type_All;
    };
  }
}

#endif // flPlatform_EventQueue_Impl_h__
