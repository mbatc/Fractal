#ifndef flPlatform_Window_h__
#define flPlatform_Window_h__

#include "../flInterface.h"

namespace flEngine
{
  namespace Platform
  {
    class flEXPORT Window : public flEngine::Interface
    {
    public:
      /**
       * @brief Create a new window.
       *
       * Constructs a new OS window.
       */
      static Window* flCCONV Create();
    };
  }
}

#endif // flPlatform_Window_h__
