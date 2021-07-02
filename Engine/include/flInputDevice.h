#pragma once

#include "flConfig.h"
#include "flPImpl.h"
#include "flInputDeviceServer.h"

namespace Fractal
{
  class Impl_InputDevice;

  /**
   * @brief A generic interface for an input device.
   *
   * Input devices can consist of any number of digital or analog inputs. In
   * this interface, digital signals are 'Buttons'.
   *
   * This class allows an input to be defined by linking an integer ID to a
   * button, or analog input.
   */
  class flEXPORT InputDevice
  {
    flPIMPL_DEF(InputDevice);

  public:
    class Button
    {
      friend InputDevice;

    public:
      /**
       * @brief Get the 'Pressed' state of the button.
       *
       * A Button is 'Pressed' when the its state goes from Up to Down.
       *
       * @return True if the button is pressed, otherwise false.
       */
      bool IsPressed() const;

      /**
       * @brief Get the 'Released' state of the button.
       *
       * A Button is 'Released' when the its state goes from Down to Up.
       *
       * @return True if the button is released, otherwise false.
       */
      bool IsReleased() const;

      /**
       * @brief Get the 'Down' state of the button.
       *
       * A Button is 'Down' when the it is pressed and held i.e. if a Button is pressed,
       * it will be down until it is released.
       *
       * @return True if the button is down, otherwise false.
       */
      bool IsDown() const;

    protected:
      int64_t m_downTime = 0;
      int64_t m_pressedTime = 0;
      int64_t m_releasedTime = 0;

      bool m_down = false;
      bool m_pressed = false;
      bool m_released = false;
    };

    class Analog
    {
      friend InputDevice;

    public:
      /**
       * @brief Get the input current value.
       *
       * @return The current value of the input.
       */
      float GetValue() const;

      /**
       * @brief Get the change in the value since the last update.
       *
       * @return The change in the value.
       */
      float GetDelta() const;

      /**
       * @brief Check if the value was changed in the last update.
       *
       * @return True if the value has changed, otherwise false.
       */
      bool HasChanged() const;

    protected:
      int64_t m_valueTime = 0;
      int64_t m_lastValueTime = 0;

      float m_value = 0;
      float m_lastValue = 0;
    };

    /**
     * @brief Create a new InputDevice.
     *
     * Create a new input device and specify how many buttons and analog
     * inputs it has.
     *
     * @param [in] buttonCount How many button (digital) inputs to allocate for this device
     * @param [in] analogCount How many analog inputs to allocate for this device
     * @param [in] pServer     The InputDeviceServer to use when updating the input device state.
     */
    InputDevice(flIN int64_t buttonCount, flIN int64_t analogCount, flIN InputDeviceServer* pServer = nullptr);

    /**
     * @brief Get the number of buttons this InputDevice interface has.
     *
     * @return The number of buttons in the interface.
     */
    int64_t GetButtonCount() const;

    /**
     * @brief Get the number of analog inputs this InputDevice interface has.
     *
     * @return The number of analog inputs in the interface.
     */
    int64_t GetAnalogCount() const;

    /**
     * @brief Access a button in the InputDevice.
     *
     * @param [in] index The index of the Button, where 0 <= index < GetButtonCount().
     */
    Button* GetButton(flIN int64_t index);

    /**
    * @brief Access an analog input in the InputDevice.
    *
    * @param [in] index The index of the an analog input, where 0 <= index < GetAnalogCount().
    */
    Analog* GetAnalog(flIN int64_t index);

    /**
    * @brief Immutable access to a button in the InputDevice.
    *
    * @param [in] index The index of the Button, where 0 <= index < GetButtonCount().
    */
    const Button* GetButton(flIN int64_t index) const;

    /**
    * @brief Immutable access to an analog input in the InputDevice.
    *
    * @param [in] index The index of the an analog input, where 0 <= index < GetAnalogCount().
    */
    const Analog* GetAnalog(flIN int64_t index) const;

    /**
    * @brief Set the input server for this device.
    *
    * This function can be used to set the input event server for this input device.
    * This can be used to use custom input event servers with an input device. This
    * might be helpful when emulating inputs for various devices.
    *
    * @param [in] pServer A pointer to the input server to use.
    */
    void SetServer(flIN InputDeviceServer* pServer);

    /**
    * @brief Get this input devices event server.
    *
    * @return A pointer to this devices input server.
    */
    InputDeviceServer* GetServer();
    InputDeviceServer const* GetServer() const;

    /**
    * @brief Update the input device.
    *
    * Updating the input device will process the events queued in the server event queue.
    * One thing to note is if a button was pressed and released between a call to Update(),
    * both the IsPressed() and IsReleased() functions will return true.
    */
    void Update();

    /**
     * @brief Get the number of registered devices.
     *
     * @return The number of registered devices.
     */
    static int64_t GetRegisteredDeviceCount();

    /**
     * @brief Get a registered device.
     *
     * @param [in] index The index of the device. This should be >= 0 and < GetRegisteredDeviceCount()
     */
    static InputDevice* GetRegisteredDevice(flIN int64_t index);

  protected:
    /**
     * @brief Performs any pre-update steps for the input device.
     *
     * This function is called during the Update, BEFORE processing any events
     * from the input server.
     *
     * This function should be overridden to perform any necessary processing BEFORE
     * updating the device state.
     */
    virtual void OnPreUpdate();

    /**
     * @brief Performs any post-update steps for the input device.
     *
     * This function is called during the Update, AFTER processing all events
     * from the input server.
     *
     * This function should be overridden to perform any necessary processing AFTER
     * updating the device state.
     */
    virtual void OnPostUpdate();
  };
}
