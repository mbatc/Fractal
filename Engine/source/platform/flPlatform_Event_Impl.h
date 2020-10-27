#ifndef flPlatform_Event_Impl_h__
#define flPlatform_Event_Impl_h__

#include "flPlatform_Event.h"

namespace flEngine
{
  namespace Platform
  {
    class Impl_Event : public Event
    {
    public:
      /**
       * @brief Construct an Impl_Event instance.
       * 
       * Construct the implementation of the Event class.
       */
      Impl_Event(const int64_t &id, const int64_t &type, const NativeEvent &_event);

      // Functions from Event interface
      virtual int64_t GetEventID() const override;
      virtual int64_t GetEventType() const override;
      virtual const NativeEvent* GetNativeEvent() const override;

    protected:
      int64_t m_eventID;
      int64_t m_eventType;
      NativeEvent m_rawEvent;
    };
  }
}

#endif // flPlatform_Event_Impl_h__
