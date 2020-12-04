#ifndef fl_Inputs_h__
#define fl_Inputs_h__

#include "flMouse.h"
#include "flKeyboard.h"

namespace flEngine
{
  class flEXPORT Inputs
  {
  public:
    // Update all the input devices
    static void Update();
  };
}


#endif // fl_Inputs_h__
