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
      E_Type_System = 1 << 0,
      E_Type_Window = 1 << 1,
      E_Type_Keyboard = 1 << 2,
      E_Type_Mouse = 1 << 3,
      E_Type_User = 1 << 4,
      E_Type_All = INT64_MAX,
    };

    /**
     * Supported OS events.
     */
    enum EventID : int64_t
    {
      // System Events
      E_Sys_Quit,         // A request to quit the application 
      E_Sys_ThemeChanged, // The system theme was changed

      // Window Events
      E_Wnd_Create,       // The window is being created
      E_Wnd_Close,        // A request to close a window
      E_Wnd_Destroy,      // The window is being destroyed
      E_Wnd_DpiChanged,   // DPI context has changed
      E_Wnd_Moving,       // Window is being moved
      E_Wnd_Sizing,       // Window is being resized
      E_Wnd_Show,         // Window is about to be hidden/shown
      E_Wnd_StyleChanged, // The windows style was modified
      E_Wnd_RectUpdated,  // The windows position or size has been modified
      E_Wnd_Activate, // The a windows keyboard focus has changed

      // Keyboard Events
      E_Kbd_KeyState,     // A keys state has changed
      E_Kbd_ASCII,        // Receive the character code of a pressed key (ASCII)
      E_Kbd_Unicode,      // Receive the character code of a pressed key (unicode)
      E_Kbd_KillFocus,    // Keyboard focus was lost
      E_Kbd_SetFocus,     // Keyboard focus was gained

      // Mouse Events
      E_Mse_State,        // A mouse buttons state has changed
      E_Mse_Move,         // The mouse pointer was moved
      E_Mse_Scroll,       // The mouse wheel was scrolled

      // Custom User Events
      E_Usr_Custom,       // Start value for custom events
    };

    /**
     * @brief Event class that contains data for supported system events.
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
       * Get the ID of the event. This value will correspond to Event ID's are group together based on the system that sent
       * the event (e.g. Window, Input, etc). Theses groups are defined by EventType.
       */
      int64_t id;

      /**
       * @brief Get the event type
       *
       * Get the Type of the event. Event types  are group together based on the system that sen
       * the event (e.g. Window, Input, etc)
       */
      int64_t type;

      union
      {
        struct SysQuit
        {
          int64_t code;
        } sysQuit;

        struct SysThemeChanged
        {
        } sysThemeChanged;

        struct WndCreate
        {
          const char *name;
          int64_t x;
          int64_t y;
          int64_t width;
          int64_t height;
        } wndCreate;

        struct WndClose
        {
        } wndClose;

        struct WndDestroy
        {
        } wndDestroy;

        struct WndDpiChanged
        {
          int64_t dpiX;
          int64_t dpiY;
          int64_t suggestedX;
          int64_t suggestedY;
          int64_t suggestedWidth;
          int64_t suggestedHeight;
        } wndDpiChanged;

        struct WndMoving
        {
          int64_t x;
          int64_t y;
        } wndMoving;

        struct WndSizing
        {
          int64_t width;
          int64_t height;
        } wndSizing;

        struct WndShow
        {
          bool isShown;
        } wndShow;

        struct WndStyleChanged
        {
          int64_t newStyle;
          int64_t oldStyle;
        } wndStyleChanged;

        struct WndRectUpdated
        {
          int64_t x;
          int64_t y;
          int64_t width;
          int64_t height;
        } wndRectUpdated;

        struct WndActive
        {
          bool isActive;
          bool mouseActivated;
        } wndActive;

        struct WndMouseFocus
        {
          bool isFocused;
        } wndMouseFocus;

        struct KbdState
        {
          int64_t keyCode;
          bool isDown;
        } kbdState;

        struct KbdASCII
        {
          char character;
        } kbdASCII;

        struct KbdUnicode
        {
        public:
          wchar_t character;
        } kbdUnicode;

        struct KbdKillFocus
        {
        } kbdKillFocus;

        struct KbdSetFocus
        {
        } kbdSetFocus;

        struct MseState
        {
          int64_t button;
          bool isDown;
        } mseState;

        struct MseMove
        {
          int64_t x;
          int64_t y;
        } mseMove;

        struct MseScroll
        {
          bool isHorizontal;
          int64_t amount;
        } mseScroll;

        struct UserEvent
        {
          void *pData;
          void (*DestroyFunc)(Event *);
        } userEvent;
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
     */
    void flCCONV Event_Create(flOUT Event *pEvent, flIN NativeEvent *pNativeEvent);

    /**
     * @brief Create an Event from a user event pointer.
     *
     * This function will create a user event and assign the pUserEvent ptr to
     * the Events internal pUserEvent member.
     */
    void flCCONV Event_Create(flOUT Event *pEvent, flIN void *pData, void (*DestroyFunc)(Event *));

    /**
     * @brief Destroy an event struct.
     * 
     * This function is used to perform any cleanup required for an event type.
     * 
     */
    void flCCONV Event_Destroy(flOUT Event *pEvent);
  }
}

#endif // flPlatform_Event_h__
