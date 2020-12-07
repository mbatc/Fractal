#ifndef fl_Platform_Window_Impl_h__
#define fl_Platform_Window_Impl_h__

#include "platform/flWindow.h"
#include "platform/flEventQueue.h"

namespace flEngine
{
  namespace Platform
  {
    class Impl_Window
    {
    public:
      ~Impl_Window();

      void Construct(const char *title, Window::Flags flags, Window::DisplayMode displayMode, Input::InputDeviceServer *pKeyboardServer, Input::InputDeviceServer *pMouseServer);

      void SetTitle(const char *title);
      void SetDisplayMode(Window::DisplayMode mode);
      void SetFocus(Window::FocusFlags flags, bool focused);
      void SetSize(int64_t width, int64_t height);
      void SetPosition(int64_t posX, int64_t posY);
      void SetRect(int64_t posX, int64_t posY, int64_t width, int64_t height);

      const char* GetTitle();

      Window::DisplayMode GetDisplayMode() const;
      Window::FocusFlags GetFocusFlags() const;
      Window::Flags GetFlags() const;

      void GetRect(int64_t *pPosX, int64_t *pPosY, int64_t *pWidth, int64_t *pHeight) const;

      void GetSize(int64_t *pWidth, int64_t *pHeight) const;

      int64_t GetWidth() const;
      int64_t GetHeight() const;

      void GetPosition(int64_t *pPosX, int64_t *pPosY) const;

      int64_t GetX() const;
      int64_t GetY() const;

      bool ReceivedEvent(Platform::EventID id, bool reset);

      Input::Keyboard* GetKeyboard();
      Input::Mouse* GetMouse();

      bool IsEventSource(const Event *pEvent) const;

      void* GetNativeHandle() const;

      void SetPixelFormat(Graphics::PixelFormat pixelFmt, Graphics::PixelComponentType pixelComponentType, Graphics::DepthFormat depthFmt);

    protected:
      void Create(const char *title, Window::Flags flags, void *hInstance);
      void Destroy();

      EventQueue m_events;
      bool m_receivedEvents[Platform::Event_Count] = { 0 };

      Window::FocusFlags m_focus = Window::FF_None;
      Window::DisplayMode m_displayMode = Window::DM_Windowed;

      Input::Keyboard m_keyboard;
      Input::Mouse m_mouse;

#if flUSING(flPLATFORM_WINDOWS)
      struct
      { // Backup struct for full-screen a window in WinAPI
        bool maximized  = false;
        int64_t x       = 0;
        int64_t y       = 0;
        int64_t width   = 0;
        int64_t height  = 0;
        int64_t style   = 0;
        int64_t exStyle = 0;
      } m_windowedState;

      bool m_pixelFormatSet = false;
      char *m_wndTitleBuffer = nullptr;

      void *m_hInstance = nullptr;
      void *m_hWnd = nullptr;
#endif
    };
  }
}

#endif // flPlatform_Window_Impl_h__
