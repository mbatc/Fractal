#ifndef fl_Platform_NativeEvent_h__
#define fl_Platform_NativeEvent_h__

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
      void *lParam;
#endif

#if flUSING(flPLATFORM_LINUX)

#endif
    };
  }
}

#endif // fl_Platform_NativeEvent_h__
