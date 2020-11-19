#ifndef fl_Input_InputDevice_h__
#define fl_Input_InputDevice_h__

#include "../flConfig.h"
#include "../flPImpl.h"

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
      public:
        bool IsPressed() const;
        bool IsReleased() const;
        bool IsDown() const;

        void Set(bool down);

      protected:
        bool m_down = false;
        bool m_lastDown = false;
      };

      class Analog
      {
      public:
        float GetValue() const;
        float GetDelta() const;
        bool HasChanged() const;

        void SetValue(float newValue);

      protected:
        float m_value = 0;
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
      InputDevice(flIN int64_t buttonCount, flIN int64_t analogCount);

      int64_t GetButtonCount() const;
      int64_t GetAnalogCount() const;

      Button* GetButton(int64_t index);
      Button* GetButton(const char *name);

      Analog* GetAnalog(int64_t index);
      Analog* GetAnalog(const char *name);

      const Button* GetButton(int64_t index) const;
      const Button* GetButton(const char *name) const;

      const Analog* GetAnalog(int64_t index) const;
      const Analog* GetAnalog(const char *name) const;

      bool AddButtonName(int64_t index, const char *name);
      bool AddAnalogName(int64_t index, const char *name);

      bool RemoveButtonName(const char *name);
      bool RemoveAnalogName(const char *name);

      int64_t GetButtonNameCount(int64_t index) const;
      const char* GetButtonName(int64_t buttonIndex, int64_t nameIndex) const;

      int64_t GetAnalogNameCount(int64_t index) const;
      const char* GetAnalogName(int64_t buttonIndex, int64_t nameIndex) const;

      int64_t GetButtonIndex(const char *name) const;
      int64_t GetAnalogIndex(const char *name) const;
    };
  }
}

#endif // flInputDevice_h__
