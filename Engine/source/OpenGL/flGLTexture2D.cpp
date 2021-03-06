#include "flGLTexture2D.h"
#include "flGLUtil.h"
#include "flApplication.h"
#include "flTask.h"

namespace Fractal
{
  Texture2D* GLTexture2D::Create(API* pAPI, PixelFormat pixelFormat, PixelComponentType type)
  {
    return flNew GLTexture2D(pAPI, pixelFormat, type);
  }

  Texture2D* GLTexture2D::Create(API* pAPI, DepthFormat depthFormat)
  {
    return flNew GLTexture2D(pAPI, depthFormat);
  }

  GLTexture2D::GLTexture2D(API* pAPI)
    : Texture2D(pAPI)
  {
    flVerifyGL(glGenTextures, 1, &m_texID);
    flVerifyGL(glBindTexture, GL_TEXTURE_2D, m_texID);

    // Setup default sampler parameters
    flVerifyGL(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    flVerifyGL(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    flVerifyGL(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    flVerifyGL(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    flVerifyGL(glBindTexture, GL_TEXTURE_2D, 0);
  }

  GLTexture2D::GLTexture2D(API* pAPI, PixelFormat pixelFormat, PixelComponentType type)
    : GLTexture2D(pAPI)
  {
    CreatePixelBufferDesc(&m_desc, pixelFormat, type, 0, 0);
    m_type = PixelBufferType_Colour;
    m_internalPixelFormat = pixelFormat;
    m_internalComponentType = type;
  }

  GLTexture2D::GLTexture2D(API* pAPI, DepthFormat depthFormat)
    : GLTexture2D(pAPI)
  {
    CreatePixelBufferDesc(&m_desc, depthFormat, 0, 0);
    m_type = PixelBufferType_Depth;
    m_internalDepthFormat = depthFormat;
  }

  GLTexture2D::~GLTexture2D()
  {
    Application::EnqueueTask(MakeTask([texID = m_texID]()
    {
      flVerifyGL(glDeleteTextures, 1, &texID);
      return 0;
    }
                                     ));
  }

  void GLTexture2D::Bind()
  {
    flVerifyGL(glBindTexture, GL_TEXTURE_2D, m_texID);
  }

  void GLTexture2D::Unbind()
  {
    flVerifyGL(glBindTexture, GL_TEXTURE_2D, 0);
  }

  TextureType GLTexture2D::GetTextureType() const
  {
    return TextureType_2D;
  }

  bool GLTexture2D::Set(void* pPixels, const PixelBufferDesc* pBufferDesc, int64_t mipMap)
  {
    uint32_t glInternalFmt, fmt, type;
    if (!GetGLFormat(pBufferDesc, &glInternalFmt, &fmt, &type))
      return false;

    flVerifyGL(glBindTexture, GL_TEXTURE_2D, m_texID);
    flVerifyGL(glTexImage2D, GL_TEXTURE_2D, (GLint)mipMap, glInternalFmt, (GLsizei)pBufferDesc->width, (GLsizei)pBufferDesc->height, 0, fmt, type, pPixels);
    flVerifyGL(glBindTexture, GL_TEXTURE_2D, 0);

    m_desc = *pBufferDesc;

    return true;
  }

  bool GLTexture2D::Set(void* pPixels, const PixelBufferDesc* pBufferDesc, int64_t widthOffset, int64_t heightOffset, int64_t depthOffset, int64_t mipMap)
  {
    ctUnused(depthOffset);

    uint32_t fmt, type;
    if (!GetGLFormat(pBufferDesc, nullptr, &fmt, &type))
      return false;

    flVerifyGL(glBindTexture, GL_TEXTURE_2D, m_texID);
    flVerifyGL(glTexSubImage2D, GL_TEXTURE_2D, (GLint)mipMap, (GLint)widthOffset, (GLint)heightOffset, (GLsizei)pBufferDesc->width, (GLsizei)pBufferDesc->height, fmt, type, pPixels);
    flVerifyGL(glBindTexture, GL_TEXTURE_2D, 0);

    m_desc = *pBufferDesc;

    return true;
  }

  bool GLTexture2D::Download(void** ppPixels, PixelBufferDesc* pBufferDesc, int64_t mipMap)
  {
    if (pBufferDesc->type == PixelBufferType_Unknown)
    {
      pBufferDesc->type = m_type;
      if (pBufferDesc->type == PixelBufferType_Colour)
      {
        pBufferDesc->colourDesc.format = m_internalPixelFormat;
        pBufferDesc->colourDesc.type = m_internalComponentType;
      }
      else
      {
        pBufferDesc->depthDesc.format;
      }
    }

    uint32_t fmt, type;
    if (!GetGLFormat(pBufferDesc, nullptr, &fmt, &type))
      return false;

    pBufferDesc->width = GetWidth(mipMap);
    pBufferDesc->height = GetHeight(mipMap);
    int64_t pixelStride = GetPixelStride(pBufferDesc);
    *ppPixels = flAlloc(pixelStride * pBufferDesc->width * pBufferDesc->height);

    flVerifyGL(glBindTexture, GL_TEXTURE_2D, m_texID);
    flVerifyGL(glGetTexImage, GL_TEXTURE_2D, (GLint)mipMap, fmt, type, *ppPixels);
    flVerifyGL(glBindTexture, GL_TEXTURE_2D, 0);
    return true;
  }

  bool GLTexture2D::GenerateMipMaps()
  {
    flVerifyGL(glGenerateTextureMipmap, m_texID);
    m_hasMipMaps = true;
    return true;
  }

  bool GLTexture2D::HasMipmaps() const
  {
    return m_hasMipMaps;
  }

  int64_t GLTexture2D::GetMipMapCount() const
  {
    return m_hasMipMaps ? int64_t(1 + floor(log2((double)ctMax(GetWidth(), GetHeight(), GetDepth())))) : 1;
  }

  int64_t GLTexture2D::GetWidth(int64_t mipMap) const
  {
    return m_desc.width;
  }

  int64_t GLTexture2D::GetHeight(int64_t mipMap) const
  {
    return m_desc.height;
  }

  int64_t GLTexture2D::GetDepth(int64_t mipMap) const
  {
    return 1;
  }

  PixelBufferType GLTexture2D::GetPixelBufferType() const
  {
    return m_desc.type;
  }

  const PixelBufferDesc* GLTexture2D::GetPixelBufferDesc() const
  {
    return &m_desc;
  }

  void* GLTexture2D::GetNativeResource()
  {
    return (void*)int64_t(m_texID);
  }

  bool GLTexture2D::GetGLFormat(const PixelBufferDesc* pBufferDesc, uint32_t* pInternal, uint32_t* pFmt, uint32_t* pType)
  {
    if (pBufferDesc->type != m_type)
    {
      // TODO: Add reporting of errors.
      //       Incompatible pixel buffer type.
      return false;
    }

    if (m_type == PixelBufferType_Colour)
    {
      if (pInternal)
        *pInternal = GLUtil::ToPixelFormatSized(m_internalPixelFormat, m_internalComponentType);
      if (pFmt)
        *pFmt = GLUtil::ToPixelFormat(pBufferDesc->colourDesc.format);
      if (pType)
        *pType = GLUtil::ToPixelDataType(pBufferDesc->colourDesc.type);
    }
    else if (m_type == PixelBufferType_Depth)
    {
      if (pInternal)
        *pInternal = GLUtil::ToPixelFormat(m_internalDepthFormat);
      if (pFmt)
        *pFmt = GLUtil::ToPixelFormat(pBufferDesc->depthDesc.format);
      if (pType)
        *pType = GLUtil::ToPixelDataType(pBufferDesc->depthDesc.format);
    }
    else
    {
      return false;
    }
    return true;
  }
}
