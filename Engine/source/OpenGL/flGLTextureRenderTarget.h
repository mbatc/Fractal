#pragma once

#include "flTextureRenderTarget.h"
#include "flRef.h"

namespace Fractal
{
    class PixelBuffer;
    class Texture2D;

    class GLTextureRenderTarget : public TextureRenderTarget
    {
      GLTextureRenderTarget(API *pAPI);

    public:
      ~GLTextureRenderTarget();

      static TextureRenderTarget* Create(API *pAPI);

      virtual bool SetFormat(flIN const RenderTargetOptions* pOptions) override;
      virtual int64_t GetWidth() const override;
      virtual int64_t GetHeight() const override;
      virtual void Clear(flIN Colour colour = 0, flIN float depth = 1, flIN int32_t stencil = 0) override;
      virtual void ClearDepth(flIN float depth = 1.0f) override;
      virtual void ClearColour(flIN Colour colour = 0) override;
      virtual void ClearStencil(flIN int32_t colour = 0) override;
      virtual void Bind(bool read, bool draw) override;
      virtual void * GetNativeResource() const override;

      virtual Texture2D * GetColourTarget() override;
      virtual Texture2D * GetDepthTarget() override;

    private:
      uint32_t m_fbo = 0;

      int64_t m_width = 0;
      int64_t m_height = 0;

      Ref<Texture2D> m_depthTarget;
      Ref<Texture2D> m_colourTarget;
    };
}
