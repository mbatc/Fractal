#ifndef flPlatform_Event_h__
#define flPlatform_Event_h__

#include "../flInterface.h"

namespace flEngine
{
  namespace Platform
  {
    /**
     * @brief System Event base class.
     *
     * This class is the base for all system events.
     */
    class flEXPORT Event : public Interface
    {
    public:
      static Event* Create();

      virtual int64_t GetType() = 0;

      virtual void* GetData() = 0;

      template<typename T
    };
  }
}

#endif // flPlatform_EventQueue_h__
