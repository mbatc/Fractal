#include "flWindow_Impl.h"

#if flUSING(flPLATFORM_WINDOWS)

#include "flWindowRenderTarget.h"
#include "flEventQueue.h"
#include "flThreads.h"
#include "flEvent.h"
#include "ctHashMap.h"
#include "ctString.h"
#include <windows.h>
#include <mutex>

namespace Fractal
{
  LRESULT CALLBACK _flWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

  static std::mutex _windowInitLock;
  static int64_t _windowInitCount = 0;
  static ctString _windowClsName = "FractalEngine_WindowClass";
  static ATOM _atom = 0;
  static ctHashMap<void*, Window*> _windowLookup;
  static Window* _pHoveredWindow = nullptr;

  static Window* _GetWindowFromHandle(HWND hWnd);

  Window::Flags _GetFlagsFromStyle(LONG style)
  {
    Window::Flags flags = Window::Flag_None;
    if (style & WS_POPUP)
      flags = flags | Window::Flag_Borderless;
    return flags;
  }

  Window::Flags _GetFlagsFromStyleEx(LONG style)
  {
    Window::Flags flags = Window::Flag_None;
    if (style & WS_EX_TOOLWINDOW)
      flags = flags | Window::Flag_NoIcon;
    if (style & WS_EX_TOPMOST)
      flags = flags | Window::Flag_TopMost;
    return flags;
  }

  LONG _GetStyleFromFlags(Window::Flags flags)
  {
    LONG style = 0;
    if (flags & Window::Flag_Borderless)
      style |=  WS_POPUP;
    else
      style |= WS_OVERLAPPEDWINDOW;
    return style;
  }

  LONG _GetStyleExFromFlags(Window::Flags flags)
  {
    LONG style = 0;
    if (flags & Window::Flag_TopMost)
      style |= WS_EX_TOPMOST;

    if (flags & Window::Flag_NoIcon)
      style |= WS_EX_TOOLWINDOW;
    else
      style |= WS_EX_APPWINDOW;

    return style;
  }

  void Impl_Window::Construct(Window* pWindow, const char* title, Window::Flags flags, Window::DisplayMode displayMode, Window* pParent)
  {
    HINSTANCE hInstance = ::GetModuleHandle(NULL);

    // Setup the event filter, so we only receive events for this window
    m_events.SetFilter(
      [](Event * pEvent, void* pUserData)
    {
      Impl_Window* pWnd = (Impl_Window*)pUserData;
      return pWnd->IsEventSource(pEvent) || pEvent->nativeEvent.hWnd == nullptr;
    },
    this);

    // Setup the event callback
    m_events.SetEventCallback(
      [](Event * pEvent, void* pUserData)
    {
      Impl_Window* pWnd = (Impl_Window*)pUserData;
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
    },
    this);

    _windowInitLock.lock();
    if (_windowInitCount++ == 0)
    {
      // Create the window class for flEngine win32 windows
      EventQueue::GetEventThread()->Add(MakeTask(
                                          [ = ]()
      {
        WNDCLASSEX wndCls = {0};
        wndCls.cbSize = sizeof(WNDCLASSEX);
        wndCls.style = 0;
        wndCls.lpfnWndProc = _flWindowProc;
        wndCls.hInstance = hInstance;
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

    Create(pWindow, title, flags, hInstance, pParent);
  }

  Impl_Window::~Impl_Window()
  {
    Destroy();

    while (!ReceivedEvent(E_Wnd_Destroy, false))
      Sleep(1);

    _windowInitLock.lock();

    if (--_windowInitCount == 0)
    {
      EventQueue::GetEventThread()->Add(MakeTask(
                                          [ = ]()
      {
        UnregisterClass(_windowClsName.c_str(), ::GetModuleHandle(NULL));
        return 0ll;
      }));
    }
    _windowInitLock.unlock();
  }

  void Impl_Window::Create(Window* pWindow, const char* title, Window::Flags flags, void* hInstance, Window* pParent)
  {
    // Create the window
    Ref<Task> pCreateTask = MakeTask(
                              [ = ]()
    {
      // TODO: Add error reporting
      m_hWnd = CreateWindowEx(
                 _GetStyleExFromFlags(flags),
                 _windowClsName.c_str(),
                 title,
                 _GetStyleFromFlags(flags),
                 CW_USEDEFAULT, CW_USEDEFAULT,
                 CW_USEDEFAULT, CW_USEDEFAULT,
                 pParent == nullptr ? 0 : (HWND)pParent->GetNativeHandle(),
                 0,
                 (HINSTANCE)hInstance,
                 0);

      _windowLookup.Add(m_hWnd, pWindow);

      int show = SW_HIDE;

      ::UpdateWindow((HWND)m_hWnd);
      if ((flags & Window::Flag_Visible) > 0)
        ::ShowWindow((HWND)m_hWnd, SW_SHOW);
      return 0ll;
    });

    EventQueue::GetEventThread()->Add(pCreateTask);

    // Wait for the task to complete
    pCreateTask->Await();
  }

  void Impl_Window::Destroy()
  {
    if (!m_hWnd)
      return;

    EventQueue::GetEventThread()->Add(
      [](void* pHandle)
    {
      ::DestroyWindow((HWND)pHandle);
      _windowLookup.Remove(pHandle);
      return 0ll;
    },
    m_hWnd);
  }

  Window* Impl_Window::GetFocusedWindow(Window::FocusFlags focusFlags)
  {
    HWND capturedWindow = ::GetCapture();
    HWND focusedWindow = ::GetFocus();

    Window* pKeyboardWnd = _GetWindowFromHandle(focusedWindow);
    Window* pMouseWnd = nullptr;

    if (capturedWindow == 0)
      pMouseWnd = _pHoveredWindow;
    else
      pMouseWnd = _GetWindowFromHandle(capturedWindow);

    bool keyboard = (focusFlags & Window::FF_Keyboard) > 0;
    bool mouse = (focusFlags & Window::FF_Mouse) > 0;
    if (keyboard && mouse)
      return pKeyboardWnd == pMouseWnd ? pKeyboardWnd : nullptr;
    else if (keyboard)
      return pKeyboardWnd;
    else if (mouse)
      return pMouseWnd;
    return nullptr;
  }

  void Impl_Window::BringToFocus()
  {
    HWND hWnd = (HWND)m_hWnd;
    ::BringWindowToTop(hWnd);
    ::SetForegroundWindow(hWnd);
    ::SetFocus(hWnd);
  }

  Window* Impl_Window::GetForegroundWindow()
  {
    return _GetWindowFromHandle(::GetForegroundWindow());
  }

  void Impl_Window::SetTitle(const char* title)
  {
    ::SetWindowText((HWND)m_hWnd, title);
  }

  void Impl_Window::SetDisplayMode(Window::DisplayMode mode)
  {
    if (m_displayMode == mode)
      return;

    HWND hWnd = (HWND)m_hWnd;
    if (m_displayMode == Window::DM_Windowed)
    {
      // Store the windowed window state
      m_windowedState.maximized = (GetFlags() & Window::Flag_Maximized) > 0;

      if (m_windowedState.maximized)
        ::SendMessage(hWnd, WM_SYSCOMMAND, SC_RESTORE, 0);

      m_windowedState.style = ::GetWindowLong(hWnd, GWL_STYLE);
      m_windowedState.exStyle = ::GetWindowLong(hWnd, GWL_EXSTYLE);

      GetRect(
        &m_windowedState.x,
        &m_windowedState.y,
        &m_windowedState.width,
        &m_windowedState.height);
    }

    switch (mode)
    {
    case Window::DM_Fullscreen:
    {
    }
    break;
    case Window::DM_FullscreenWindowed:
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
    }
    break;
    case Window::DM_Windowed:
    {
      // Restore window sizes
      ::SetWindowLong(hWnd, GWL_STYLE, (LONG)m_windowedState.style);
      ::SetWindowLong(hWnd, GWL_EXSTYLE, (LONG)m_windowedState.exStyle);

      // Restore window rect
      SetRect(m_windowedState.x, m_windowedState.y, m_windowedState.width, m_windowedState.height);

      // Restore maximized state
      if (m_windowedState.maximized)
        ::SendMessage(hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
    }
    break;
    }

    m_displayMode = mode;
  }

  void Impl_Window::SetFocus(Window::FocusFlags flags, bool focused)
  {
    HWND hWnd = (HWND)m_hWnd;
    if (flags & Window::FF_Mouse)
      ::SetFocus(focused ? hWnd : 0);

    if (flags & Window::FF_Keyboard)
    {
      if (focused)
        ::SetCapture(hWnd);
      else
        ::ReleaseCapture();
    }
  }

  void Impl_Window::SetSize(int64_t width, int64_t height)
  {
    RECT rect = {0};
    rect.left = 0;
    rect.top = 0;
    rect.right = (int)width;
    rect.bottom = (int)height;
    ::AdjustWindowRectEx(&rect, GetWindowLong((HWND)m_hWnd, GWL_STYLE), false, GetWindowLong((HWND)m_hWnd, GWL_EXSTYLE));
    ::SetWindowPos((HWND)m_hWnd, 0, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
  }

  void Impl_Window::SetPosition(int64_t posX, int64_t posY)
  {
    RECT rect = { (LONG)posX, (LONG)posY, (LONG)posX, (LONG)posY };
    ::AdjustWindowRectEx(&rect, GetWindowLong((HWND)m_hWnd, GWL_STYLE), FALSE, GetWindowLong((HWND)m_hWnd, GWL_EXSTYLE));
    ::SetWindowPos((HWND)m_hWnd, 0, (int)posX, (int)posY, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
  }

  void Impl_Window::SetRect(int64_t posX, int64_t posY, int64_t width, int64_t height)
  {
    ::SetWindowPos((HWND)m_hWnd, 0, (int)posX, (int)posY, (int)width, (int)height, SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
  }

  void Impl_Window::SetParent(Window* pParent)
  {
    ::SetParent((HWND)m_hWnd, pParent == nullptr ? 0 : (HWND)pParent->GetNativeHandle());
  }

  Window* Impl_Window::GetParent() const
  {
    HWND hParent = ::GetParent((HWND)m_hWnd);
    return _GetWindowFromHandle(hParent);
  }

  const char* Impl_Window::GetTitle() const
  {
    int len = ::GetWindowTextLength((HWND)m_hWnd) + 1;
    m_pWndTitleBuffer->resize(len);
    memset(m_pWndTitleBuffer->data(), 0, len);
    ::GetWindowText((HWND)m_hWnd, m_pWndTitleBuffer->data(), len);
    return m_pWndTitleBuffer->data();
  }

  Window::DisplayMode Impl_Window::GetDisplayMode() const
  {
    return m_displayMode;
  }

  Window::FocusFlags Impl_Window::GetFocusFlags() const
  {
    Window* pKeyboard = GetFocusedWindow(Window::FF_Keyboard);
    Window* pMouse = GetFocusedWindow(Window::FF_Mouse);
    Window::FocusFlags flags = Window::FF_None;
    if (pKeyboard && pKeyboard->pImplWindow == this)
      flags = flags | Window::FF_Keyboard;
    if (pMouse && pMouse->pImplWindow == this)
      flags = flags | Window::FF_Keyboard;
    return flags;
  }

  Window::Flags Impl_Window::GetFlags() const
  {
    HWND hWnd = (HWND)m_hWnd;
    Window::Flags flags = Window::Flag_None;
    flags = flags | (::IsWindowVisible(hWnd) ? Window::Flag_Visible : Window::Flag_None);
    flags = flags | (::IsZoomed(hWnd) ? Window::Flag_Maximized : Window::Flag_None);
    flags = flags | (::IsIconic(hWnd) ? Window::Flag_Minimized : Window::Flag_None);
    flags = flags | _GetFlagsFromStyle(GetWindowLong(hWnd, GWL_EXSTYLE));
    flags = flags | _GetFlagsFromStyle(GetWindowLong(hWnd, GWL_STYLE));
    return flags;
  }

  void Impl_Window::SetFlags(flIN Window::Flags flags)
  {
    HWND hWnd = (HWND)m_hWnd;
    LONG style   = _GetStyleFromFlags(flags);
    LONG exStyle = _GetStyleExFromFlags(flags);

    ::SetWindowLong(hWnd, GWL_EXSTYLE, exStyle);
    ::SetWindowLong(hWnd, GWL_STYLE, style);

    if (!(flags & Window::Flag_Visible))
      ::ShowWindow(hWnd, SW_HIDE);
    else
    {
      if (flags & Window::Flag_Minimized)
        ::ShowWindow(hWnd, SW_SHOWMINIMIZED);
      else if (flags & Window::Flag_Maximized)
        ::ShowWindow(hWnd, SW_SHOWMAXIMIZED);
      else                                     ::ShowWindow(hWnd, SW_SHOW);
    }
  }

  void Impl_Window::AddFlags(flIN Window::Flags flags)
  {
    SetFlags(GetFlags() | flags);
  }

  void Impl_Window::RemoveFlags(flIN Window::Flags flags)
  {
    SetFlags(GetFlags() & ~flags);
  }

  void Impl_Window::GetRect(int64_t* pPosX, int64_t* pPosY, int64_t* pWidth, int64_t* pHeight) const
  {
    RECT rect = { 0 };
    ::GetClientRect((HWND)m_hWnd, &rect);
    POINT tl = {0, 0};
    ::ClientToScreen((HWND)m_hWnd, &tl);
    if (pPosX)
      *pPosX = tl.x;
    if (pPosY)
      *pPosY = tl.y;
    if (pWidth)
      *pWidth = rect.right;
    if (pHeight)
      *pHeight = rect.bottom;
  }

  void Impl_Window::GetSize(int64_t* pWidth, int64_t* pHeight) const
  {
    GetRect(nullptr, nullptr, pWidth, pHeight);
  }

  int64_t Impl_Window::GetWidth() const
  {
    int64_t width;
    GetSize(&width, nullptr);
    return width;
  }

  int64_t Impl_Window::GetHeight() const
  {
    int64_t height;
    GetSize(nullptr, &height);
    return height;
  }

  void Impl_Window::GetPosition(int64_t* pPosX, int64_t* pPosY) const
  {
    GetRect(pPosX, pPosY, nullptr, nullptr);
  }

  int64_t Impl_Window::GetX() const
  {
    int64_t x;
    GetPosition(&x, nullptr);
    return x;
  }

  int64_t Impl_Window::GetY() const
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

    Window** ppWindow = _windowLookup.TryGet(hwnd);
    evnt.pWindow = ppWindow ? *ppWindow : nullptr;

    EventQueue::PostGlobalEvent(&evnt);

    if (evnt.id == E_Wnd_Close)
      return 0;

    return ::DefWindowProc(hwnd, uMsg, wParam, lParam);
  }

  bool Impl_Window::IsEventSource(const Event* pEvent) const
  {
    return pEvent->nativeEvent.hWnd == m_hWnd;
  }

  void* Impl_Window::GetNativeHandle() const
  {
    return m_hWnd;
  }

  WindowRenderTarget* Impl_Window::GetRenderTarget() const
  {
    return m_pRenderTarget;
  }

  bool Impl_Window::BindRenderTarget(WindowRenderTarget* pTarget)
  {
    if (m_pRenderTarget)
      return false;

    pTarget->IncRef();
    m_pRenderTarget = pTarget;
    return true;
  }

  void Impl_Window::UnbindRenderTarget()
  {
    if (m_pRenderTarget)
      m_pRenderTarget->DecRef();
    m_pRenderTarget = nullptr;
  }

  static Window* _GetWindowFromHandle(HWND hWnd)
  {
    Window* pWindow;
    Ref<Task> pTask = MakeTask(
                        [&]()
    {
      pWindow = _windowLookup.GetOr(hWnd, nullptr);
      return 0ll;
    });

    EventQueue::GetEventThread()->Add(pTask);

    pTask->Await();

    return pWindow;
  }
}

#endif
