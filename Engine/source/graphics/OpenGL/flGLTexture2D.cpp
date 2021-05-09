#include "graphics/OpenGL/flGLTexture2D.h"
#include "flGLUtil.h"

namespace flEngine
{
  namespace Graphics
  {
    Texture2D *GLTexture2D::Create(PixelFormat pixelFormat, PixelComponentType type)
    {
      return flNew GLTexture2D(pixelFormat, type);
    }

    Texture2D *GLTexture2D::Create(DepthFormat depthFormat)
    {
      return flNew GLTexture2D(depthFormat);
    }

    TextureType GLTexture2D::GetTextureType() const
    {
      return TextureType_2D;
    }

    GLTexture2D::GLTexture2D()
    {
      glGenTextures(1, &m_texID);
      glBindTexture(GL_TEXTURE_2D, m_texID);

      // Setup default sampler parameters
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glBindTexture(GL_TEXTURE_2D, 0);
    }

    GLTexture2D::~GLTexture2D()
    {
      glDeleteTextures(1, &m_texID);
    }

    GLTexture2D::GLTexture2D(PixelFormat pixelFormat, PixelComponentType type)
      : GLTexture2D()
    {
      m_type = PixelBufferType_Colour;
      m_internalPixelFormat = pixelFormat;
      m_internalComponentType = type;
    }

    GLTexture2D::GLTexture2D(DepthFormat depthFormat)
      : GLTexture2D()
    {
      m_type = PixelBufferType_Depth;
      m_internalDepthFormat = depthFormat;
    }

    bool GLTexture2D::Set(void *pPixels, const PixelBufferDesc *pBufferDesc, int64_t mipMap)
    {
      uint32_t glInternalFmt, fmt, type;
      if (!GetGLFormat(pBufferDesc, &glInternalFmt, &fmt, &type))
        return false;

      glBindTexture(GL_TEXTURE_2D, m_texID);
      glTexImage2D(GL_TEXTURE_2D, (GLint)mipMap, glInternalFmt, (GLsizei)pBufferDesc->width, (GLsizei)pBufferDesc->height, 0, fmt, type, pPixels);
      glBindTexture(GL_TEXTURE_2D, 0);
      return true;
    }

    bool GLTexture2D::Set(void *pPixels, const PixelBufferDesc *pBufferDesc, int64_t widthOffset, int64_t heightOffset, int64_t depthOffset, int64_t mipMap)
    {
      ctUnused(depthOffset);

      uint32_t fmt, type;
      if (!GetGLFormat(pBufferDesc, nullptr, &fmt, &type))
        return false;

      glBindTexture(GL_TEXTURE_2D, m_texID);
      glTexSubImage2D(GL_TEXTURE_2D, (GLint)mipMap, (GLint)widthOffset, (GLint)heightOffset, (GLsizei)pBufferDesc->width, (GLsizei)pBufferDesc->height, fmt, type, pPixels);
      glBindTexture(GL_TEXTURE_2D, 0);
      return true;
    }

    bool GLTexture2D::Download(void **ppPixels, PixelBufferDesc *pBufferDesc, int64_t mipMap)
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

      glBindTexture(GL_TEXTURE_2D, m_texID);
      glGetTexImage(GL_TEXTURE_2D, (GLint)mipMap, fmt, type, *ppPixels);
      glBindTexture(GL_TEXTURE_2D, 0);
      return true;
    }

    bool GLTexture2D::GenerateMipMaps()
    {
      glGenerateTextureMipmap(m_texID);
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
      return m_resolution.x;
    }

    int64_t GLTexture2D::GetHeight(int64_t mipMap) const
    {
      return m_resolution.y;
    }

    int64_t GLTexture2D::GetDepth(int64_t mipMap) const
    {
      return 1;
    }

    PixelBufferType GLTexture2D::GetPixelBufferType() const
    {
      return m_desc.type;
    }

    const PixelBufferDesc *GLTexture2D::GetPixelBufferDesc() const
    {
      return &m_desc;
    }

    void *GLTexture2D::GetNativeResource()
    {
      return (void *)int64_t(m_texID);
    }

    bool GLTexture2D::GetGLFormat(const PixelBufferDesc *pBufferDesc, uint32_t *pInternal, uint32_t *pFmt, uint32_t *pType)
    {
      if (pBufferDesc->type != m_type)
      {
        // TODO: Add reporting of errors.
        //       Incompatible pixel buffer type.
        return false;
      }

      if (m_type == PixelBufferType_Colour)
      {
        if (pInternal) *pInternal = GLUtil::ToPixelFormatSized(m_internalPixelFormat, m_internalComponentType);
        if (pFmt)      *pFmt = GLUtil::ToPixelFormat(pBufferDesc->colourDesc.format);
        if (pType)     *pType = GLUtil::ToPixelDataType(pBufferDesc->colourDesc.type);
      }
      else if (m_type == PixelBufferType_Depth)
      {
        if (pInternal) *pInternal = GLUtil::ToPixelFormat(m_internalDepthFormat);
        if (pFmt)      *pFmt = GLUtil::ToPixelFormat(pBufferDesc->depthDesc.format);
        if (pType)     *pType = GLUtil::ToPixelDataType(pBufferDesc->depthDesc.format);
      }
      else
      {
        return false;
      }
      return true;
    }
  }
}
