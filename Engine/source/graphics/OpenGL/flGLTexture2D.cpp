#include "graphics/OpenGL/flGLTexture2D.h"
#include "flGLUtil.h"

namespace flEngine
{
  namespace Graphics
  {
    class flPIMPL_CLASS(GLTexture2D)
    {
    public:
      Impl_GLTexture2D()
      {
        glGenTextures(1, &m_texID);
        glBindTexture(GL_TEXTURE_2D, m_texID);
        glBindTexture(GL_TEXTURE_2D, 0);
      }

      ~Impl_GLTexture2D()
      {
        glDeleteTextures(1, &m_texID);
      }

      void Construct(PixelFormat pixelFormat, PixelComponentType type)
      {
        m_type = PixelBufferType_Colour;
        m_internalPixelFormat = pixelFormat;
        m_internalComponentType = type;
      }

      void Construct(DepthFormat depthFormat)
      {
        m_type = PixelBufferType_Depth;
        m_internalDepthFormat = depthFormat;
      }

      bool Set(void *pPixels, const PixelBufferDesc *pBufferDesc, int64_t mipMap = 0)
      {
        uint32_t glInternalFmt, fmt, type;
        if (!GetGLFormat(pBufferDesc, &glInternalFmt, &fmt, &type))
          return false;

        glBindTexture(GL_TEXTURE_2D, m_texID);
        glTexImage2D(GL_TEXTURE_2D, (GLint)mipMap, glInternalFmt, (GLsizei)pBufferDesc->width, (GLsizei)pBufferDesc->height, 0, fmt, type, pPixels);
        glBindTexture(GL_TEXTURE_2D, 0);
        return true;
      }

      bool Set(void *pPixels, const PixelBufferDesc *pBufferDesc, Math::Vec3I offset = Math::Vec3I::zero(), int64_t mipMap = 0)
      {
        uint32_t fmt, type;
        if (!GetGLFormat(pBufferDesc, nullptr, &fmt, &type))
          return false;

        glBindTexture(GL_TEXTURE_2D, m_texID);
        glTexSubImage2D(GL_TEXTURE_2D, (GLint)mipMap, offset.x, offset.y, (GLsizei)pBufferDesc->width, (GLsizei)pBufferDesc->height, fmt, type, pPixels);
        glBindTexture(GL_TEXTURE_2D, 0);
        return true;
      }

      bool Download(void **ppPixels, PixelBufferDesc *pBufferDesc, int64_t mipMap = 0)
      {
        if (pBufferDesc->type == PixelBufferType_Unknown)
        {
          pBufferDesc->type = m_type;
          if (pBufferDesc->type == PixelBufferType_Colour)
          {
            pBufferDesc->colourDesc.format = m_internalPixelFormat;
            pBufferDesc->colourDesc.type   = m_internalComponentType;
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

      bool GenerateMipMaps()
      {
        glGenerateMipmap(m_texID);
        return true;
      }

      bool HasMipmaps() const
      {
        return m_hasMipMaps;
      }

      int64_t GetMimMapCount() const
      {
        return 1;
      }

      int64_t GetWidth(int64_t mipMap = 0) const
      {
        return m_resolution.x;
      }

      int64_t GetHeight(int64_t mipMap = 0) const
      {
        return m_resolution.y;
      }

      int64_t GetDepth(int64_t mipMap = 0) const
      {
        return 1;
      }

      PixelBufferType GetPixelBufferType() const
      {
        return m_desc.type;
      }

      const PixelBufferDesc* GetPixelBufferDesc() const
      {
        return &m_desc;
      }

      void* GetNativeResource()
      {
        return (void*)int64_t(m_texID);
      }

    protected:
      bool GetGLFormat(const PixelBufferDesc *pBufferDesc, uint32_t *pInternal, uint32_t *pFmt, uint32_t *pType)
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
          if (pFmt)      *pFmt      = GLUtil::ToPixelFormat(pBufferDesc->colourDesc.format);
          if (pType)     *pType     = GLUtil::ToPixelDataType(pBufferDesc->colourDesc.type);
        }
        else if (m_type == PixelBufferType_Depth)
        {
          if (pInternal) *pInternal = GLUtil::ToPixelFormat(m_internalDepthFormat);
          if (pFmt)      *pFmt      = GLUtil::ToPixelFormat(pBufferDesc->depthDesc.format);
          if (pType)     *pType     = GLUtil::ToPixelDataType(pBufferDesc->depthDesc.format);
        }
        else
        {
          return false;
        }

        return true;
      }

      PixelBufferDesc m_desc;

      PixelBufferType    m_type;
      PixelFormat        m_internalPixelFormat;
      PixelComponentType m_internalComponentType;
      DepthFormat        m_internalDepthFormat;

      uint32_t m_texID = 0;
      bool m_hasMipMaps;
      Math::Vec2I m_resolution = { -1, -1 };
    };
  }
}

using namespace flEngine;
using namespace flEngine::Graphics;

flPIMPL_IMPL(GLTexture2D)

GLTexture2D::GLTexture2D(flIN PixelFormat pixelFormat, flIN PixelComponentType type)
{
  Impl()->Construct(pixelFormat, type);
}

GLTexture2D::GLTexture2D(flIN DepthFormat depthFormat)
{
  Impl()->Construct(depthFormat);
}

Texture2D* GLTexture2D::Create(flIN PixelFormat pixelFormat, flIN PixelComponentType type)
{
  return flNew GLTexture2D(pixelFormat, type);
}

Texture2D* GLTexture2D::Create(flIN DepthFormat depthFormat)
{
  return flNew GLTexture2D(depthFormat);
}

TextureType GLTexture2D::GetTextureType() const
{
  return TextureType_2D;
}

bool GLTexture2D::Set(flIN void *pPixels, flIN const PixelBufferDesc *pBufferDesc, flIN int64_t mipMap /*= 0*/)
{
  return Impl()->Set(pPixels, pBufferDesc, mipMap);
}

bool GLTexture2D::Download(flOUT void **ppPixels, flIN flOUT PixelBufferDesc *pBufferDesc, flIN int64_t mipMap /*= 0*/)
{
  return Impl()->Download(ppPixels, pBufferDesc, mipMap);
}

bool GLTexture2D::GenerateMipMaps()
{
  return Impl()->GenerateMipMaps();
}

bool GLTexture2D::HasMipmaps() const
{
  return Impl()->HasMipmaps();
}

int64_t GLTexture2D::GetMipMapCount() const
{
  return Impl()->GetMimMapCount();
}

int64_t GLTexture2D::GetWidth(flIN int64_t mipMap /*= 0*/) const
{
  return Impl()->GetWidth(mipMap);
}

int64_t GLTexture2D::GetHeight(flIN int64_t mipMap /*= 0*/) const
{
  return Impl()->GetHeight(mipMap);
}

int64_t GLTexture2D::GetDepth(flIN int64_t mipMap /*= 0*/) const
{
  return Impl()->GetDepth(mipMap);
}

PixelBufferType GLTexture2D::GetPixelBufferType() const
{
  return Impl()->GetPixelBufferType();
}

const PixelBufferDesc *GLTexture2D::GetPixelBufferDesc() const
{
  return Impl()->GetPixelBufferDesc();
}

void* GLTexture2D::GetNativeResource()
{
  return Impl()->GetNativeResource();
}

bool GLTexture2D::Set(flIN void *pPixels, flIN const PixelBufferDesc *pBufferDesc, flIN int64_t widthOffset, flIN int64_t heightOffset, flIN int64_t depthOffset, flIN int64_t mipMap /*= 0*/)
{
  return Impl()->Set(pPixels, pBufferDesc, { widthOffset, heightOffset, depthOffset }, mipMap);
}
