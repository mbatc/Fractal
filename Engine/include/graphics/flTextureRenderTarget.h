#ifndef fl_Graphics_RenderTarget_h__
#define fl_Graphics_RenderTarget_h__

#include "flRenderTarget.h"

namespace flEngine
{
  namespace Graphics
  {
    class PixelBuffer;

    class flEXPORT TextureRenderTarget : public RenderTarget
    {
    public:
      PixelBuffer* GetPixels();
    };
  }
}

#endif // fl_Graphics_RenderTarget_h__
