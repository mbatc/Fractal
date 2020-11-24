#ifndef fl_Input_InputDevice_h__
#define fl_Input_InputDevice_h__

#include "../flConfig.h"
#include "../flPImpl.h"
#include "flInputDeviceServer.h"

namespace flEngine
{
  namespace Input
  {
    class flPIMPL_CLASS(InputDevice);

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
         *
         */
        bool IsPressed() const;

        /**
         *
         */
        bool IsReleased() const;

        /**
         *
         */
        bool IsDown() const;

      protected:
        int64_t m_downTime     = 0;
        int64_t m_pressedTime  = 0;
        int64_t m_releasedTime = 0;

        bool m_down     = false;
        bool m_pressed  = false;
        bool m_released = false;
      };

      class Analog
      {
        friend InputDevice;

      public:
        /**
         *
         */
        float GetValue() const;

        /**
         *
         */
        float GetDelta() const;

        /**
         *
         */
        bool HasChanged() const;

      protected:
        int64_t m_valueTime     = 0;
        int64_t m_lastValueTime = 0;

        float m_value     = 0;
        float m_lastValue = 0;
      };

      /**
       * @brief Create a new input device.
       *
       * Create a new input device and specify how many buttons and analog
       * inputs it has.
       *
       * @param [in] buttonCount How many button (digital) inputs to allocate for this device
       * @param [in] analogCount How many analog inputs to allocate for this device
       */
      InputDevice(flIN int64_t buttonCount, flIN int64_t analogCount, flIN InputDeviceServer *pServer = nullptr);
      
      /**
       *
       */
      int64_t GetButtonCount() const;

      /**
       *
       */
      int64_t GetAnalogCount() const;

      /**
       *
       */
      Button* GetButton(flIN int64_t index);

      /**
       *
       */
      Button* GetButton(flIN const char *name);

      /**
       *
       */
      Analog* GetAnalog(flIN int64_t index);

      /**
       *
       */
      Analog* GetAnalog(flIN const char *name);

      /**
       *
       */
      const Button* GetButton(flIN int64_t index) const;

      /**
       *
       */
      const Button* GetButton(flIN const char *name) const;

      /**
       *
       */
      const Analog* GetAnalog(flIN int64_t index) const;

      /**
       *
       */
      const Analog* GetAnalog(flIN const char *name) const;

      /**
       *
       */
      bool AddButtonName(flIN int64_t index, flIN const char *name);

      /**
       *
       */
      bool AddAnalogName(flIN int64_t index, flIN const char *name);

      /**
       *
       */
      bool RemoveButtonName(flIN const char *name);

      /**
       *
       */
      bool RemoveAnalogName(flIN const char *name);

      /**
       *
       */
      int64_t GetButtonNameCount(flIN int64_t index) const;

      /**
       *
       */
      const char* GetButtonName(flIN int64_t buttonIndex, flIN int64_t nameIndex) const;

      /**
       *
       */
      int64_t GetAnalogNameCount(flIN int64_t index) const;

      /**
       *
       */
      const char* GetAnalogName(flIN int64_t buttonIndex, flIN int64_t nameIndex) const;

      /**
       *
       */
      int64_t GetButtonIndex(flIN const char *name) const;

      /**
       *
       */
      int64_t GetAnalogIndex(flIN const char *name) const;

      /**
      * @brief Set the input server for this device.
      *
      * This function can be used to set the input event server for this input device.
      * This can be used to use custom input event servers with an input device. This
      * might be helpful when emulating inputs for various devices.
      *
      * @param [in] pServer A pointer to the input server to use.
      */
      void SetServer(flIN InputDeviceServer *pServer);

      /**
      * @brief Get this input devices event server.
      *
      * @return A pointer to this devices input server.
      */
      InputDeviceServer* GetServer() const;

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
      virtual void OnUpdate();
    };
  }
}

#endif // flInputDevice_h__
