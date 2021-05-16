#include "graphics\OpenGL\flGLWindowRenderTarget.h"
#include "flGLUtil.h"

namespace flEngine
{
  namespace Graphics
  {
    WindowRenderTarget *GLWindowRenderTarget::Create(API *pAPI, flIN Platform::Window *pWindow, flIN const RenderTargetOptions *pOptions)
    {
      return flNew GLWindowRenderTarget(pAPI, pWindow, pOptions);
    }

    int64_t GLWindowRenderTarget::GetWidth() const
    {
      return GetWindow()->GetWidth();
    }

    int64_t GLWindowRenderTarget::GetHeight() const
    {
      return GetWindow()->GetHeight();
    }

    void GLWindowRenderTarget::Clear(flIN Util::Colour colour, flIN float depth, flIN int32_t stencil)
    {
      ClearColour(colour);
      ClearDepth(depth);
      ClearStencil(stencil);
    }

    void GLWindowRenderTarget::ClearDepth(flIN float depth)
    {
      MakeCurrent();
      glClearDepth(depth);
      glClear(GL_DEPTH_BUFFER_BIT);
    }

    void GLWindowRenderTarget::ClearColour(flIN Util::Colour colour)
    {
      MakeCurrent();
      glClearColor(colour.r, colour.g, colour.b, colour.a);
      glClear(GL_COLOR_BUFFER_BIT);
    }

    void GLWindowRenderTarget::ClearStencil(flIN int32_t stencil)
    {
      MakeCurrent();
      glClearStencil(stencil);
      glClear(GL_STENCIL_BUFFER_BIT);
    }

    void GLWindowRenderTarget::Bind(bool read, bool draw)
    {
      MakeCurrent();
      if (read) glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
      if (draw) glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    }
  }
}
