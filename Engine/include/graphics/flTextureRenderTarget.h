#ifndef fl_Graphics_TextureRenderTarget_h__
#define fl_Graphics_TextureRenderTarget_h__

#include "flRenderTarget.h"

namespace flEngine
{
  namespace Graphics
  {
    class Texture2D;
    class PixelBuffer;

    class flEXPORT TextureRenderTarget : public RenderTarget
    {
    protected:
      TextureRenderTarget(API *pAPI);

    public:
      virtual Texture2D * GetColourTarget() = 0;

      virtual Texture2D * GetDepthTarget() = 0;
    };
  }
}

#endif // fl_Graphics_RenderTarget_h__
