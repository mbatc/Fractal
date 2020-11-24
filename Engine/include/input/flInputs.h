#ifndef fl_Inputs_h__
#define fl_Inputs_h__

#include "flMouse.h"
#include "flKeyboard.h"

namespace flEngine
{
  class flPIMPL_CLASS(Inputs);

  class flEXPORT Inputs
  {
    flPIMPL_DEF(Inputs);

  public:
    // Get this input sets mouse interface
    virtual Input::Mouse* GetMouse();

    // Get this input sets keyboard interface
    virtual Input::Keyboard* GetKeyboard();

    // Update all the input devices
    static void Update();

    // Get the active mouse
    static Input::Mouse* GetActiveMouse();

    // Get the active keyboard
    static Input::Keyboard* GetActiveKeyboard();

    // Set the active mouse
    static void SetActiveMouse(Input::Mouse *pMouse);

    // Set the active keyboard
    static void SetActiveKeyboard(Input::Keyboard *pKeyboard);
  };
}


#endif // fl_Inputs_h__
