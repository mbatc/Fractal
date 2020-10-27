#include "flPlatform_Event_Impl.h"

#if flUSING(flPLATFORM_WINDOWS)

using namespace flEngine::Platform;

#include <windows.h>

Event* _CreateQuit(NativeEvent *pNativeEvent)
{
  return nullptr;
}

Event* _CreateThemeChanged(NativeEvent *pNativeEvent)
{
  return nullptr;
}

Event* _CreateCreate(NativeEvent *pNativeEvent)
{
  return nullptr;
}

Event* _CreateClose(NativeEvent *pNativeEvent)
{
  return nullptr;
}

Event* _CreateDestroy(NativeEvent *pNativeEvent)
{
  return nullptr;
}

Event* _CreateDpiChanged(NativeEvent *pNativeEvent)
{
  return nullptr;
}

Event* _CreateMoving(NativeEvent *pNativeEvent)
{
  return nullptr;
}

Event* _CreateSizing(NativeEvent *pNativeEvent)
{
  return nullptr;
}

Event* _CreateShowWindow(NativeEvent *pNativeEvent)
{
  return nullptr;
}

Event* _CreateStyleChanged(NativeEvent *pNativeEvent)
{
  return nullptr;
}

Event* _CreateWindowPosChanged(NativeEvent *pNativeEvent)
{
  return nullptr;
}

Event* _CreateActivate(NativeEvent *pNativeEvent)
{
  return nullptr;
}

Event* _CreateMouseActivate(NativeEvent *pNativeEvent)
{
  return nullptr;
}

Event* _CreateKeyDown(NativeEvent *pNativeEvent)
{
  return nullptr;
}

Event* _CreateKeyUp(NativeEvent *pNativeEvent)
{
  return nullptr;
}

Event* _CreateChar(NativeEvent *pNativeEvent)
{
  return nullptr;
}

Event* _CreateUniChar(NativeEvent *pNativeEvent)
{
  return nullptr;
}

Event* _CreateKillFocus(NativeEvent *pNativeEvent)
{
  return nullptr;
}

Event* _CreateSetFocus(NativeEvent *pNativeEvent)
{
  return nullptr;
}

Event* _CreateMouseScroll(bool horizontal, NativeEvent *pNativeEvent)
{
  return nullptr;
}

Event* _CreateMouseMove(NativeEvent *pNativeEvent)
{
  return nullptr;
}

Event* _CreateMouseUp(int64_t msButton, NativeEvent *pNativeEvent)
{
  return nullptr;
}

Event* _CreateMouseDown(int64_t msButton, NativeEvent *pNativeEvent)
{
  return nullptr;
}


// Event interface factory function
// This function will translate NativeEvent's to Fractal engine events
Event* flCCONV Event::Create(NativeEvent *pNativeEvent)
{
  int64_t mouseUp = -1;
  int64_t mouseDown = -1;

  switch (pNativeEvent->msg)
  {
    // System Events
  case WM_QUIT:            return _CreateQuit(pNativeEvent);
  case WM_THEMECHANGED:    return _CreateThemeChanged(pNativeEvent);

    // Window Events
  case WM_CREATE:           return _CreateCreate(pNativeEvent);
  case WM_CLOSE:            return _CreateClose(pNativeEvent);
  case WM_DESTROY:          return _CreateDestroy(pNativeEvent);
  case WM_DPICHANGED:       return _CreateDpiChanged(pNativeEvent);
  case WM_MOVING:           return _CreateMoving(pNativeEvent);
  case WM_SIZING:           return _CreateSizing(pNativeEvent);
  case WM_SHOWWINDOW:       return _CreateShowWindow(pNativeEvent);
  case WM_STYLECHANGED:     return _CreateStyleChanged(pNativeEvent);
  case WM_WINDOWPOSCHANGED: return _CreateWindowPosChanged(pNativeEvent);
  case WM_ACTIVATE:         return _CreateActivate(pNativeEvent);
  case WM_MOUSEACTIVATE:    return _CreateMouseActivate(pNativeEvent);

    // Keyboard Events
  case WM_KEYDOWN:     return _CreateKeyDown(pNativeEvent);
  case WM_KEYUP:       return _CreateKeyUp(pNativeEvent);
  case WM_CHAR:        return _CreateChar(pNativeEvent);
  case WM_UNICHAR:     return _CreateUniChar(pNativeEvent);
  case WM_KILLFOCUS:   return _CreateKillFocus(pNativeEvent);
  case WM_SETFOCUS:    return _CreateSetFocus(pNativeEvent);

    // Mouse Events
  case WM_MOUSEWHEEL:  return _CreateMouseScroll(false, pNativeEvent);
  case WM_MOUSEHWHEEL: return _CreateMouseScroll(true, pNativeEvent);
  case WM_MOUSEMOVE:   return _CreateMouseMove(pNativeEvent);


  case WM_XBUTTONDOWN:  mouseDown = 0; break;
  case WM_LBUTTONDOWN:  mouseDown = 1; break;
  case WM_RBUTTONDOWN:  mouseDown = 2; break;
  case WM_MBUTTONDOWN:  mouseDown = 3; break;
  case WM_LBUTTONUP:    mouseUp = 0; break;
  case WM_RBUTTONUP:    mouseUp = 1; break;
  case WM_MBUTTONUP:    mouseUp = 2; break;
  case WM_XBUTTONUP:    mouseUp = 3; break;
  }

  if (mouseUp != -1)   return _CreateMouseUp(mouseUp, pNativeEvent);
  if (mouseDown != -1) return _CreateMouseDown(mouseDown, pNativeEvent);

  return nullptr;
}

#endif
