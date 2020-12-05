#ifndef fl_Graphics_RenderTarget_h__
#define fl_Graphics_RenderTarget_h__

#include "../flInterface.h"

namespace flEngine
{
  namespace Graphics
  {
    class PixelBuffer;

    class RenderTarget : public Interface
    {
    public:
      PixelBuffer* GetPixels();
    };
  }
}

#endif // fl_Graphics_RenderTarget_h__
