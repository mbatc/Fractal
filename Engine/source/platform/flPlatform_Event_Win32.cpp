#include "flPlatform_Event.h"

#if flUSING(flPLATFORM_WINDOWS)

#include <windows.h>

using namespace flEngine::Platform;

// Event interface factory function
// This function will translate NativeEvent's to Fractal engine events
void flCCONV Event_Create(flOUT Event *pEvent, flIN NativeEvent *pNativeEvent)
{
  memset(pEvent, 0, sizeof(Event));

  int64_t mouseUp = -1;
  int64_t mouseDown = -1;

  switch (pNativeEvent->msg)
  {
    // System Events
  case WM_QUIT:
    pEvent->type = E_Type_System;
    pEvent->id = E_Sys_Quit;
    pEvent->sysQuit.code = pNativeEvent->wParam;
    break;

  case WM_THEMECHANGED:
    pEvent->type = E_Type_System;
    pEvent->id = E_Sys_ThemeChanged;
    break;

    // Window Events
  case WM_CREATE:
    pEvent->type = E_Type_Window;
    pEvent->id = E_Wnd_Create;
    break;

  case WM_CLOSE:
    pEvent->type = E_Type_Window;
    pEvent->id = E_Wnd_Close;
    break;

  case WM_DESTROY:
    pEvent->type = E_Type_Window;
    pEvent->id = E_Wnd_Destroy;
    break;

  case WM_DPICHANGED:
    pEvent->type = E_Type_Window;
    pEvent->id = E_Wnd_DpiChanged;
    break;

  case WM_MOVING:
    pEvent->type = E_Type_Window;
    pEvent->id = E_Wnd_Moving;
    break;

  case WM_SIZING:           
    pEvent->type = E_Type_Window;
    pEvent->id = E_Wnd_Sizing;
    break;

  case WM_SHOWWINDOW:       
    pEvent->type = E_Type_Window;
    pEvent->id = E_Wnd_Show;
    break;

  case WM_STYLECHANGED:
    pEvent->type = E_Type_Window;
    pEvent->id = E_Wnd_StyleChanged;
    break;

  case WM_WINDOWPOSCHANGED:
    pEvent->type = E_Type_Window;
    pEvent->id = E_Wnd_RectUpdated;
    break;

  case WM_MOUSEACTIVATE: pEvent->wndActive.mouseActivated = true;
  case WM_ACTIVATE:      // fall-through
    pEvent->type = E_Type_Window;
    pEvent->id = E_Wnd_Activate;
    pEvent->wndActive.isActive;
    break;

    // Keyboard Events
  case WM_KEYDOWN:
    pEvent->type = E_Type_Keyboard;
    pEvent->id = E_Wnd_Activate;
    break;

  case WM_KEYUP:       
    pEvent->type = E_Type_Keyboard;
    pEvent->id = E_Wnd_Activate;
    break;

  case WM_CHAR:
    pEvent->type = E_Type_Keyboard;
    pEvent->id = E_Wnd_Activate;
    break;

  case WM_UNICHAR:
    pEvent->type = E_Type_Keyboard;
    pEvent->id = E_Wnd_Activate;
    break;

  case WM_KILLFOCUS:
    pEvent->type = E_Type_Keyboard;
    pEvent->id = E_Wnd_Activate;
    break;

  case WM_SETFOCUS:
    pEvent->type = E_Type_Keyboard;
    pEvent->id = E_Wnd_Activate;
    break;


    // Mouse Events
  case WM_MOUSEHWHEEL: pEvent->mseScroll.isHorizontal = true;
  case WM_MOUSEWHEEL:  // fall-through
    pEvent->type = E_Type_Mouse;
    pEvent->id = E_Mse_Scroll;
    break;

  case WM_MOUSEMOVE:
    pEvent->type = E_Type_Mouse;
    pEvent->id = E_Mse_Move;
    break;

  case WM_XBUTTONDOWN:  mouseDown = 0; break;
  case WM_LBUTTONDOWN:  mouseDown = 1; break;
  case WM_RBUTTONDOWN:  mouseDown = 2; break;
  case WM_MBUTTONDOWN:  mouseDown = 3; break;
  case WM_LBUTTONUP:    mouseUp = 0; break;
  case WM_RBUTTONUP:    mouseUp = 1; break;
  case WM_MBUTTONUP:    mouseUp = 2; break;
  case WM_XBUTTONUP:    mouseUp = 3; break;
  }

  if (mouseUp != -1)
  {
    pEvent->type = E_Type_Mouse;
    pEvent->id = E_Mse_State;
    pEvent->mseState.button = mouseUp;
    pEvent->mseState.isDown = false;
  }

  if (mouseDown != -1)
  {
    pEvent->type = E_Type_Mouse;
    pEvent->id = E_Mse_State;
    pEvent->mseState.button = mouseDown;
    pEvent->mseState.isDown = true;
  }
}

#endif
