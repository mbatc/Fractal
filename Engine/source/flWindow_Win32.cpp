#include "flWindow.h"

#if flUSING(flPLATFORM_WINDOWS)

#include "flWindowRenderTarget.h"
#include "flEventQueue.h"
#include "flThreads.h"
#include "flEvent.h"
#include "flITask.h"
#include "ctHashMap.h"
#include "ctString.h"
#include <windows.h>
#include <mutex>

namespace Fractal
{
  namespace Impl
  {
    LRESULT CALLBACK _flWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    static std::mutex _windowInitLock;
    static int64_t _windowInitCount = 0;
    static ctString _windowClsName = "FractalEngine_WindowClass";
    static ATOM _atom = 0;
    static ctHashMap<void*, IWindow*> _windowLookup;
    static IWindow* _pHoveredWindow = nullptr;

    static IWindow* _GetWindowFromHandle(HWND hWnd);

    Window::Window(const char* title, WindowFlags flags, WindowDisplayMode displayMode)
    {
      HINSTANCE hInstance = ::GetModuleHandle(NULL);

      // Setup the event filter, so we only receive events for this window
      m_pEvents->SetFilter(
        [](Event* pEvent, void* pUserData)
        {
          Window* pWnd = (Window*)pUserData;
          return pWnd->IsEventSource(pEvent) || pEvent->nativeEvent.hWnd == nullptr;
        }, this);

      // Setup the event callback
      m_pEvents->SetEventCallback(
        [](Event* pEvent, void* pUserData)
        {
          Window* pWnd = (Window*)pUserData;
          pWnd->m_receivedEvents[pEvent->id] = true;

          switch (pEvent->id)
          {
          case E_Wnd_Activate:
            if (pEvent->wndActive.isActive)
              _pHoveredWindow = pEvent->pWindow;
            else if (_pHoveredWindow == pEvent->pWindow)
              _pHoveredWindow = nullptr;
            break;
          }
        }, this);

      _windowInitLock.lock();
      if (_windowInitCount++ == 0)
      {
        // Create the window class for flEngine win32 windows
        Fractal_GetEventThread()->Add(
          MakeTask(
          [=]()
          {
            WNDCLASSEX wndCls = { 0 };
            wndCls.cbSize = sizeof(WNDCLASSEX);
            wndCls.style = 0;
            wndCls.lpfnWndProc = _flWindowProc;
            wndCls.hInstance = (HINSTANCE)hInstance;
            wndCls.hIcon = ::LoadIcon(NULL, IDI_APPLICATION);
            wndCls.hCursor = ::LoadCursor(NULL, IDC_ARROW);
            wndCls.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
            wndCls.lpszClassName = _windowClsName.c_str();

            // TODO: Add error reporting
            _atom = RegisterClassEx(&wndCls);

            return 0ll;
          }));
      }
      _windowInitLock.unlock();

      Create(title, flags, hInstance);
    }

    Window::~Window()
    {
      Destroy();

      while (!ReceivedEvent(E_Wnd_Destroy, false))
        Sleep(1);

      _windowInitLock.lock();

      if (--_windowInitCount == 0)
      {
        Fractal_GetEventThread()->Add(
          MakeTask(
          []()
          {
            UnregisterClass(_windowClsName.c_str(), ::GetModuleHandle(NULL));
            return 0ll;
          }));
      }
      _windowInitLock.unlock();
    }

    void Window::Create(const char* title, WindowFlags flags, void* hInstance)
    {
      ITask* pCreateTask = nullptr;

      // Create the window
      Fractal_GetEventThread()->Add(
        MakeTask([=]() {
          // TODO: Add error reporting
          m_hWnd = CreateWindowEx(
            WS_EX_OVERLAPPEDWINDOW,
            _windowClsName.c_str(),
            title,
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT,
            CW_USEDEFAULT, CW_USEDEFAULT,
            0,
            0,
            (HINSTANCE)hInstance,
            0);

          _windowLookup.Add(m_hWnd, this);

          int show = SW_HIDE;

          ::UpdateWindow((HWND)m_hWnd);
          if ((flags & WindowFlag_Visible) > 0)
            ::ShowWindow((HWND)m_hWnd, SW_SHOW);
          return 0ll;
        })
      );

      // Wait for the task to complete
      pCreateTask->Await();
      pCreateTask->DecRef();
    }

    void Window::DestroyWnd()
    {
      if (!m_hWnd)
        return;

      Fractal_GetEventThread()->Add(MakeTask(
        [=]()
        {
          ::DestroyWindow((HWND)m_hWnd);
          _windowLookup.Remove(m_hWnd);
          return 0ll;
        }));
    }

    void Window::SetTitle(const char* title)
    {
      ::SetWindowText((HWND)m_hWnd, title);
    }

    void Window::SetDisplayMode(WindowDisplayMode mode)
    {
      if (m_displayMode == mode)
        return;

      HWND hWnd = (HWND)m_hWnd;
      if (m_displayMode == WindowDisplayMode_Windowed)
      {
        // Store the windowed window state
        m_windowedState.maximized = (GetFlags() & WindowFlag_Maximized) > 0;

        if (m_windowedState.maximized)
          ::SendMessage(hWnd, WM_SYSCOMMAND, SC_RESTORE, 0);

        m_windowedState.style = ::GetWindowLong(hWnd, GWL_STYLE);
        m_windowedState.exStyle = ::GetWindowLong(hWnd, GWL_EXSTYLE);

        GetRect(&m_windowedState.x,
          &m_windowedState.y,
          &m_windowedState.width,
          &m_windowedState.height);
      }

      switch (mode)
      {
      case WindowDisplayMode_Fullscreen:
      {
      } break;
      case WindowDisplayMode_FullscreenWindowed:
      {
        // Set new window style and size.
        ::SetWindowLong(hWnd, GWL_STYLE, (LONG)m_windowedState.style & ~(WS_CAPTION | WS_THICKFRAME));
        ::SetWindowLong(hWnd, GWL_EXSTYLE, (LONG)m_windowedState.exStyle & ~(WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE));

        // On expand, if we're given a window_rect, grow to it, otherwise do not resize.
        MONITORINFO monitorInfo;
        monitorInfo.cbSize = sizeof(monitorInfo);
        ::GetMonitorInfo(::MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST), &monitorInfo);
        RECT windowRect(monitorInfo.rcMonitor); // TODO: Add a Monitor API to the engine
        ::SetWindowPos(hWnd, NULL, windowRect.left, windowRect.top, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
      } break;
      case WindowDisplayMode_Windowed:
      {
        // Restore window sizes
        ::SetWindowLong(hWnd, GWL_STYLE, (LONG)m_windowedState.style);
        ::SetWindowLong(hWnd, GWL_EXSTYLE, (LONG)m_windowedState.exStyle);

        // Restore window rect
        SetRect(m_windowedState.x, m_windowedState.y, m_windowedState.width, m_windowedState.height);

        // Restore maximized state
        if (m_windowedState.maximized)
          ::SendMessage(hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
      } break;
      }

      m_displayMode = mode;
    }

    void Window::SetFocus(WindowFocusFlags flags, bool focused)
    {
      HWND hWnd = (HWND)m_hWnd;
      if (flags & WindowFocusFlag_Mouse)
        ::SetFocus(focused ? hWnd : 0);

      if (flags & WindowFocusFlag_Keyboard)
      {
        if (focused)
          ::SetCapture(hWnd);
        else
          ::ReleaseCapture();
      }
    }

    void Window::SetSize(int64_t width, int64_t height)
    {
      RECT rect = { 0 };
      rect.left = 0;          rect.top = 0;
      rect.right = (int)width; rect.bottom = (int)height;
      AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
      ::SetWindowPos((HWND)m_hWnd, 0, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
    }

    void Window::SetPosition(int64_t posX, int64_t posY)
    {
      ::SetWindowPos((HWND)m_hWnd, 0, (int)posX, (int)posY, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
    }

    void Window::SetRect(int64_t posX, int64_t posY, int64_t width, int64_t height)
    {
      ::SetWindowPos((HWND)m_hWnd, 0, (int)posX, (int)posY, (int)width, (int)height, SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
    }

    const char* Window::GetTitle() const
    {
      int len = ::GetWindowTextLength((HWND)m_hWnd) + 1;
      m_pWndTitleBuffer->resize(len);
      memset(m_pWndTitleBuffer->data(), 0, len);
      ::GetWindowText((HWND)m_hWnd, m_pWndTitleBuffer->data(), len);
      return m_pWndTitleBuffer->data();
    }

    WindowDisplayMode Window::GetDisplayMode() const
    {
      return m_displayMode;
    }

    WindowFocusFlags Window::GetFocusFlags() const
    {
      IWindow* pKeyboard = GetFocusedWindow(WindowFocusFlag_Keyboard);
      IWindow* pMouse    = GetFocusedWindow(WindowFocusFlag_Mouse);
      WindowFocusFlags flags = WindowFocusFlag_None;
      if (pKeyboard && pKeyboard == this)
        flags = flags | WindowFocusFlag_Keyboard;
      if (pMouse && pMouse == this)
        flags = flags | WindowFocusFlag_Keyboard;
      return flags;
    }

    WindowFlags Window::GetFlags() const
    {
      HWND hWnd = (HWND)m_hWnd;
      WindowFlags flags = WindowFlag_None;
      flags = flags | (::IsWindowVisible(hWnd) ? WindowFlag_Visible : WindowFlag_None);
      flags = flags | (::IsZoomed(hWnd) ? WindowFlag_Maximized : WindowFlag_None);
      flags = flags | (::IsIconic(hWnd) ? WindowFlag_Minimized : WindowFlag_None);
      return flags;
    }

    void Window::GetRect(int64_t* pPosX, int64_t* pPosY, int64_t* pWidth, int64_t* pHeight) const
    {
      RECT rect = { 0 };
      ::GetClientRect((HWND)m_hWnd, &rect);

      if (pPosX)
        *pPosX = rect.left;
      if (pPosY)
        *pPosY = rect.top;
      if (pWidth)
        *pWidth = rect.right - rect.left;
      if (pHeight)
        *pHeight = rect.bottom - rect.top;
    }

    bool Window::ReceivedEvent(EventID id, bool reset)
    {
      bool received = m_receivedEvents[id];
      m_receivedEvents[id] &= !reset;
      return received;
    }

    void Window::GetSize(int64_t* pWidth, int64_t* pHeight) const
    {
      GetRect(nullptr, nullptr, pWidth, pHeight);
    }

    int64_t Window::GetWidth() const
    {
      int64_t width;
      GetSize(&width, nullptr);
      return width;
    }

    int64_t Window::GetHeight() const
    {
      int64_t height;
      GetSize(nullptr, &height);
      return height;
    }

    void Window::GetPosition(int64_t* pPosX, int64_t* pPosY) const
    {
      GetRect(pPosX, pPosY, nullptr, nullptr);
    }

    int64_t Window::GetX() const
    {
      int64_t x;
      GetPosition(&x, nullptr);
      return x;
    }

    int64_t Window::GetY() const
    {
      int64_t y;
      GetPosition(nullptr, &y);
      return y;
    }

    static LRESULT CALLBACK _flWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
      NativeEvent nativeEvent;
      nativeEvent.msg = uMsg;
      nativeEvent.hWnd = hwnd;
      nativeEvent.wParam = (uint32_t)wParam;
      nativeEvent.lParam = (void*)lParam;

      Event evnt;
      Event_Create(&evnt, &nativeEvent);

      IWindow** ppWindow = _windowLookup.TryGet(hwnd);
      evnt.pWindow = ppWindow ? *ppWindow : nullptr;

      Fractal_PostGlobalEvent(&evnt);

      if (evnt.id == E_Wnd_Close)
        return 0;

      return ::DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    bool Window::IsEventSource(const Event* pEvent) const
    {
      return pEvent->nativeEvent.hWnd == m_hWnd;
    }

    void* Window::GetNativeHandle() const
    {
      return m_hWnd;
    }

    WindowRenderTarget* Window::GetRenderTarget() const
    {
      return m_pRenderTarget;
    }

    bool Window::BindRenderTarget(WindowRenderTarget* pTarget)
    {
      if (m_pRenderTarget != nullptr)
        return false;

      pTarget->IncRef();
      m_pRenderTarget = pTarget;
      return true;
    }

    void Window::UnbindRenderTarget()
    {
      if (m_pRenderTarget != nullptr)
        m_pRenderTarget->DecRef();
      m_pRenderTarget = nullptr;
    }

    static IWindow* _GetWindowFromHandle(HWND hWnd)
    {
      IWindow* pWindow = nullptr;
      ITask* pTask = MakeTask([&]()
        {
          pWindow = _windowLookup.GetOr(hWnd, 0);
          return 0ll;
        });

      Fractal_GetEventThread()->Add(pTask);

      pTask->Await();
      pTask->DecRef();

      return pWindow;
    }

    IWindow* Window::GetFocusedWindow(flIN WindowFocusFlags focusFlags)
    {
      HWND capturedWindow = ::GetCapture();
      HWND focusedWindow = ::GetFocus();

      IWindow* pKeyboardWnd = _GetWindowFromHandle(focusedWindow);
      IWindow* pMouseWnd = nullptr;

      if (capturedWindow == 0)
        pMouseWnd = _pHoveredWindow;
      else
        pMouseWnd = _GetWindowFromHandle(capturedWindow);


      bool keyboard = (focusFlags & WindowFocusFlag_Keyboard) > 0;
      bool mouse = (focusFlags & WindowFocusFlag_Mouse) > 0;
      if (keyboard && mouse)
        return pKeyboardWnd == pMouseWnd ? pKeyboardWnd : nullptr;
      else if (keyboard)
        return pKeyboardWnd;
      else if (mouse)
        return pMouseWnd;
      return nullptr;
    }
  }
}

#endif
