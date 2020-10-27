#ifndef flPlatform_Event_h__
#define flPlatform_Event_h__

#include "../flInterface.h"
#include "flPlatform_NativeEvent.h"

namespace flEngine
{
  namespace Platform
  {
    class flEXPORT Event : public Interface
    {
    public:
      /**
       * @brief Create an Event from a native system event.
       * 
       * This function will create a event based on the native event passed.
       * The instanced returned will be of one of the derived Event implementations
       * (e.g. Events::WindowSize).
       */
      static Event* flCCONV Create(NativeEvent *pNativeEvent);

      /**
       * @brief Get the event ID
       * 
       * Get the ID of the event. This value will correspond to Event ID's are group together based on the system that sent
       * the event (e.g. Window, Input, etc). Theses groups are defined by EventType.
       */
      virtual int64_t GetEventID() const = 0;

      /**
       * @brief Get the event type
       *
       * Get the Type of the event. Event types  are group together based on the system that sen
       * the event (e.g. Window, Input, etc)
       */
      virtual int64_t GetEventType() const = 0;

      /**
       * @brief Get the native OS event data.
       * 
       * Return a pointer to the OS event which was received.
       */
      virtual const NativeEvent* GetNativeEvent() const = 0;
    };

    /**
     * List of event type groupings.
     */
    enum EventType : int64_t
    {
      E_Type_System   = 1 << 0,
      E_Type_Window   = 1 << 1,
      E_Type_Keyboard = 1 << 2,
      E_Type_Mouse    = 1 << 3,
      E_Type_All      = INT64_MAX,
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
      E_Wnd_ShowWindow,   // Window is about to be hidden/shown
      E_Wnd_StyleChanged, // The windows style was modified
      E_Wnd_RectUpdated,  // The windows position or size has been modified
      E_Wnd_KeyoardFocus, // The a windows keyboard focus has changed
      E_Wnd_MouseFocus,   // The a windows mouse focus has changed

      // Keyboard Events
      E_Kbd_Down,         // A key was pressed
      E_Kbd_Up,           // A key was released
      E_Kbd_ASCII,        // Receive the character code of a pressed key (ASCII)
      E_Kbd_Unicode,      // Receive the character code of a pressed key (unicode)
      E_Kbd_KillFocus,    // Keyboard focus was lost
      E_Kbd_SetFocus,     // Keyboard focus was gained

      // Mouse Events
      E_Mse_Up,           // A mouse button is up
      E_Mse_Down,         // A mouse button is down
      E_Mse_Move,         // The mouse pointer was moved
      E_Mse_Scroll,       // The mouse wheel was scrolled

      // Custom User Events
      E_Usr_Custom,       // Start value for custom events
    };
  }
}

#endif // flPlatform_Event_h__
