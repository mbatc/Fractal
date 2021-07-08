#include "flEvent.h"
#include "flKeyboard.h"

#if flUSING(flPLATFORM_WINDOWS)

#include <windows.h>
#include <windowsx.h>
#include "flMouse.h"

namespace Fractal
{
  static int64_t _TranslateKeyCode(int64_t winKey);

  // Event interface factory function
  // This function will translate NativeEvent's to Fractal engine events
  void flCCONV Event_Create(flOUT Event* pEvent, flIN NativeEvent* pNativeEvent)
  {
    memset(pEvent, 0, sizeof(Event));

    int64_t mouseUp = -1;
    int64_t mouseDown = -1;

    pEvent->nativeEvent = *pNativeEvent;

    switch (pNativeEvent->msg)
    {
    // System Events
    case WM_QUIT:
    {
      pEvent->type = E_Type_System;
      pEvent->id = E_Sys_Quit;
      pEvent->sysQuit.code = pNativeEvent->wParam;
    }
    break;

    case WM_THEMECHANGED:
    {
      pEvent->type = E_Type_System;
      pEvent->id = E_Sys_ThemeChanged;
    }
    break;

    // Window Events
    case WM_CREATE:
    {
      pEvent->type = E_Type_Window;
      pEvent->id = E_Wnd_Create;
      CREATESTRUCT* pCreateInfo = (CREATESTRUCT*)pNativeEvent->lParam;

      pEvent->wndCreate.width = pCreateInfo->cx;
      pEvent->wndCreate.height = pCreateInfo->cy;
      pEvent->wndCreate.x = pCreateInfo->x;
      pEvent->wndCreate.y = pCreateInfo->y;
      pEvent->wndCreate.name = nullptr;
    }
    break;

    case WM_CLOSE:
    {
      pEvent->type = E_Type_Window;
      pEvent->id = E_Wnd_Close;
    }
    break;

    case WM_DESTROY:
    {
      pEvent->type = E_Type_Window;
      pEvent->id = E_Wnd_Destroy;
    }
    break;

    case WM_DPICHANGED:
    {
      pEvent->type = E_Type_Window;
      pEvent->id = E_Wnd_DpiChanged;
      pEvent->wndDpiChanged.dpiX = HIWORD(pNativeEvent->wParam);
      pEvent->wndDpiChanged.dpiY = LOWORD(pNativeEvent->wParam);

      RECT* pRect = (RECT*)pNativeEvent->lParam;
      pEvent->wndDpiChanged.suggestedHeight = pRect->bottom - pRect->top;
      pEvent->wndDpiChanged.suggestedWidth = pRect->right - pRect->left;
      pEvent->wndDpiChanged.suggestedX = pRect->left;
      pEvent->wndDpiChanged.suggestedY = pRect->top;
    }
    break;

    case WM_MOVING:
    {
      pEvent->type = E_Type_Window;
      pEvent->id = E_Wnd_Moving;

      RECT* pRect = (RECT*)pNativeEvent->lParam;
      pEvent->wndMoving.x = pRect->left;
      pEvent->wndMoving.y = pRect->top;
    }
    break;

    case WM_SIZING:
    {
      pEvent->type = E_Type_Window;
      pEvent->id = E_Wnd_Sizing;

      RECT* pRect = (RECT*)pNativeEvent->lParam;
      pEvent->wndSizing.width = pRect->right - pRect->left;
      pEvent->wndSizing.height = pRect->bottom - pRect->top;
    }
    break;

    case WM_SHOWWINDOW:
    {
      pEvent->type = E_Type_Window;
      pEvent->id = E_Wnd_Show;

      pEvent->wndShow.isShown = pNativeEvent->wParam > 0;
    }
    break;

    case WM_STYLECHANGED:
    {
      pEvent->type = E_Type_Window;
      pEvent->id = E_Wnd_StyleChanged;

      STYLESTRUCT* pStyle = (STYLESTRUCT*)pNativeEvent->lParam;
      pEvent->wndStyleChanged.newStyle = pStyle->styleNew;
      pEvent->wndStyleChanged.oldStyle = pStyle->styleOld;
    }
    break;

    case WM_WINDOWPOSCHANGED:
    {
      pEvent->type = E_Type_Window;
      pEvent->id = E_Wnd_RectUpdated;

      WINDOWPOS* pPos = (WINDOWPOS*)pNativeEvent->lParam;
      pEvent->wndRectUpdated.x = pPos->x;
      pEvent->wndRectUpdated.y = pPos->y;
      pEvent->wndRectUpdated.width = pPos->cx;
      pEvent->wndRectUpdated.height = pPos->cy;
    }
    break;

    case WM_MOUSEACTIVATE:
      pEvent->wndActive.mouseActivated = true;
    case WM_ACTIVATE: // fall-through
    {
      pEvent->type = E_Type_Window;
      pEvent->id = E_Wnd_Activate;
      pEvent->wndActive.isActive = LOWORD(pNativeEvent->wParam) > 0;
      pEvent->wndActive.mouseActivated |= HIWORD(pNativeEvent->wParam) == WA_CLICKACTIVE;
    }
    break;

    // Keyboard Events
    case WM_KEYDOWN:
      pEvent->kbdState.isDown = true;
    case WM_KEYUP:
    {
      pEvent->type = E_Type_Keyboard;
      pEvent->id = E_Kbd_KeyState;
      pEvent->kbdState.keyCode = _TranslateKeyCode(pNativeEvent->wParam);
    }
    break;

    case WM_CHAR:
    {
      pEvent->type = E_Type_Keyboard;
      pEvent->id = E_Kbd_ASCII;
      pEvent->kbdASCII.character = pNativeEvent->wParam;
    }
    break;

    case WM_KILLFOCUS:
    {
      pEvent->type = E_Type_Keyboard;
      pEvent->id = E_Kbd_KillFocus;
    }
    break;

    case WM_SETFOCUS:
    {
      pEvent->type = E_Type_Keyboard;
      pEvent->id = E_Kbd_SetFocus;
    }
    break;

    // Mouse Events
    case WM_MOUSEHWHEEL:
      pEvent->mseScroll.isHorizontal = true;
    case WM_MOUSEWHEEL: // fall-through
    {
      pEvent->type = E_Type_Mouse;
      pEvent->id = E_Mse_Scroll;
      pEvent->mseScroll.amount = GET_WHEEL_DELTA_WPARAM(pNativeEvent->wParam) / (float)WHEEL_DELTA;
    }
    break;

    case WM_MOUSEMOVE:
    {
      pEvent->type = E_Type_Mouse;
      pEvent->id = E_Mse_Move;
      pEvent->mseMove.wndX = GET_X_LPARAM(pNativeEvent->lParam);
      pEvent->mseMove.wndY = GET_Y_LPARAM(pNativeEvent->lParam);

      POINT pnt;
      pnt.x = (LONG)pEvent->mseMove.wndX;
      pnt.y = (LONG)pEvent->mseMove.wndY;
      ClientToScreen((HWND)pEvent->nativeEvent.hWnd, &pnt);
      pEvent->mseMove.screenX = pnt.x;
      pEvent->mseMove.screenY = pnt.y;
    }
    break;

    case WM_LBUTTONDOWN:
      mouseDown = MB_Left;
      break;
    case WM_RBUTTONDOWN:
      mouseDown = MB_Right;
      break;
    case WM_MBUTTONDOWN:
      mouseDown = MB_Middle;
      break;
    case WM_XBUTTONDOWN:
      mouseDown = 3;
      break;
    case WM_LBUTTONUP:
      mouseUp = MB_Left;
      break;
    case WM_RBUTTONUP:
      mouseUp = MB_Right;
      break;
    case WM_MBUTTONUP:
      mouseUp = MB_Middle;
      break;
    case WM_XBUTTONUP:
      mouseUp = 3;
      break;
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

  static int64_t _TranslateKeyCode(int64_t winKey)
  {
    switch (winKey)
    {
    case VK_BACK:
      return KC_Backspace;
    case VK_TAB:
      return KC_Tab;
    case VK_RETURN:
      return KC_Return;
    case VK_SHIFT:
      return KC_Shift;
    case VK_CONTROL:
      return KC_Control;
    case VK_MENU:
      return KC_Alt;
    case VK_PAUSE:
      return KC_PauseBreak;
    case VK_CAPITAL:
      return KC_CapsLock;
    case VK_ESCAPE:
      return KC_Escape;
    case VK_SPACE:
      return KC_Space;
    case VK_PRIOR:
      return KC_PageUp;
    case VK_NEXT:
      return KC_PageDown;
    case VK_END:
      return KC_End;
    case VK_HOME:
      return KC_Home;
    case VK_LEFT:
      return KC_Left;
    case VK_RIGHT:
      return KC_Right;
    case VK_UP:
      return KC_Up;
    case VK_DOWN:
      return KC_Down;
    case VK_SNAPSHOT:
      return KC_PrintScreen;
    case VK_INSERT:
      return KC_Insert;
    case VK_DELETE:
      return KC_Delete;
    case VK_NUMPAD0:
      return KC_Numpad0;
    case VK_NUMPAD1:
      return KC_Numpad1;
    case VK_NUMPAD2:
      return KC_Numpad2;
    case VK_NUMPAD3:
      return KC_Numpad3;
    case VK_NUMPAD4:
      return KC_Numpad4;
    case VK_NUMPAD5:
      return KC_Numpad5;
    case VK_NUMPAD6:
      return KC_Numpad6;
    case VK_NUMPAD7:
      return KC_Numpad7;
    case VK_NUMPAD8:
      return KC_Numpad8;
    case VK_NUMPAD9:
      return KC_Numpad9;
    case VK_F1:
      return KC_F1;
    case VK_F2:
      return KC_F2;
    case VK_F3:
      return KC_F3;
    case VK_F4:
      return KC_F4;
    case VK_F5:
      return KC_F5;
    case VK_F6:
      return KC_F6;
    case VK_F7:
      return KC_F7;
    case VK_F8:
      return KC_F8;
    case VK_F9:
      return KC_F9;
    case VK_F10:
      return KC_F10;
    case VK_F11:
      return KC_F11;
    case VK_F12:
      return KC_F12;
    case '0':
      return KC_0;
    case '1':
      return KC_1;
    case '2':
      return KC_2;
    case '3':
      return KC_3;
    case '4':
      return KC_4;
    case '5':
      return KC_5;
    case '6':
      return KC_6;
    case '7':
      return KC_7;
    case '8':
      return KC_8;
    case '9':
      return KC_9;
    case 'A':
      return KC_A;
    case 'B':
      return KC_B;
    case 'C':
      return KC_C;
    case 'D':
      return KC_D;
    case 'E':
      return KC_E;
    case 'F':
      return KC_F;
    case 'G':
      return KC_G;
    case 'H':
      return KC_H;
    case 'I':
      return KC_I;
    case 'J':
      return KC_J;
    case 'K':
      return KC_K;
    case 'L':
      return KC_L;
    case 'M':
      return KC_M;
    case 'N':
      return KC_N;
    case 'O':
      return KC_O;
    case 'P':
      return KC_P;
    case 'Q':
      return KC_Q;
    case 'R':
      return KC_R;
    case 'S':
      return KC_S;
    case 'T':
      return KC_T;
    case 'U':
      return KC_U;
    case 'V':
      return KC_V;
    case 'W':
      return KC_W;
    case 'X':
      return KC_X;
    case 'Y':
      return KC_Y;
    case 'Z':
      return KC_Z;
    case VK_OEM_COMMA:
      return KC_Comma;
    case VK_OEM_MINUS:
      return KC_Minus;
    case VK_SUBTRACT:
      return KC_NumpadMinus;
    case VK_DECIMAL:
      return KC_NumpadDecimal;
    case VK_DIVIDE:
      return KC_NumpadDivide;
    case VK_ADD:
      return KC_NumpadAdd;
    case VK_MULTIPLY:
      return KC_NumpadMultiply;
    case VK_OEM_PERIOD:
      return KC_Period;
    case VK_VOLUME_UP:
      return KC_VolumeUp;
    case VK_VOLUME_DOWN:
      return KC_VolumeDown;
    case VK_VOLUME_MUTE:
      return KC_Mute;
    case VK_MEDIA_PLAY_PAUSE:
      return KC_PlayPause;
    case VK_MEDIA_NEXT_TRACK:
      return KC_NextTrack;
    case VK_MEDIA_PREV_TRACK:
      return KC_PrevTrack;
    case VK_MEDIA_STOP:
      return KC_Stop;
    case VK_OEM_PLUS:
      return KC_Equals;
    case VK_OEM_2:
      return KC_ForwardSlash;
    case VK_OEM_1:
      return KC_SemiColon;
    case VK_OEM_3:
      return KC_Apostraphe;
    case VK_OEM_4:
      return KC_OpenSqrBracket;
    case VK_OEM_5:
      return KC_BackSlash;
    case VK_OEM_6:
      return KC_CloseSqrBracket;
    case VK_OEM_7:
      return KC_Quote;
    case VK_LSHIFT:
      return KC_LShift;
    case VK_RSHIFT:
      return KC_RShift;
    case VK_LCONTROL:
      return KC_LControl;
    case VK_RCONTROL:
      return KC_RControl;
    case VK_LMENU:
      return KC_LAlt;
    case VK_RMENU:
      return KC_RAlt;
    }

    return KC_Unknown;
  }
}

#endif
