#ifndef fl_Graphics_GLTextureRenderTarget_h__
#define fl_Graphics_GLTextureRenderTarget_h__

#include "graphics/flTextureRenderTarget.h"

namespace flEngine
{
  namespace Graphics
  {
    class PixelBuffer;

    class GLTextureRenderTarget : public TextureRenderTarget
    {
      GLTextureRenderTarget();

    public:
      static TextureRenderTarget* Create();

      virtual bool SetFormat(flIN const RenderTargetOptions* pOptions) override;
      virtual void Clear(flIN Util::Colour colour = 0, flIN float depth = 1, flIN int32_t stencil = 0) override;
      virtual void ClearDepth(flIN float depth = 1.0f) override;
      virtual void ClearColour(flIN Util::Colour colour = 0) override;
      virtual void ClearStencil(flIN int32_t colour = 0) override;
      virtual void Bind() override;
    };
  }
}

#endif // fl_Graphics_RenderTarget_h__
