#include "flPlatform_Window_Impl.h"

#if flUSING(flPLATFORM_WINDOWS)

#include "flPlatform_EventQueue.h"
#include "flPlatform_Event.h"
#include "atString.h"
#include <windows.h>
#include <mutex>

using namespace flEngine::Platform;

LRESULT CALLBACK _flWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

static std::mutex _windowInitLock;
static int64_t _windowInitCount = 0;
static atString _windowClsName = "FractalEngine_WindowClass";
static ATOM _atom = 0;

flEngine::Platform::Impl_Window::~Impl_Window()
{
  if (m_pHandle)
    DestroyWindow((HWND)m_pHandle);

  _windowInitLock.lock();
  if (--_windowInitCount == 0)
    UnregisterClass(_windowClsName.c_str(), GetModuleHandle(NULL));
  _windowInitLock.unlock();
}

void flEngine::Platform::Impl_Window::Construct(const char *title, Window::Flags flags, Window::DisplayMode displayMode)
{
  HINSTANCE hInstance = GetModuleHandle(NULL);

  _windowInitLock.lock();
  if (_windowInitCount++ == 0)
  { // Create the window class for flEngine win32 windows
    WNDCLASSEX wndCls = { 0 };
    wndCls.cbSize = sizeof(WNDCLASSEX);
    wndCls.style = 0;
    wndCls.lpfnWndProc = _flWindowProc;
    wndCls.hInstance = hInstance;
    wndCls.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndCls.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndCls.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wndCls.lpszClassName = _windowClsName.c_str();

    // TODO: Add error reporting
    _atom = RegisterClassEx(&wndCls);
  }
  _windowInitLock.unlock();

  // TODO: Add error reporting
  m_pHandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, _windowClsName.c_str(), title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, hInstance, 0);

  int show = SW_HIDE;

  if ((flags & Window::Flag_Visible) > 0)
    UpdateWindow((HWND)m_pHandle);
  ShowWindow((HWND)m_pHandle, SW_SHOW);
}

void Impl_Window::SetTitle(const char *title)
{
  SetWindowText((HWND)m_pHandle, title);
}

void Impl_Window::SetDisplayMode(Window::DisplayMode mode)
{
}

void Impl_Window::SetFocus(Window::FocusFlags flags, bool focused)
{

}

void Impl_Window::SetSize(int64_t width, int64_t height)
{
}

void Impl_Window::SetPosition(int64_t posX, int64_t posY)
{

}

const char* Impl_Window::GetTitle()
{
  int len = GetWindowTextLength((HWND)m_pHandle) + 1;
  flDelete[] m_wndTitleBuffer;
  m_wndTitleBuffer = flNew char[len];
  memset(m_wndTitleBuffer, 0, len);
  GetWindowText((HWND)m_pHandle, m_wndTitleBuffer, len);
  return m_wndTitleBuffer;
}

Window::DisplayMode Impl_Window::GetDisplayMode() const
{
  return Window::DM_Windowed;
}

Window::FocusFlags Impl_Window::GetFocusFlags() const
{
  return Window::FF_None;
}

Window::Flags flEngine::Platform::Impl_Window::GetFlags() const
{
  HWND hWnd = (HWND)m_pHandle;
  Window::Flags flags = Window::Flag_None;
  flags = flags | (IsWindowVisible(hWnd) ? Window::Flag_Visible : Window::Flag_None);
  flags = flags | (IsZoomed(hWnd) ? Window::Flag_Maximized : Window::Flag_None);
  flags = flags | (IsIconic(hWnd) ? Window::Flag_Minimized : Window::Flag_None);
  return flags;
}

void Impl_Window::GetRect(int64_t * pPosX, int64_t * pPosY, int64_t * pWidth, int64_t * pHeight) const
{
  RECT rect = { 0 };
  GetWindowRect((HWND)m_pHandle, &rect);

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

  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

#endif