#ifndef flPlatform_NativeEvent_h__
#define flPlatform_NativeEvent_h__

#include "flConfig.h"

namespace flEngine
{
  namespace Platform
  {
    struct NativeEvent
    {
#if flUSING(flPLATFORM_WINDOWS)
      void *hWnd;
      uint32_t msg;
      uint32_t wParam;
      void* lParam;
      uint32_t time;
      uint32_t cursorX;
      uint32_t cursorY;
#endif

#if flUSING(flPLATFORM_LINUX)

#endif
    };
  }
}

#endif // flPlatform_NativeEvent_h__
