#ifndef fl_Input_Mouse_h__
#define fl_Input_Mouse_h__

#include "flInputDevice.h"
#include "../math/flMath.h"
#include "../platform/flEvent.h"

namespace flEngine
{
  namespace Input
  {
    /**
     * @brief Valid Buttons for the Mouse input device
     */
    enum MouseButton
    {
      MB_Left,                ///< The left mouse button.
      MB_Right,               ///< The right mouse button.
      MB_Middle,              ///< The middle mouse button.
      MB_Count,               ///< The number of standard mouse buttons.

      MB_Extended = MB_Count, ///< The start ID for extended mouse buttons.
      MB_ExtendedCount = 16,  ///< The number supported extended mouse buttons.
    };

    /**
     * @brief Valid Analog inputs for the Mouse input device.
     */
    enum MouseAxis
    {
      MA_XPos,    ///< The X position of the mouse cursor.
      MA_YPos,    ///< The Y position of the mouse cursor.
      MA_HScroll, ///< The horizontal scroll of the scroll wheel.
      MA_VScroll, ///< The vertical scroll of the scroll wheel.
      MA_Count,   ///< The number of analog inputs
    };

    /**
     * @brief An input device interface for to the mouse.
     *
     * 
     * This input device, by default, receives global mouse events from the
     * OS. Creating an instance of this class will allow you to query any mouse
     * inputs received by a Window created by Fractal Engine.
     */
    class flEXPORT Mouse : public InputDevice
    {
    public:
      /**
       * @brief Create a mouse input device.
       */
      Mouse();

      /**
       * @brief Get the 'Down' state of a mouse button.
       *
       * A key is 'Down' when the it is pressed and held i.e. if a button is pressed,
       * it will be 'Down' until it is released.
       *
       * @param [in] button The MouseButton to check.
       *
       * @return True if the button specified is down, otherwise false.
       */
      bool GetDown(flIN MouseButton button) const;

      /**
       * @brief Get the 'Pressed' state of a mouse button.
       *
       * A button is 'Pressed' when the its state goes from Up to Down.
       *
       * @param [in] button The MouseButton to check.
       *
       * @return True if the button specified is pressed, otherwise false.
       */
      bool GetPressed(flIN MouseButton button) const;

      /**
       * @brief Get the 'Pressed' state of a mouse button.
       *
       * A button is 'Pressed' when the its state goes from Up to Down.
       *
       * @param [in] button The MouseButton to check.
       *
       * @return True if the button specified is pressed, otherwise false.
       */
      bool GetReleased(flIN MouseButton button) const;

      /**
       * @brief Get the X position of the mouse cursor.
       *
       * @return The X position of the mouse cursor.
       */
      float GetX() const;

      /**
       * @brief Get the Y position of the mouse cursor.
       *
       * @return The X position of the mouse cursor.
       */
      float GetY() const;

      /**
       * @brief Get the mouse cursor's change in X position since the last update.
       *
       * @return The change in X position of the mouse cursor.
       */
      float GetXDelta() const;

      /**
       * @brief Get the mouse cursor's change in Y position since the last update.
       *
       * @return The change in Y position of the mouse cursor.
       */
      float GetYDelta() const;

      /**
       * @brief Get the horizontal scroll value of the mouse wheel.
       *
       * @return The horizontal scroll value.
       */
      float GetScrollH() const;

      /**
       * @brief Get the vertical scroll value of the mouse wheel.
       *
       * @return The vertical scroll value.
       */
      float GetScrollV() const;

      /**
       * @brief Get the change in horizontal scroll since the last update.
       *
       * @return The change in horizontal scroll.
       */
      float GetScrollHDelta() const;

      /**
      * @brief Get the change in vertical scroll since the last update.
      *
      * @return The change in vertical scroll.
      */
      float GetScrollVDelta() const;

      /**
       * @brief Get the x,y position of the mouse cursor.
       *
       * @return The x,y position.
       */
      Math::flVec2F GetPosition() const;

      /**
      * @brief Get the change in x,y position of the mouse cursor.
      *
      * @return The change in x,y position.
      */
      Math::flVec2F GetPositionDelta() const;

      /**
      * @brief Get the horizontal and vertical scroll of the mouse wheel.
      *
      * @return The horizontal and vertical scroll.
      */

      Math::flVec2F GetScroll() const;
      /**
      * @brief Get the change in horizontal and vertical scroll of the mouse wheel.
      *
      * @return The change in horizontal and vertical scroll.
      */
      Math::flVec2F GetScrollDelta() const;

      /**
       * @brief The default Mouse event handler.
       *
       * This is the default event handler that can be used to forward system mouse
       * events to a mouse's InputDeviceServer.
       *
       * @param [in]  pEvent       The event to handle.
       * @param [out] pInputServer A pointer to an InputDeviceServer.
       */
      static void EventHandler(flIN Platform::Event *pEvent, flIN void *pUserData);

    protected:
      void OnPostUpdate() override;
    };
  }
}

#endif // fl_Input_Mouse_h__
