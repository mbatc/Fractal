#include "graphics/OpenGL/flGLTextureRenderTarget.h"
#include "flGLUtil.h"

namespace flEngine
{
  namespace Graphics
  {
    class flPIMPL_CLASS(GLTextureRenderTarget)
    {
    public:
      flPIMPL_CLASS(GLTextureRenderTarget)()
      {
        glGenFramebuffers(1, &m_fbo);
      }

      ~flPIMPL_CLASS(GLTextureRenderTarget)()
      {
        glDeleteFramebuffers(1, &m_fbo);
      }

      void* GetNativeResource() { return flNativeFromGLID(m_fbo); }

    private:
      uint32_t m_fbo = 0;
    };

    GLTextureRenderTarget::GLTextureRenderTarget()
    {

    }

    TextureRenderTarget* GLTextureRenderTarget::Create()
    {
      return flNew GLTextureRenderTarget;
    }

    bool GLTextureRenderTarget::SetFormat(flIN RenderTargetOptions const* pOptions)
    {
      pOptions;
      return false;
    }

    void GLTextureRenderTarget::Clear(flIN Util::Colour colour, flIN float depth, flIN int32_t stencil)
    {
      colour, depth, stencil;
    }

    void GLTextureRenderTarget::ClearDepth(flIN float depth)
    {
      depth;
    }

    void GLTextureRenderTarget::ClearColour(flIN Util::Colour colour)
    {
      colour;
    }

    void GLTextureRenderTarget::ClearStencil(flIN int32_t colour)
    {
      colour;
    }

    void GLTextureRenderTarget::Bind()
    {

    }
  }
}
