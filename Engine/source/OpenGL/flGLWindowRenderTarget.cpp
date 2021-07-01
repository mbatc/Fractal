#include "flGLWindowRenderTarget.h"
#include "flGLUtil.h"

namespace Fractal
{
  WindowRenderTarget* GLWindowRenderTarget::Create(API* pAPI, flIN Window* pWindow, flIN const RenderTargetOptions* pOptions)
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

  void GLWindowRenderTarget::Clear(flIN Colour colour, flIN float depth, flIN int32_t stencil)
  {
    ClearColour(colour);
    ClearDepth(depth);
    ClearStencil(stencil);
  }

  void GLWindowRenderTarget::ClearDepth(flIN float depth)
  {
    MakeCurrent();
    flVerifyGL(glClearDepth, depth);
    flVerifyGL(glClear, GL_DEPTH_BUFFER_BIT);
  }

  void GLWindowRenderTarget::ClearColour(flIN Colour colour)
  {
    MakeCurrent();
    flVerifyGL(glClearColor, colour.r, colour.g, colour.b, colour.a);
    flVerifyGL(glClear, GL_COLOR_BUFFER_BIT);
  }

  void GLWindowRenderTarget::ClearStencil(flIN int32_t stencil)
  {
    MakeCurrent();
    flVerifyGL(glClearStencil, stencil);
    flVerifyGL(glClear, GL_STENCIL_BUFFER_BIT);
  }

  void GLWindowRenderTarget::Bind(bool read, bool draw)
  {
    MakeCurrent();
    if (read)
      flVerifyGL(glBindFramebuffer, GL_READ_FRAMEBUFFER, 0);

    if (draw)
      flVerifyGL(glBindFramebuffer, GL_DRAW_FRAMEBUFFER, 0);
  }
}
