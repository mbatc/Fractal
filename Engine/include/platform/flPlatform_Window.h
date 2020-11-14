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
       * Available Window display modes.
       */
      enum DisplayMode
      {
        DM_Windowed,           ///> Windowed mode
        DM_Fullscreen,         ///> Fullscreen mode
        DM_FullscreenWindowed, ///> Fullscreen Windowed mode
        DM_Count = 3           ///> Number of window display modes
      };

      /**
       * Input focus flags
       */
      enum FocusFlags
      {
        FF_None     = 0,      ///> The window has no input focus
        FF_Keyboard = 1 << 0, ///> The window has keyboard focus
        FF_Mouse    = 1 << 1, ///> The window has mouse focus
        FF_Grabbed  = 1 << 2, ///> Did the window just gain focus
        FF_Count = 3          ///> Number of window focus flags
      };
      
      /**
       * General window behavior flags
       */
      enum Flags
      {
        Flag_None       = 0,      ///> Special No-Flags value
        Flag_Visible    = 1 << 0, ///> The window is visible
        Flag_Resizable  = 1 << 1, ///> The window can be resized using the borders
        Flag_Borderless = 1 << 2, ///> The window has a border
        Flag_Minimized  = 1 << 3, ///> The window is minimized
        Flag_Maximized  = 1 << 4, ///> The window is maximized
        Flag_Count      = 5       ///> Number of window flags
      };

      /**
       * Create a new window.
       *
       * @param [in] title       A c-string to use as the title. This will be copied so it may be destroyed after calling this function.
       * @param [in] flags       A set of initial flags for this window.
       * @param [in] displayMode The initial display mode for this window (e.g. Windowed or Fullscreen).
       */
      Window(flIN const char *title, flIN Flags flags, flIN DisplayMode displayMode);

      /**
       * Set the title of the Window.
       *
       * @param [in] title A c-string to set the window title to.
       */
      void SetTitle(flIN const char *title);

      /**
       * @brief Set the display mode of the Window.
       *
       * This function can be used to set the window 'windowed' state, for example whether it
       * is Windowed or Fullscreen, etc.
       *
       * @param [in] mode The display mode to set the window to.
       */
      void SetDisplayMode(flIN DisplayMode mode);

      /**
       * @brief Set the windows input focus
       *
       * This function can be used to take focus of different inputs,
       * e.g. Mouse or Keyboard focus.
       * 
       * @param [in] flags   FocusFlags specifying the device to set focus for.
       * @param [in] focused Whether to take focus or not.
       */
      void SetFocus(flIN FocusFlags flags, flIN bool focused);

      /**
       * Set the size of the window.
       *
       * @param [in] width  The new width of the window.
       * @param [in] height The new height of the window.
       */
      void SetSize(flIN int64_t width, flIN int64_t height);

      /**
      * Set the position of the window.
      *
      * @param [in] posX The new X position of the window.
      * @param [in] posY The new Y position of the window.
      */
      void SetPosition(flIN int64_t posX, flIN int64_t posY);
      
      /**
       * Get the window title.
       *
       * @return A c-string containing the window title. 
       */
      const char* GetTitle() const;
      
      /**
       * @brief Get the windows display mode.
       *
       * This function can be used to retrieve the display mode of this
       * window. The display mode is specifies whether the window is Windowed,
       * Fullscreen, etc.
       *
       * @return The DisplayMode of the window
       */
      DisplayMode GetDisplayMode() const;
      
      /**
       * @brief Get the focus flags.
       *
       * This function returns the input focus flags for this window. It can
       * be used to determine if this window is capturing keyboard or mouse
       * inputs.
       *
       * @return The FocusFlags for this window.
       */
      FocusFlags GetFocusFlags() const;

      /**
       * @brief Get general window flags.
       *
       * @return The Flags for this window.
       */
      Window::Flags GetFlags() const;

      /**
       * Get the size of the window.
       *
       * @param [out] pPosX 
       * @param [out] pWidth  A pointer to an int64 to copy the windows width to. Can be NULL.
       * @param [out] pHeight A pointer to an int64 to copy the windows height to. Can be NULL.
       */
      void GetSize(flOUT int64_t *pWidth, flOUT int64_t *pHeight) const;

      /**
      * Get the width of the window.
      *
      * @return The width of the window
      */
      int64_t GetWidth() const;

      /**
       * Get the height of the window.
       *
       * @return The height of the window
       */
      int64_t GetHeight() const;

      /**
       * Get the position of the window.
       *
       * @param [out] pPosX A pointer to an int64 to copy the X position to. Can be NULL.
       * @param [out] pPosY A pointer to an int64 to copy the Y position to. Can be NULL.
       */
      void GetPosition(flOUT int64_t *pPosX, flOUT int64_t *pPosY) const;

      /**
      * Get the X position of the window.
      *
      * @return The X position of the window.
      */
      int64_t GetX() const;

      /**
       * Get the Y position of the window.
       *
       * @return The Y position of the window.
       */
      int64_t GetY() const;

      /**
       * Get the windows screen rect.
       *
       * @param [out] pPosX   A pointer to an int64 to copy the X position to. Can be NULL.
       * @param [out] pPosY   A pointer to an int64 to copy the Y position to. Can be NULL.
       * @param [out] pWidth  A pointer to an int64 to copy the windows width to. Can be NULL.
       * @param [out] pHeight A pointer to an int64 to copy the windows height to. Can be NULL.
       */
      void GetRect(int64_t *pPosX, int64_t *pPosY, int64_t *pWidth, int64_t *pHeight) const;
    };

    flBITWISE_ENUM_OPERATORS(Window::FocusFlags);
    flBITWISE_ENUM_OPERATORS(Window::Flags);
  }
}

#endif // flPlatform_Window_h__
