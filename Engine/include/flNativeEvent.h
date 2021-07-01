#pragma once

#include "flConfig.h"

namespace Fractal
{
  struct NativeEvent
  {
#if flUSING(flPLATFORM_WINDOWS)
    void* hWnd;
    uint32_t msg;
    uint32_t wParam;
    void* lParam;
#endif

#if flUSING(flPLATFORM_LINUX)

#endif
  };
}
