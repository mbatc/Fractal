#ifndef fl_Graphics_GLPixelBuffer_h__
#define fl_Graphics_GLPixelBuffer_h__

#include "../flPixelBuffer.h"

namespace flEngine
{
  namespace Graphics
  {
    class flEXPORT GLPixelBuffer : public PixelBuffer
    {
    public:
      static GLPixelBuffer* Create();
    };
  }
}

#endif // fl_Graphics_PixelBuffer_h__