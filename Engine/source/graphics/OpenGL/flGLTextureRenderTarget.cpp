#include "graphics/OpenGL/flGLTextureRenderTarget.h"
#include "flGLUtil.h"
#include "ctAssert.h"

namespace flEngine
{
  namespace Graphics
  {
    GLTextureRenderTarget::GLTextureRenderTarget()
    {
      glGenFramebuffers(1, &m_fbo);
    }

    GLTextureRenderTarget::~GLTextureRenderTarget()
    {
      glDeleteFramebuffers(1, &m_fbo);
    }

    TextureRenderTarget* GLTextureRenderTarget::Create()
    {
      ctFail("GLTextureRenderTarget is Not Implemented");
      return flNew GLTextureRenderTarget;
    }

    bool GLTextureRenderTarget::SetFormat(flIN RenderTargetOptions const* pOptions)
    {
      pOptions;
      return false;
    }

    int64_t GLTextureRenderTarget::GetWidth() const
    {
      return 0;
    }

    int64_t GLTextureRenderTarget::GetHeight() const
    {
      return 0;
    }

    void GLTextureRenderTarget::Clear(flIN Util::Colour colour, flIN float depth, flIN int32_t stencil)
    {
      ClearColour(colour);
      ClearDepth(depth);
      ClearStencil(stencil);
    }

    void GLTextureRenderTarget::ClearDepth(flIN float depth)
    {
      glClearNamedFramebufferfv(m_fbo, GL_DEPTH, 0, &depth);
      depth;
    }

    void GLTextureRenderTarget::ClearColour(flIN Util::Colour colour)
    {
      glClearNamedFramebufferfv(m_fbo, GL_COLOR, GL_DRAW_BUFFER0, &colour.r);
    }

    void GLTextureRenderTarget::ClearStencil(flIN int32_t colour)
    {
      glClearNamedFramebufferiv(m_fbo, GL_STENCIL, 0, &colour);
    }

    void GLTextureRenderTarget::Bind(bool read, bool draw)
    {
      if (read)
        glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo);
      if (draw)
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
    }

    void * GLTextureRenderTarget::GetNativeResource() const
    {
      return flNativeFromGLID(m_fbo);
    }
  }
}
