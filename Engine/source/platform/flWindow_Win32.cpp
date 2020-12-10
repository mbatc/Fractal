#include "platform/flWindow_Impl.h"

#if flUSING(flPLATFORM_WINDOWS)

#include "graphics/flWindowRenderTarget.h"
#include "platform/flEventQueue.h"
#include "threads/flThreads.h"
#include "platform/flEvent.h"
#include "atString.h"
#include <windows.h>
#include <mutex>

using namespace flEngine;
using namespace flEngine::Input;
using namespace flEngine::Platform;

LRESULT CALLBACK _flWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

static std::mutex _windowInitLock;
static int64_t _windowInitCount = 0;
static atString _windowClsName = "FractalEngine_WindowClass";
static ATOM _atom = 0;

void Impl_Window::Construct(const char *title, Window::Flags flags, Window::DisplayMode displayMode, InputDeviceServer *pKeyboardServer, InputDeviceServer *pMouseServer)
{
  // Set input device servers
  m_keyboard.SetServer(pKeyboardServer);
  m_mouse.SetServer(pMouseServer);

  HINSTANCE hInstance = ::GetModuleHandle(NULL);

  // Setup the event filter, so we only receive events for this window
  m_events.SetFilter([](Event *pEvent, void *pUserData) {
    Impl_Window *pWnd = (Impl_Window*)pUserData;
    return pWnd->IsEventSource(pEvent) || pEvent->nativeEvent.hWnd == nullptr;
  }, this);

  // Setup the event callback
  m_events.SetEventCallback([](Event *pEvent, void *pUserData) {
    Impl_Window *pWnd = (Impl_Window*)pUserData;
    pWnd->m_receivedEvents[pEvent->id] = true;

    switch (pEvent->id)
    {
    case E_Wnd_Activate:
      if (pEvent->wndActive.isActive)
        pWnd->m_focus = Window::FF_Keyboard | Window::FF_Mouse | Window::FF_Grabbed;
      else
        pWnd->m_focus = Window::FF_None;
      break;

    case E_Kbd_SetFocus:
      pWnd->m_focus = pWnd->m_focus | Window::FF_Keyboard;
      break;

    case E_Kbd_KillFocus:
      pWnd->m_focus = pWnd->m_focus & ~Window::FF_Keyboard;
      break;
    }
  }, this);

  _windowInitLock.lock();
  if (_windowInitCount++ == 0)
  { // Create the window class for flEngine win32 windows
    EventQueue::GetEventThread()->Add([](void *pUserData) {
      WNDCLASSEX wndCls = { 0 };
      wndCls.cbSize = sizeof(WNDCLASSEX);
      wndCls.style = 0;
      wndCls.lpfnWndProc = _flWindowProc;
      wndCls.hInstance = (HINSTANCE)pUserData;
      wndCls.hIcon = ::LoadIcon(NULL, IDI_APPLICATION);
      wndCls.hCursor = ::LoadCursor(NULL, IDC_ARROW);
      wndCls.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
      wndCls.lpszClassName = _windowClsName.c_str();

      // TODO: Add error reporting
      _atom = RegisterClassEx(&wndCls);

      return 0ll;
    }, hInstance);
  }
  _windowInitLock.unlock();

  Create(title, flags, hInstance);
}

Impl_Window::~Impl_Window()
{
  Destroy();

  while (!ReceivedEvent(E_Wnd_Destroy, false))
    Threads::Sleep(1);

  _windowInitLock.lock();

  if (--_windowInitCount == 0)
  {
    EventQueue::GetEventThread()->Add([](void *) {
      UnregisterClass(_windowClsName.c_str(), ::GetModuleHandle(NULL));
      return 0ll;
    });
  }
  _windowInitLock.unlock();
}

void Impl_Window::Create(const char *title, Window::Flags flags, void *hInstance)
{
  Util::Task *pCreateTask = nullptr;

  // Create the window on the System event thread
  struct CreateData
  {
    void        **ppHandle;
    const char   *title;
    Window::Flags flags;
    HINSTANCE     hInstance;
  };

  CreateData createData;
  createData.ppHandle  = &m_hWnd;
  createData.title     = title;
  createData.flags     = flags;
  createData.hInstance = (HINSTANCE)hInstance;

  // Create the window
  EventQueue::GetEventThread()->Add([](void *pUserData) {
    CreateData *pCreateData = (CreateData*)pUserData;

    // TODO: Add error reporting
    *pCreateData->ppHandle = CreateWindowEx(
      WS_EX_OVERLAPPEDWINDOW,
      _windowClsName.c_str(),
      pCreateData->title,
      WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT,
      CW_USEDEFAULT, CW_USEDEFAULT,
      0,
      0,
      pCreateData->hInstance,
      0);

    int show = SW_HIDE;

    ::UpdateWindow((HWND)*pCreateData->ppHandle);
    if ((pCreateData->flags & Window::Flag_Visible) > 0)
      ::ShowWindow((HWND)*pCreateData->ppHandle, SW_SHOW);

    return 0ll;
  }, &createData, &pCreateTask);

  // Wait for the task to complete
  pCreateTask->Wait();
  pCreateTask->DecRef();
}

void Impl_Window::Destroy()
{
  if (!m_hWnd)
    return;

  EventQueue::GetEventThread()->Add([](void *pHandle) {
    ::DestroyWindow((HWND)pHandle);
    return 0ll;
  }, m_hWnd);
}

void Impl_Window::SetTitle(const char *title)
{
  ::SetWindowText((HWND)m_hWnd, title);
}

void Impl_Window::SetDisplayMode(Window::DisplayMode mode)
{
  if (m_displayMode == mode)
    return;

  HWND hWnd = (HWND)m_hWnd;
  if (m_displayMode == Window::DM_Windowed)
  { // Store the windowed window state
    m_windowedState.maximized = (GetFlags() & Window::Flag_Maximized) > 0;

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
  case Window::DM_Fullscreen:
  {
  } break;
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
  } break;
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
  } break;
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

  if (focused) m_focus = m_focus | flags;
  else         m_focus = m_focus & ~flags;
}

void Impl_Window::SetSize(int64_t width, int64_t height)
{
  ::SetWindowPos((HWND)m_hWnd, 0, 0, 0, (int)width, (int)height, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
}

void Impl_Window::SetPosition(int64_t posX, int64_t posY)
{
  ::SetWindowPos((HWND)m_hWnd, 0, (int)posX, (int)posY, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
}

void Impl_Window::SetRect(int64_t posX, int64_t posY, int64_t width, int64_t height)
{
  ::SetWindowPos((HWND)m_hWnd, 0, (int)posX, (int)posY, (int)width, (int)height, SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
}

const char* Impl_Window::GetTitle()
{
  int len = ::GetWindowTextLength((HWND)m_hWnd) + 1;
  flDelete[] m_wndTitleBuffer;
  m_wndTitleBuffer = flNew char[len];
  memset(m_wndTitleBuffer, 0, len);
  ::GetWindowText((HWND)m_hWnd, m_wndTitleBuffer, len);
  return m_wndTitleBuffer;
}

Window::DisplayMode Impl_Window::GetDisplayMode() const
{
  return m_displayMode;
}

Window::FocusFlags Impl_Window::GetFocusFlags() const
{
  return m_focus;
}

Window::Flags Impl_Window::GetFlags() const
{
  HWND hWnd = (HWND)m_hWnd;
  Window::Flags flags = Window::Flag_None;
  flags = flags | (::IsWindowVisible(hWnd) ? Window::Flag_Visible   : Window::Flag_None);
  flags = flags | (::IsZoomed(hWnd)        ? Window::Flag_Maximized : Window::Flag_None);
  flags = flags | (::IsIconic(hWnd)        ? Window::Flag_Minimized : Window::Flag_None);
  return flags;
}

void Impl_Window::GetRect(int64_t *pPosX, int64_t *pPosY, int64_t *pWidth, int64_t *pHeight) const
{
  RECT rect = { 0 };
  ::GetWindowRect((HWND)m_hWnd, &rect);

  if (pPosX)   *pPosX   = rect.left;
  if (pPosY)   *pPosY   = rect.top;
  if (pWidth)  *pWidth  = rect.right - rect.left;
  if (pHeight) *pHeight = rect.bottom - rect.top;
}

void Impl_Window::GetSize(int64_t *pWidth, int64_t *pHeight) const
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

void Impl_Window::GetPosition(int64_t *pPosX, int64_t *pPosY) const
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

  EventQueue::PostGlobalEvent(&evnt);

  if (evnt.id == E_Wnd_Close)
    return 0;

  return ::DefWindowProc(hwnd, uMsg, wParam, lParam);
}

bool Impl_Window::IsEventSource(const Event *pEvent) const
{
  return pEvent->nativeEvent.hWnd == m_hWnd;
}

void* Impl_Window::GetNativeHandle() const
{
  return m_hWnd;
}

Graphics::WindowRenderTarget* flEngine::Platform::Impl_Window::GetRenderTarget() const
{
  return m_pRenderTarget;
}

bool flEngine::Platform::Impl_Window::BindRenderTarget(Graphics::WindowRenderTarget *pTarget)
{
  if (m_pRenderTarget)
    return false;

  pTarget->IncRef();
  m_pRenderTarget = pTarget;
  return true;
}

void flEngine::Platform::Impl_Window::UnbindRenderTarget()
{
  if (m_pRenderTarget)
    m_pRenderTarget->DecRef();
  m_pRenderTarget = nullptr;
}

#endif
