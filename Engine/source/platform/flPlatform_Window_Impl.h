#ifndef flPlatform_Window_Impl_h__
#define flPlatform_Window_Impl_h__

#include "flPlatform_Window.h"

namespace flEngine
{
  namespace Platform
  {
    class flEXPORT Impl_Window
    {
    public:
      ~Impl_Window();

      void Construct(const char *title, Window::Flags flags, Window::DisplayMode displayMode);

      void SetTitle(const char *title);
      void SetDisplayMode(Window::DisplayMode mode);
      void SetFocus(Window::FocusFlags flags, bool focused);
      void SetSize(int64_t width, int64_t height);
      void SetPosition(int64_t posX, int64_t posY);
      
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

    protected:
#if flUSING(flPLATFORM_WINDOWS)
      char *m_wndTitleBuffer = nullptr;
      void *m_pHandle = nullptr;
#endif

    };
  }
}

#endif // flPlatform_Window_Impl_h__
