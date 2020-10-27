#ifndef flPlatform_EventQueue_h__
#define flPlatform_EventQueue_h__

#include "flPlatform_Event.h"

namespace flEngine
{
  namespace Platform
  {
    class flEXPORT EventQueue : public Interface
    {
    public:
      /**
      * @brief Create a system event queue.
      *
      * The system event queue can be used to receive events from the operating
      * system. Each event queue instance is independent of others, meaning OS
      * events will be forwarded individually to every Events instance.
      */
      static EventQueue* flCCONV Create();

      /**
      * @brief Set a filter for this event queue.
      *
      * This will only allow events of the specified type to be added to this
      * event queue. Event types can be combined to allow more than 1 or more
      * types.
      */
      virtual void SetFilter() = 0;

      /**
      * @brief Get the next event without removing it from the queue.
      *
      */
      virtual bool PeekEvent() = 0;

      /**
      * @brief Get the next event and remove it from the queue.
      *
      */
      virtual bool NextEvent() = 0;
    };
  }
}

#endif // flPlatform_EventQueue_h__
