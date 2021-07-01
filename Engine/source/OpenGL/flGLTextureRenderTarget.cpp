#include "flTexture2D.h"
#include "flAPI.h"

#include "flGLTextureRenderTarget.h"
#include "flGLUtil.h"
#include "ctAssert.h"

namespace Fractal
{
  GLTextureRenderTarget::GLTextureRenderTarget(API* pAPI)
    : TextureRenderTarget(pAPI)
  {
    flVerifyGL(glGenFramebuffers, 1, &m_fbo);
  }

  GLTextureRenderTarget::~GLTextureRenderTarget()
  {
    flVerifyGL(glDeleteFramebuffers, 1, &m_fbo);
  }

  TextureRenderTarget* GLTextureRenderTarget::Create(API* pAPI)
  {
    return flNew GLTextureRenderTarget(pAPI);
  }

  bool GLTextureRenderTarget::SetFormat(flIN RenderTargetOptions const* pOptions)
  {
    m_depthTarget = nullptr;
    m_colourTarget = nullptr;

    bool hasTarget = false;
    if (pOptions->colourFormat != PixelFormat_Unknown)
    {
      PixelBufferDesc desc;
      CreatePixelBufferDesc(&desc, pOptions->colourFormat, pOptions->pixelComponentType, pOptions->width, pOptions->height);
      m_colourTarget = MakeRef(GetAPI()->CreateTexture2D(pOptions->colourFormat, pOptions->pixelComponentType), false);
      m_colourTarget->Set(nullptr, &desc);
      hasTarget = true;
    }

    if (pOptions->depthFormat != DepthFormat_Unknown)
    {
      PixelBufferDesc desc;
      CreatePixelBufferDesc(&desc, pOptions->depthFormat, pOptions->width, pOptions->height);
      m_depthTarget = MakeRef(GetAPI()->CreateTexture2D(pOptions->depthFormat), false);
      m_depthTarget->Set(nullptr, &desc);
      hasTarget = true;
    }

    m_width  = pOptions->width;
    m_height = pOptions->height;

    flVerifyGL(glBindFramebuffer, GL_FRAMEBUFFER, m_fbo);

    if (m_colourTarget)
    {
      m_colourTarget->Bind();
      flVerifyGL(glFramebufferTexture2D,
                 GL_FRAMEBUFFER,
                 GL_COLOR_ATTACHMENT0,
                 GL_TEXTURE_2D,
                 flNativeToGLID(m_colourTarget->GetNativeResource()),
                 0);

      GLenum buffers = GL_COLOR_ATTACHMENT0;
      flVerifyGL(glDrawBuffers, 1, &buffers);
      flVerifyGL(glReadBuffer, GL_COLOR_ATTACHMENT0);
    }
    else
    {
      flVerifyGL(glDrawBuffer, GL_NONE);
      flVerifyGL(glReadBuffer, GL_NONE);
    }

    if (m_depthTarget)
    {
      m_depthTarget->Bind();
      flVerifyGL(glFramebufferTexture2D,
                 GL_FRAMEBUFFER,
                 GL_DEPTH_ATTACHMENT,
                 GL_TEXTURE_2D,
                 flNativeToGLID(m_depthTarget->GetNativeResource()),
                 0);
    }

    flVerifyGL(glBindFramebuffer, GL_FRAMEBUFFER, 0);

    return true;
  }

  int64_t GLTextureRenderTarget::GetWidth() const
  {
    return m_width;
  }

  int64_t GLTextureRenderTarget::GetHeight() const
  {
    return m_height;
  }

  void GLTextureRenderTarget::Clear(flIN Colour colour, flIN float depth, flIN int32_t stencil)
  {
    ClearColour(colour);
    ClearDepth(depth);
    ClearStencil(stencil);
  }

  void GLTextureRenderTarget::ClearDepth(flIN float depth)
  {
    flVerifyGL(glClearDepth, depth);
    flVerifyGL(glClear, GL_DEPTH_BUFFER_BIT);
  }

  void GLTextureRenderTarget::ClearColour(flIN Colour colour)
  {
    flVerifyGL(glClearColor, colour.r, colour.g, colour.b, colour.a);
    flVerifyGL(glClear, GL_COLOR_BUFFER_BIT);
  }

  void GLTextureRenderTarget::ClearStencil(flIN int32_t colour)
  {
    flVerifyGL(glClearStencil, colour);
    flVerifyGL(glClear, GL_STENCIL_BUFFER_BIT);
  }

  void GLTextureRenderTarget::Bind(bool read, bool draw)
  {
    if (read)
    {
      flVerifyGL(glBindFramebuffer, GL_READ_FRAMEBUFFER, m_fbo);
      flVerifyGL(glReadBuffer, GL_COLOR_ATTACHMENT0);
    }
    if (draw)
      flVerifyGL(glBindFramebuffer, GL_DRAW_FRAMEBUFFER, m_fbo);
  }

  void* GLTextureRenderTarget::GetNativeResource() const
  {
    return flNativeFromGLID(m_fbo);
  }

  Texture2D* GLTextureRenderTarget::GetColourTarget()
  {
    return m_colourTarget.Get();
  }

  Texture2D* GLTextureRenderTarget::GetDepthTarget()
  {
    return m_depthTarget.Get();
  }
}
