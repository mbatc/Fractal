#ifndef fl_Graphics_GLDeviceState_h__
#define fl_Graphics_GLDeviceState_h__

#include "../flDeviceState.h"

namespace flEngine
{
  namespace Graphics
  {
    class flPIMPL_CLASS(GLDeviceState);

    class flEXPORT GLDeviceState : public DeviceState
    {
      flPIMPL_DEF(GLDeviceState);

    public:
      static GLDeviceState* Create();
    };
  }
}

#endif // flGLDeviceState_h__
