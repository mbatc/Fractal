#pragma once

#include "flPImpl.h"
#include "flInputs.h"
#include "flEvent.h"
#include "flPixelFormat.h"

namespace Fractal
{
  class WindowRenderTarget;

  class Impl_Window;

  class flEXPORT Window : public Interface
  {
    flPIMPL_DEF(Window);

  public:
    /**
     * @brief Available Window display modes.
     */
    enum DisplayMode : int64_t
    {
      DM_Windowed,           ///< Windowed mode
      DM_Fullscreen,         ///< Fullscreen mode
      DM_FullscreenWindowed, ///< Fullscreen Windowed mode
      DM_Count = 3           ///< Number of window display modes
    };

    /**
     * @brief Input focus flags
     */
    enum FocusFlags : int64_t
    {
      FF_None = 0,          ///< The window has no input focus
      FF_Keyboard = 1 << 0, ///< The window has keyboard focus
      FF_Mouse = 1 << 1,    ///< The window has mouse focus
      FF_Grabbed = 1 << 2,  ///< Did the window just gain focus
      FF_Count = 3          ///< Number of window focus flags
    };

    /**
     * @brief General window behavior flags
     */
    enum Flags : int64_t
    {
      Flag_None = 0,            ///< Special No-Flags value
      Flag_Visible = 1 << 0,    ///< The window is visible
      Flag_Resizable = 1 << 1,  ///< The window can be resized using the borders
      Flag_Borderless = 1 << 2, ///< The window has a border
      Flag_Minimized = 1 << 3,  ///< The window is minimized
      Flag_Maximized = 1 << 4,  ///< The window is maximized
      Flag_TopMost = 1 << 5,    ///< The window is always draw on top on non top-most windows.
      Flag_NoIcon = 1 << 6,     ///< The window does not have an icon on the task bar.
      Flag_Count = 7,           ///< Number of window flags
      Flag_Default = Flag_Visible | Flag_Resizable, ///< The default window flags
    };

    /**
     * @brief Create a new window.
     *
     * @param [in] title       A c-string to use as the title. This will be copied so it may be destroyed after calling this function.
     * @param [in] flags       A set of initial flags for this window.
     * @param [in] displayMode The initial display mode for this window (e.g. Windowed or Fullscreen).
     * @param [in] pParent
     */
    static Window* Create(flIN const char* title, flIN Flags flags, flIN DisplayMode displayMode, Window* pParent = nullptr);

    /**
     * @brief Create a new window.
     *
     * @param [in] title       A c-string to use as the title. This will be copied so it may be destroyed after calling this function.
     * @param [in] flags       A set of initial flags for this window.
     * @param [in] displayMode The initial display mode for this window (e.g. Windowed or Fullscreen).
     * @param [in] pParent
     */
    Window(flIN const char* title, flIN Flags flags, flIN DisplayMode displayMode, Window* pParent = nullptr);

    /**
     * @brief Set the title of the Window.
     *
     * @param [in] title A c-string to set the window title to.
     */
    void SetTitle(flIN const char* title);

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
     * @brief Set the size of the window.
     *
     * @param [in] width  The new width of the window.
     * @param [in] height The new height of the window.
     */
    void SetSize(flIN int64_t width, flIN int64_t height);

    /**
    * @brief Set the position of the window.
    *
    * @param [in] posX The new X position of the window.
    * @param [in] posY TThe new X position of the window.
    */
    void SetPosition(flIN int64_t posX, flIN int64_t posY);

    /**
    * @brief Set the windows screen rect.
    *
    * @param [in] posX   The new X position of the window.
    * @param [in] posY   The new Y position of the window.
    * @param [in] width  The new width of the window.
    * @param [in] height The new height of the window.
    */
    void SetRect(flIN int64_t posX, flIN int64_t posY, flIN int64_t width, flIN int64_t height);

    /**
     * @brief Set this windows parent.
     */
    void SetParent(flIN Window* pParent);

    /**
     * @brief Get this windows parent.
     */
    Window* GetParent() const;

    /**
     * @brief Get the window title.
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
    Flags GetFlags() const;

    /**
     * @brief Update the windows Flags.
     *
     * @param [in] flags The new flags to apply to the window
     */
    void SetFlags(flIN Flags flags);

    /**
     * @brief Add flags to the window.
     */
    void AddFlags(flIN Flags flags);

    /**
     * @brief Remove flags from the window.
     */
    void RemoveFlags(flIN Flags flags);

    /**
     * @brief Bring the window to the front of focus
     */
    void BringToFocus();

    /**
     * @brief Get the size of the window.
     *
     * @param [out] pPosX
     * @param [out] pWidth  A pointer to an int64 to copy the windows width to. Can be NULL.
     * @param [out] pHeight A pointer to an int64 to copy the windows height to. Can be NULL.
     */
    void GetSize(flOUT int64_t* pWidth, flOUT int64_t* pHeight) const;

    /**
    * @brief Get the width of the window.
    *
    * @return The width of the window
    */
    int64_t GetWidth() const;

    /**
     * @brief Get the height of the window.
     *
     * @return The height of the window
     */
    int64_t GetHeight() const;

    /**
     * @brief Get the position of the window.
     *
     * @param [out] pPosX A pointer to an int64 to copy the X position to. Can be NULL.
     * @param [out] pPosY A pointer to an int64 to copy the Y position to. Can be NULL.
     */
    void GetPosition(flOUT int64_t* pPosX, flOUT int64_t* pPosY) const;

    /**
    * @brief Get the X position of the window.
    *
    * @return The X position of the window.
    */
    int64_t GetX() const;

    /**
     * @brief Get the Y position of the window.
     *
     * @return The Y position of the window.
     */
    int64_t GetY() const;

    /**
     * @brief Get the windows screen rect.
     *
     * @param [out] pPosX   A pointer to an int64 to copy the X position to. Can be NULL.
     * @param [out] pPosY   A pointer to an int64 to copy the Y position to. Can be NULL.
     * @param [out] pWidth  A pointer to an int64 to copy the windows width to. Can be NULL.
     * @param [out] pHeight A pointer to an int64 to copy the windows height to. Can be NULL.
     */
    void GetRect(flOUT int64_t* pPosX, flOUT int64_t* pPosY, flOUT int64_t* pWidth, flOUT int64_t* pHeight) const;

    /**
     * @brief Check if the window has received a system event.
     *
     * @param [in] id    The event ID to check for.
     * @param [in] reset Set this to false if the received status should NOT be reset to false.
     */
    bool ReceivedEvent(flIN EventID id, flIN bool reset = true);

    /**
     * @brief Test if this window is the source of the given event.
     *
     * @return True if this window is the source of the event.
     */
    bool IsEventSource(const Event* pEvent) const;

    /**
     * @brief Get the native OS handle for this window.
     *
     * @return The OS handle.
     */
    void* GetNativeHandle() const;

    /**
     * @brief Get the Hardware render target for this window.
     *
     * @return A pointer to a WindowRenderTarget for this window.
     */
    WindowRenderTarget* GetRenderTarget() const;

    /**
     * @brief Get a pointer to the window that has focus.
     *
     * @param [in] focusFlags Flags specifying the type of focus to check
     *
     * @return A pointer to the Window that has focus
     */
    static Window* GetFocusedWindow(flIN FocusFlags focusFlags);

    static Window* GetForegroundWindow();
  };

  flBITWISE_ENUM_OPERATORS(Window::FocusFlags);
  flBITWISE_ENUM_OPERATORS(Window::Flags);
}
