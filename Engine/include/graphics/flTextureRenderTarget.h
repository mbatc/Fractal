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
      /**
       * @brief Get a pointer to the colour target texture.
       */
      virtual Texture2D * GetColourTarget() = 0;

      /**
       * @brief Get a pointer to the depth target texture.
       */
      virtual Texture2D * GetDepthTarget() = 0;
    };
  }
}

#endif // fl_Graphics_RenderTarget_h__
