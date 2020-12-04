#ifndef fl_Input_InputDeviceServer_h__
#define fl_Input_InputDeviceServer_h__

#include "../flConfig.h"
#include "../flPImpl.h"
#include "../flInterface.h"

namespace flEngine
{
  namespace Input
  {
    class flPIMPL_CLASS(InputDeviceServer);

    class flEXPORT InputDeviceServer : public Interface
    {
      flPIMPL_DEF(InputDeviceServer);
    protected:
      InputDeviceServer();

    public:
      /**
       * @brief Create a device input server/
       */
      static InputDeviceServer* Create();

      void Lock();
      void Unlock();

      /**
       * @brief Get the next event from the server for a button input.
       *
       * @param [out] pButtonID  A pointer to a int64 to copy the button input ID into.
       * @param [out] pValue     A pointer to a bool to copy the pressed state of the button into.
       * @param [out] pTimestamp A pointer to a int64 to copy the timestamp of the event into.
       *
       * @return True if there is an event in the queue.
       */
      bool GetEvent(flOUT int64_t *pButtonID, flOUT bool *pValue, flOUT int64_t *pTimestamp);

      /**
       * @brief Get the next event from the server for an analog input.
       *
       * @param [out] pAnalogID  A pointer to a int64 to copy the analog input ID into.
       * @param [out] pValue     A pointer to a float to copy the value of the input into.
       * @param [out] pAddValue  A pointer to a bool to copy the add value indicator into.
       * @param [out] pTimestamp A pointer to a int64 to copy the timestamp of the event into.
       *
       * @return True if there is an event in the queue.
       */
      bool GetEvent(flOUT int64_t *pAnalogID, flOUT float *pValue, flOUT bool *pAddValue, flOUT int64_t *pTimestamp);

      /**
       * Send a button update event
       *
       * @param [in] buttonID  The ID of the button input.
       * @param [in] pressed   The 'pressed' state of the button.
       * @param [in] timestamp The timestamp to associate with the event. This should be in milliseconds since epoch. If -1, then clock() is used.
       */
      void SendEvent(flIN int64_t buttonID, flIN bool pressed, flIN int64_t timestamp = -1);

      /**
       * Send an analog update event
       *
       * @param [in] analogID  The ID of the analog input.
       * @param [in] value     The value of the analog input for this event.
       * @param [in] addValue  Set to true, to add 'value' to the existing input value.
       * @param [in] timestamp The timestamp to associate with the event. This should be in milliseconds since epoch. If -1, then clock() is used.
       */
      void SendEvent(flIN int64_t analogID, flIN float value, flIN bool addValue = false, flIN int64_t timestamp = -1);
    };
  }
}

#endif // flInputDeviceServer_h__
