#ifndef flPlatform_Event_h__
#define flPlatform_Event_h__

#include "../flInterface.h"
#include "flPlatform_NativeEvent.h"

namespace flEngine
{
  namespace Platform
  {
    /**
     * List of event type groupings.
     */
    enum EventType : int64_t
    {
      E_Type_System = 1 << 0,   ///< General system events
      E_Type_Window = 1 << 1,   ///< Window related events
      E_Type_Keyboard = 1 << 2, ///< Keyboard related events
      E_Type_Mouse = 1 << 3,    ///< Mouse related events
      E_Type_User = 1 << 4,     ///< Custom user event
      E_Type_All = INT64_MAX,
    };

    /**
     * Supported OS events.
     */
    enum EventID : int64_t
    {
      // System Events
      E_Sys_Quit,         ///< A request to quit the application 
      E_Sys_ThemeChanged, ///< The system theme was changed

      // Window Events
      E_Wnd_Create,       ///< The window is being created
      E_Wnd_Close,        ///< A request to close a window
      E_Wnd_Destroy,      ///< The window is being destroyed
      E_Wnd_DpiChanged,   ///< DPI context has changed
      E_Wnd_Moving,       ///< Window is being moved
      E_Wnd_Sizing,       ///< Window is being resized
      E_Wnd_Show,         ///< Window is about to be hidden/shown
      E_Wnd_StyleChanged, ///< The windows style was modified
      E_Wnd_RectUpdated,  ///< The windows position or size has been modified
      E_Wnd_Activate,     ///< The a windows keyboard focus has changed

      // Keyboard Events
      E_Kbd_KeyState,     ///< A keys state has changed
      E_Kbd_ASCII,        ///< Receive the character code of a pressed key (ASCII)
      E_Kbd_Unicode,      ///< Receive the character code of a pressed key (unicode)
      E_Kbd_KillFocus,    ///< Keyboard focus was lost
      E_Kbd_SetFocus,     ///< Keyboard focus was gained

      // Mouse Events
      E_Mse_State,        ///< A mouse buttons state has changed
      E_Mse_Move,         ///< The mouse pointer was moved
      E_Mse_Scroll,       ///< The mouse wheel was scrolled

      // Custom User Events
      E_Usr_Custom,       ///< Start value for custom events. Custom events should be greater than this value
    };

    /**
     * @brief Event struct that contains data for supported system events.
     * 
     * This class consists of a collection of interfaces that specify the parameters
     * for various system events. These are implemented using a union, so that the same
     * event class can be used for every event type.
     * 
     * There is also a pUserEvent field that can be used to pass a pointer custom event data.
     */
    struct flEXPORT Event
    {
      /**
       * @brief Get the event ID
       *
       * The ID of the event. This value will correspond to Event ID's are group together based on the system that sent
       * the event (e.g. Window, Input, etc). Theses groups are defined by EventType.
       */
      int64_t id;

      /**
       * @brief Get the event type
       *
       * The Type of the event. Event types  are group together based on the system that sen
       * the event (e.g. Window, Input, etc)
       */
      int64_t type;

      union
      {
        struct SysQuit
        {
          int64_t code; ///< The exit code posted by the system
        } sysQuit;      ///< System quit event data

        struct SysThemeChanged
        {
        } sysThemeChanged; ///< System theme changed event data

        struct WndCreate
        {
          const char *name; ///< The name of the new window
          int64_t x;        ///< The X position of the new window
          int64_t y;        ///< The Y position of the new window
          int64_t width;    ///< The width of the new window
          int64_t height;   ///< The height of the new window
          int64_t style;    ///< The style of the window
        } wndCreate; ///< Window create event data

        struct WndClose
        {
        } wndClose; ///< Window close event data

        struct WndDestroy
        {
        } wndDestroy;  ///< Window destroy event data

        struct WndDpiChanged
        {
          int64_t dpiX;            ///< The new DPI in the x-direction
          int64_t dpiY;            ///< The new DPI in the y-direction
          int64_t suggestedX;      ///< Recommended X position for the window
          int64_t suggestedY;      ///< Recommended Y position for the window
          int64_t suggestedWidth;  ///< Recommended width position for the window
          int64_t suggestedHeight; ///< Recommended height position for the window
        } wndDpiChanged;  ///< Window DPI changed event data

        struct WndMoving
        {
          int64_t x; ///< The x position of the window
          int64_t y; ///< The y position of the window
        } wndMoving; ///< Window moved event data

        struct WndSizing
        {
          int64_t width;  ///< The new width of the window
          int64_t height; ///< The new height of the window
        } wndSizing; ///< Window resized event data

        struct WndShow
        {
          bool isShown; ///< Visible state of the window
        } wndShow; ///< Window visibility state event data

        struct WndStyleChanged
        {
          int64_t newStyle; ///< The new window style
          int64_t oldStyle; ///< The previous window style
        } wndStyleChanged; ///< Window style changed event data

        struct WndRectUpdated
        {
          int64_t x;      ///< The x position of the window
          int64_t y;      ///< The y position of the window
          int64_t width;  ///< The width position of the window
          int64_t height; ///< The height position of the window
        } wndRectUpdated; ///< Window resized or moved event data

        struct WndActive
        {
          bool isActive;       ///< Is the window focused
          bool mouseActivated; ///< Is activated via a mouse interaction
        } wndActive; ///< Window focus changed event data

        struct KbdState
        {
          int64_t keyCode; ///< The id of the key pressed
          bool isDown;     ///< Is the key down
        } kbdState; ///< Keyboard key state event data

        struct KbdChar
        {
          wchar_t character;
        } kbdASCII; ///< Keyboard text input event data

        struct KbdKillFocus
        {
        } kbdKillFocus; ///< Window lost keyboard focus event data

        struct KbdSetFocus
        {
        } kbdSetFocus;  ///< Window gained keyboard focus event data

        struct MseState
        {
          int64_t button; ///< The index of the button pressed
          bool isDown;    ///< Is the button down
        } mseState; ///< Mouse button state event data

        struct MseMove
        {
          int64_t x; ///< The x position of the mouse
          int64_t y; ///< The y position of the mouse
        } mseMove; ///< Mouse moved event data

        struct MseScroll
        {
          bool isHorizontal; ///< The mouse scroll direction
          int64_t amount;    ///< The mouse scroll amount ('+' away from used, '-' towards user)
        } mseScroll; ///< Mouse scroll event data

        struct UserEvent
        {
          void *pData;                  ///< Custom event data pointer
          void (*DestroyFunc)(Event *); ///< Custom event destroy callback (This should be used to cleanup custom event data)
        } userEvent; ///< Custom user event data
      };

      /**
       * @brief Get the native OS event data.
       *
       * Return a pointer to the OS event which was received.
       */
      NativeEvent nativeEvent;
    };

    /**
     * @brief Create an Event from a native system event.
     *
     * This function will create a event based on the native event passed.
     * The instanced returned will be of one of the derived Event implementations
     * (e.g. Events::WindowSize).
     * 
     * @param [out] pEvent A pointer to the the Event struct to fill out
     * @param [in]  pNativeEvent A pointer to the NativeEvent struct containing the system event to translate.
     */
    void flCCONV Event_Create(flOUT Event *pEvent, flIN NativeEvent *pNativeEvent);

    /**
     * @brief Create an Event from a user event pointer.
     *
     * This function will create a user event and assign the pUserEvent ptr to
     * the Events internal pUserEvent member.
     *
     * @param [out] pEvent A pointer to the the Event struct to fill out
     * @param [in] pData A pointer to the custom events data (if needed)
     * @param [in] DestroyFunc A pointer to a function to call when destroying the event. This can be used to
     *             cleanup the event data.
     */
    void flCCONV Event_Create(flOUT Event *pEvent, flIN void *pData, void (*DestroyFunc)(Event *));

    /**
     * @brief Destroy an event struct.
     * 
     * This function is used to perform any cleanup required for an event type.
     * 
     * @param [in, out] pEvent The event to destroy.
     */
    void flCCONV Event_Destroy(flIN flOUT Event *pEvent);
  }
}

#endif // flPlatform_Event_h__
