#ifndef fl_Inputs_h__
#define fl_Inputs_h__

#include "flMouse.h"
#include "flKeyboard.h"

namespace flEngine
{
  class flEXPORT Inputs
  {
  public:
    Input::Mouse* GetMouse();

    Input::Keyboard* GetKeyboard();

    static Inputs* GlobalInput();
  };
}


#endif // fl_Inputs_h__
