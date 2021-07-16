#pragma once

#include "flIWindow.h"
#include "flRef.h"

#include "ctVector.h"

namespace Fractal
{
  class IEventQueue;

  namespace Impl
  {
    class Window : public IWindow
    {
      FRACTAL_DEFAULT_INTERFACE;

    public:
      Window(const char* title, WindowFlags flags, WindowDisplayMode displayMode);
      ~Window();

      void SetTitle(const char* title) override;
      void SetDisplayMode(WindowDisplayMode mode) override;
      void SetFocus(WindowFocusFlags flags, bool focused) override;
      void SetSize(int64_t width, int64_t height) override;
      void SetPosition(int64_t posX, int64_t posY) override;
      void SetRect(int64_t posX, int64_t posY, int64_t width, int64_t height) override;
      const char* GetTitle() const override;
      WindowDisplayMode GetDisplayMode() const override;
      WindowFocusFlags GetFocusFlags() const override;
      WindowFlags GetFlags() const override;
      void GetSize(int64_t* pWidth, int64_t* pHeight) const override;
      int64_t GetWidth() const override;
      int64_t GetHeight() const override;
      void GetPosition(int64_t* pPosX, int64_t* pPosY) const override;
      int64_t GetX() const override;
      int64_t GetY() const override;
      void GetRect(int64_t* pPosX, int64_t* pPosY, int64_t* pWidth, int64_t* pHeight) const override;
      bool ReceivedEvent(EventID id, bool reset = true) override;
      bool IsEventSource(const Event* pEvent) const override;
      void* GetNativeHandle() const override;
      WindowRenderTarget* GetRenderTarget() const override;

      bool BindRenderTarget(WindowRenderTarget* pTarget);
      void UnbindRenderTarget();

      static IWindow * GetFocusedWindow(WindowFocusFlags focusFlags);

    protected:
      void Create(const char* title, WindowFlags flags, void* hInstance);
      void DestroyWnd();

      Ref<IEventQueue> m_pEvents;
      bool m_receivedEvents[Event_Count] = { 0 };

      WindowDisplayMode m_displayMode = WindowDisplayMode_Windowed;

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
}
