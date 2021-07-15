#pragma once

#include "flIWindow.h"

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

      void SetTitle(flIN const char* title) override;
      void SetDisplayMode(flIN WindowDisplayMode mode) override;
      void SetFocus(flIN WindowFocusFlags flags, flIN bool focused) override;
      void SetSize(flIN int64_t width, flIN int64_t height) override;
      void SetPosition(flIN int64_t posX, flIN int64_t posY) override;
      void SetRect(flIN int64_t posX, flIN int64_t posY, flIN int64_t width, flIN int64_t height) override;
      const char* GetTitle() const override;
      WindowDisplayMode GetDisplayMode() const override;
      WindowFocusFlags GetFocusFlags() const override;
      WindowFlags GetFlags() const override;
      void GetSize(flOUT int64_t* pWidth, flOUT int64_t* pHeight) const override;
      int64_t GetWidth() const override;
      int64_t GetHeight() const override;
      void GetPosition(flOUT int64_t* pPosX, flOUT int64_t* pPosY) const override;
      int64_t GetX() const override;
      int64_t GetY() const override;
      void GetRect(flOUT int64_t* pPosX, flOUT int64_t* pPosY, flOUT int64_t* pWidth, flOUT int64_t* pHeight) const override;
      bool ReceivedEvent(flIN EventID id, flIN bool reset = true) override;
      bool IsEventSource(const Event* pEvent) const override;
      void* GetNativeHandle() const override;
      WindowRenderTarget* GetRenderTarget() const override;

      static Window * GetFocusedWindow(flIN WindowFocusFlags focusFlags);

    protected:
      void Create(const char* title, WindowFlags flags, void* hInstance);

      Ref<IEventQueue> m_pEvents;
      bool m_receivedEvents[Event_Count] = { 0 };

      WindowDisplayMode m_displayMode = DM_Windowed;

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
