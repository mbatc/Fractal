#include "flDisplay.h"
#include "flDisplay_Impl.h"

#if flUSING(flPLATFORM_WINDOWS)

#include <windows.h>
#include <ShellScalingApi.h>

typedef HRESULT(WINAPI* GetDpiForMonitorFunc)(HMONITOR, MONITOR_DPI_TYPE, UINT*, UINT*);

namespace Fractal
{
  static double _GetDPI(HMONITOR hMonitor)
  {
    UINT xdpi = 96, ydpi = 96;
    GetDpiForMonitor(hMonitor, MDT_EFFECTIVE_DPI, &xdpi, &ydpi);
    return xdpi / 96.0;
  }

  DisplayList* Display::EnumerateDisplays()
  {
    DisplayList* pDisplayList = flNew DisplayList;

    EnumDisplayMonitors(
      NULL, NULL,
      [](HMONITOR hMonitor, HDC, LPRECT, LPARAM lParam)
    {
      DisplayList* pDisplayList = (DisplayList*)lParam;
      MONITORINFO info = {};
      info.cbSize = sizeof(MONITORINFO);
      if (!::GetMonitorInfo(hMonitor, &info))
        return TRUE;

      Ref<Display> pDisplay = MakeRef<Display>();

      pDisplay->Impl()->position = Vec2I(info.rcMonitor.left, info.rcMonitor.top);
      pDisplay->Impl()->size = Vec2I(info.rcMonitor.right - info.rcMonitor.left, info.rcMonitor.bottom - info.rcMonitor.top);
      pDisplay->Impl()->workAreaPosition = Vec2I(info.rcWork.left, info.rcWork.top);
      pDisplay->Impl()->workAreaSize = Vec2I(info.rcWork.right - info.rcWork.left, info.rcWork.bottom - info.rcWork.top);
      pDisplay->Impl()->dpiScale = _GetDPI(hMonitor);

      pDisplay->Impl()->primary = (info.dwFlags & MONITORINFOF_PRIMARY) > 0;

      if (pDisplay->IsPrimaryMonitor())
        pDisplayList->Impl()->displays.push_front(pDisplay);
      else
        pDisplayList->Impl()->displays.push_back(pDisplay);
      return TRUE;
    },
    (LPARAM)pDisplayList);

    return pDisplayList;
  }
}

#endif
