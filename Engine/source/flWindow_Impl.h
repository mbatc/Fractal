#pragma once

#include "flWindow.h"
#include "flEventQueue.h"
#include "ctVector.h"

namespace Fractal
{
  class Impl_Window
  {
  public:
    ~Impl_Window();

    void Construct(Window* pWindow, const char* title, Window::Flags flags, Window::DisplayMode displayMode);

    void SetTitle(const char* title);
    void SetDisplayMode(Window::DisplayMode mode);
    void SetFocus(Window::FocusFlags flags, bool focused);
    void SetSize(int64_t width, int64_t height);
    void SetPosition(int64_t posX, int64_t posY);
    void SetRect(int64_t posX, int64_t posY, int64_t width, int64_t height);

    const char* GetTitle() const;

    Window::DisplayMode GetDisplayMode() const;
    Window::FocusFlags GetFocusFlags() const;
    Window::Flags GetFlags() const;

    void GetRect(int64_t* pPosX, int64_t* pPosY, int64_t* pWidth, int64_t* pHeight) const;

    void GetSize(int64_t* pWidth, int64_t* pHeight) const;

    int64_t GetWidth() const;
    int64_t GetHeight() const;

    void GetPosition(int64_t* pPosX, int64_t* pPosY) const;

    int64_t GetX() const;
    int64_t GetY() const;

    bool ReceivedEvent(EventID id, bool reset);

    bool IsEventSource(const Event* pEvent) const;

    void* GetNativeHandle() const;

    WindowRenderTarget* GetRenderTarget() const;

    bool BindRenderTarget(WindowRenderTarget* pTarget);
    void UnbindRenderTarget();

    void Create(Window* pWindow, const char* title, Window::Flags flags, void* hInstance);
    void Destroy();

    static Window* GetFocusedWindow(Window::FocusFlags focusFlags);

  protected:
    EventQueue m_events;
    bool m_receivedEvents[Event_Count] = { 0 };

    Window::DisplayMode m_displayMode = Window::DM_Windowed;

    WindowRenderTarget* m_pRenderTarget = nullptr;

#if flUSING(flPLATFORM_WINDOWS)
    struct
    {
      // Backup struct for full-screen a window in WinAPI
      bool maximized = false;
      int64_t x = 0;
      int64_t y = 0;
      int64_t width = 0;
      int64_t height = 0;
      int64_t style = 0;
      int64_t exStyle = 0;
    } m_windowedState;

    bool m_pixelFormatSet = false;
    std::unique_ptr<ctVector<char>> m_pWndTitleBuffer = std::make_unique<ctVector<char>>();

    void* m_hInstance = nullptr;
    void* m_hWnd = nullptr;
#endif
  };
}
