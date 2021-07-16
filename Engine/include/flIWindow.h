#pragma once

#include "flPImpl.h"
#include "flInputs.h"
#include "flEvent.h"
#include "flPixelFormat.h"

namespace Fractal
{
  class WindowRenderTarget;

  /**
     * @brief Available Window display modes.
     */
  enum WindowDisplayMode : int64_t
  {
    WindowDisplayMode_Windowed,           ///< Windowed mode
    WindowDisplayMode_Fullscreen,         ///< Fullscreen mode
    WindowDisplayMode_FullscreenWindowed, ///< Fullscreen Windowed mode
    WindowDisplayMode_Count = 3           ///< Number of window display modes
  };

  /**
     * @brief Input focus flags
     */
  enum WindowFocusFlags : int64_t
  {
    WindowFocusFlag_None = 0,          ///< The window has no input focus
    WindowFocusFlag_Keyboard = 1 << 0, ///< The window has keyboard focus
    WindowFocusFlag_Mouse = 1 << 1,    ///< The window has mouse focus
    WindowFocusFlag_Grabbed = 1 << 2,  ///< Did the window just gain focus
    WindowFocusFlag_Count = 3          ///< Number of window focus flags
  };

  /**
     * @brief General window behavior flags
     */
  enum WindowFlags : int64_t
  {
    WindowFlag_None = 0,                                ///< Special No-Flags value
    WindowFlag_Visible = 1 << 0,                        ///< The window is visible
    WindowFlag_Resizable = 1 << 1,                      ///< The window can be resized using the borders
    WindowFlag_Borderless = 1 << 2,                     ///< The window has a border
    WindowFlag_Minimized = 1 << 3,                      ///< The window is minimized
    WindowFlag_Maximized = 1 << 4,                      ///< The window is maximized
    WindowFlag_Count = 5,                               ///< Number of window flags
    WindowFlag_Default = WindowFlag_Visible | WindowFlag_Resizable, ///< The default window flags
  };

  class flEXPORT IWindow : public Interface
  {
  public:
    /**
     * @brief Set the title of the Window.
     *
     * @param [in] title A c-string to set the window title to.
     */
    virtual void SetTitle(flIN const char *title) = 0;

    /**
     * @brief Set the display mode of the Window.
     *
     * This function can be used to set the window 'windowed' state, for example whether it
     * is Windowed or Fullscreen, etc.
     *
     * @param [in] mode The display mode to set the window to.
     */
    virtual void SetDisplayMode(flIN WindowDisplayMode mode) = 0;

    /**
     * @brief Set the windows input focus
     *
     * This function can be used to take focus of different inputs,
     * e.g. Mouse or Keyboard focus.
     *
     * @param [in] flags   FocusFlags specifying the device to set focus for.
     * @param [in] focused Whether to take focus or not.
     */
    virtual void SetFocus(flIN WindowFocusFlags flags, flIN bool focused) = 0;

    /**
     * @brief Set the size of the window.
     *
     * @param [in] width  The new width of the window.
     * @param [in] height The new height of the window.
     */
    virtual void SetSize(flIN int64_t width, flIN int64_t height) = 0;

    /**
    * @brief Set the position of the window.
    *
    * @param [in] posX The new X position of the window.
    * @param [in] posY TThe new X position of the window.
    */
    virtual void SetPosition(flIN int64_t posX, flIN int64_t posY) = 0;

    /**
    * @brief Set the windows screen rect.
    *
    * @param [in] posX   The new X position of the window.
    * @param [in] posY   The new Y position of the window.
    * @param [in] width  The new width of the window.
    * @param [in] height The new height of the window.
    */
    virtual void SetRect(flIN int64_t posX, flIN int64_t posY, flIN int64_t width, flIN int64_t height) = 0;

    /**
     * @brief Get the window title.
     *
     * @return A c-string containing the window title.
     */
    virtual const char *GetTitle() const = 0;

    /**
     * @brief Get the windows display mode.
     *
     * This function can be used to retrieve the display mode of this
     * window. The display mode is specifies whether the window is Windowed,
     * Fullscreen, etc.
     *
     * @return The DisplayMode of the window
     */
    virtual WindowDisplayMode GetDisplayMode() const = 0;

    /**
     * @brief Get the focus flags.
     *
     * This function returns the input focus flags for this window. It can
     * be used to determine if this window is capturing keyboard or mouse
     * inputs.
     *
     * @return The FocusFlags for this window.
     */
    virtual WindowFocusFlags GetFocusFlags() const = 0;

    /**
     * @brief Get general window flags.
     *
     * @return The Flags for this window.
     */
    virtual WindowFlags GetFlags() const = 0;

    /**
     * @brief Get the size of the window.
     *
     * @param [out] pPosX
     * @param [out] pWidth  A pointer to an int64 to copy the windows width to. Can be NULL.
     * @param [out] pHeight A pointer to an int64 to copy the windows height to. Can be NULL.
     */
    virtual void GetSize(flOUT int64_t *pWidth, flOUT int64_t *pHeight) const = 0;

    /**
    * @brief Get the width of the window.
    *
    * @return The width of the window
    */
    virtual int64_t GetWidth() const = 0;

    /**
     * @brief Get the height of the window.
     *
     * @return The height of the window
     */
    virtual int64_t GetHeight() const = 0;

    /**
     * @brief Get the position of the window.
     *
     * @param [out] pPosX A pointer to an int64 to copy the X position to. Can be NULL.
     * @param [out] pPosY A pointer to an int64 to copy the Y position to. Can be NULL.
     */
    virtual void GetPosition(flOUT int64_t *pPosX, flOUT int64_t *pPosY) const = 0;

    /**
    * @brief Get the X position of the window.
    *
    * @return The X position of the window.
    */
    virtual int64_t GetX() const = 0;

    /**
     * @brief Get the Y position of the window.
     *
     * @return The Y position of the window.
     */
    virtual int64_t GetY() const = 0;

    /**
     * @brief Get the windows screen rect.
     *
     * @param [out] pPosX   A pointer to an int64 to copy the X position to. Can be NULL.
     * @param [out] pPosY   A pointer to an int64 to copy the Y position to. Can be NULL.
     * @param [out] pWidth  A pointer to an int64 to copy the windows width to. Can be NULL.
     * @param [out] pHeight A pointer to an int64 to copy the windows height to. Can be NULL.
     */
    virtual void GetRect(flOUT int64_t *pPosX, flOUT int64_t *pPosY, flOUT int64_t *pWidth, flOUT int64_t *pHeight) const = 0;

    /**
     * @brief Check if the window has received a system event.
     *
     * @param [in] id    The event ID to check for.
     * @param [in] reset Set this to false if the received status should NOT be reset to false.
     */
    virtual bool ReceivedEvent(flIN EventID id, flIN bool reset = true) = 0;

    /**
     * @brief Test if this window is the source of the given event.
     *
     * @return True if this window is the source of the event.
     */
    virtual bool IsEventSource(const Event *pEvent) const = 0;

    /**
     * @brief Get the native OS handle for this window.
     *
     * @return The OS handle.
     */
    virtual void *GetNativeHandle() const = 0;

    /**
     * @brief Get the Hardware render target for this window.
     *
     * @return A pointer to a WindowRenderTarget for this window.
     */
    virtual WindowRenderTarget *GetRenderTarget() const = 0;
  };

  flBITWISE_ENUM_OPERATORS(WindowFocusFlags);
  flBITWISE_ENUM_OPERATORS(WindowFlags);
}

extern "C" {
  /**
   * @brief Create a new window.
   *
   * @param [in] title       A c-string to use as the title. This will be copied so it may be destroyed after calling this function.
   * @param [in] flags       A set of initial flags for this window.
   * @param [in] displayMode The initial display mode for this window (e.g. Windowed or Fullscreen).
   */
  flEXPORT Fractal::IWindow * Fractal_CreateWindow(flIN char const * title, flIN Fractal::WindowFlags flags, flIN Fractal::WindowDisplayMode displayMode);

  /**
   * @brief Get a pointer to the window that has focus.
   *
   * @param [in] focusFlags Flags specifying the type of focus to check
   *
   * @return A pointer to the Window that has focus
   */
  flEXPORT Fractal::IWindow * Fractal_GetFocusedWindow(flIN Fractal::WindowFocusFlags focusFlags);
}
