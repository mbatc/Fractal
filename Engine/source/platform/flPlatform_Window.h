#ifndef flPlatform_Window_h__
#define flPlatform_Window_h__

#include "../flPImpl.h"
#include "../flConfig.h"

namespace flEngine
{
  namespace Platform
  {
    class Impl_Window;

    class flEXPORT Window
    {
      flPIMPL_DEF(Window);
    public:
      /**
       * 
       */
      enum DisplayMode
      {
        DM_Windowed,
        DM_Fullscreen,
        DM_FullscreenWindowed,
        DM_Count = 3
      };

      /**
      *
      */
      enum FocusFlags
      {
        FF_Keyboard = 1 << 0,
        FF_Mouse    = 1 << 1,
        FF_Grabbed  = 1 << 2,
        FF_Count = 3
      };

      /**
      *
      */
      enum Flags
      {
        Flag_Visible    = 1 << 0,
        Flag_Resizable  = 1 << 1,
        Flag_Borderless = 1 << 2,
        Flag_Minimized  = 1 << 3,
        Flag_Maximized  = 1 << 4,
        Flag_Count      = 5
      };

      /**
      * @brief Create a new window.
      *
      * Constructs a new OS window.
      */
      Window(const char *title, Flags flags, DisplayMode displayMode);

      /**
       * 
       */
      void SetTitle(const char *title);

      /**
       * 
       */
      void SetDisplayMode(DisplayMode mode);

      /**
      *
      */
      void SetKeyboardFocus(bool focused);

      /**
      *
      */
      void SetMouseFocus(bool focused);

      /**
      *
      */
      void SetSize(int64_t width, int64_t height);

      /**
      *
      */
      void SetPosition(int64_t posX, int64_t posY);

      /**
      *
      */
      const char* GetTitle() const;

      /**
      *
      */
      DisplayMode GetDisplayMode() const;

      /**
       * 
       */
      FocusFlags GetFocusFlags() const;

      /**
      *
      */
      void GetSize(int64_t *pWidth, int64_t *pHeight) const;

      /**
      *
      */
      void GetPosition(int64_t *pPosX, int64_t *pPosY) const;
    };
  }
}

#endif // flPlatform_Window_h__
