#ifndef flPlatform_Event_h__
#define flPlatform_Event_h__

#include "../flInterface.h"

namespace flEngine
{
  namespace Platform
  {
    class flEXPORT Event : public Interface
    {
    public:
      /**
       * 
       */
      static Event* flCCONV Create(const int64_t &type, const int64_t &eventID);

      virtual int64_t GetType() = 0;
      virtual int64_t GetEventID() = 0;
    };
  }
}

#endif // flPlatform_Event_h__
