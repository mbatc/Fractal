#include "flGLSampler.h"
#include "flGLUtil.h"

namespace Fractal
{
  GLSampler::GLSampler(API* pAPI)
    : Sampler(pAPI)
  {
    flVerifyGL(glCreateSamplers, 1, &m_samplerID);
  }

  GLSampler::~GLSampler()
  {
    flVerifyGL(glDeleteSamplers, 1, &m_samplerID);
  }

  Sampler* GLSampler::Create(API* pAPI)
  {
    return flNew GLSampler(pAPI);
  }

  void GLSampler::Bind(flIN int64_t textureUnit)
  {
    flVerifyGL(glBindSampler, (GLuint)textureUnit, m_samplerID);
  }

  void GLSampler::SetWrapMode(WrapMode wrap)
  {
    SetWrapModeX(wrap);
    SetWrapModeY(wrap);
  }

  void GLSampler::GetWrapMode(WrapMode* pWrapX, WrapMode* pWrapY) const
  {
    int32_t xMode = 0;
    int32_t yMode = 0;

    flVerifyGL(glGetSamplerParameteriv, m_samplerID, GL_TEXTURE_WRAP_S, &xMode);
    flVerifyGL(glGetSamplerParameteriv, m_samplerID, GL_TEXTURE_WRAP_T, &yMode);

    if (pWrapX)
      *pWrapX = GLUtil::GetWrapMode(xMode);
    if (pWrapY)
      *pWrapY = GLUtil::GetWrapMode(yMode);
  }

  void GLSampler::SetWrapModeX(WrapMode wrap)
  {
    flVerifyGL(glSamplerParameteri, m_samplerID, GL_TEXTURE_WRAP_S, GLUtil::ToWrapMode(wrap));
  }

  void GLSampler::SetWrapModeY(WrapMode wrap)
  {
    flVerifyGL(glSamplerParameteri, m_samplerID, GL_TEXTURE_WRAP_T, GLUtil::ToWrapMode(wrap));
  }

  void GLSampler::SetFilterMinMode(FilterMode mode, bool mipmaps)
  {
    flVerifyGL(glSamplerParameteri, m_samplerID, GL_TEXTURE_MIN_FILTER, GLUtil::ToFilterMode(mode, mipmaps));
  }

  void GLSampler::SetFilterMagMode(FilterMode mode)
  {
    flVerifyGL(glSamplerParameteri, m_samplerID, GL_TEXTURE_MAG_FILTER, GLUtil::ToFilterMode(mode));
  }

  FilterMode GLSampler::GetFilterMinMode(bool* pUseMipmaps) const
  {
    int32_t mode = 0;
    flVerifyGL(glGetSamplerParameteriv, m_samplerID, GL_TEXTURE_MAG_FILTER, &mode);
    return GLUtil::GetFilterMode(mode, pUseMipmaps);
  }

  FilterMode GLSampler::GetFilterMagMode() const
  {
    int32_t mode = 0;
    flVerifyGL(glGetSamplerParameteriv, m_samplerID, GL_TEXTURE_MAG_FILTER, &mode);
    return GLUtil::GetFilterMode(mode);
  }

  void GLSampler::SetBorderColour(Colour* pColour)
  {
    flVerifyGL(glSamplerParameterfv, m_samplerID, GL_TEXTURE_BORDER_COLOR, &pColour->r);
  }

  void GLSampler::GetBorderColour(Colour* pColour) const
  {
    flVerifyGL(glGetSamplerParameterfv, m_samplerID, GL_TEXTURE_BORDER_COLOR, &pColour->r);
  }

  void* GLSampler::GetNativeResource()
  {
    return flNativeFromGLID(m_samplerID);
  }
}
