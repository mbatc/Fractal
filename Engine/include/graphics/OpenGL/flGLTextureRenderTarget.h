#ifndef fl_Graphics_GLTextureRenderTarget_h__
#define fl_Graphics_GLTextureRenderTarget_h__

#include "../flTextureRenderTarget.h"

namespace flEngine
{
  namespace Graphics
  {
    class PixelBuffer;

    class flEXPORT GLTextureRenderTarget : public TextureRenderTarget
    {
    public:
      static GLTextureRenderTarget* Create();

    };
  }
}

#endif // fl_Graphics_RenderTarget_h__
