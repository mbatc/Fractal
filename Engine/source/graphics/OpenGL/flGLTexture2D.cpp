#include "graphics/OpenGL/flGLTexture2D.h"
#include "GL/glew.h"
#include "GL/wglew.h"
#include "GL/GL.h"

namespace flEngine
{
  namespace Graphics
  {
    class flPIMPL_CLASS(GLTexture2D)
    {
    public:
      void Construct()
      {
        glGenTextures(1, &m_texID);
      }

      bool Set(flIN void *pPixels, flIN PixelBufferDesc *pBufferDesc, flIN int64_t mipMap = 0)
      {
        glTexImage2D(p)
      }

      bool Set(flIN void *pPixels, flIN PixelBufferDesc *pBufferDesc, flIN Math::Vec3I offset = Math::Vec3I::zero(), flIN int64_t mipMap = 0)
      {

      }

      bool Download(flOUT void **ppPixels, flIN flOUT PixelBufferDesc *pBufferDesc, flIN int64_t mipMap = 0)
      {

      }

      bool GenerateMipMaps()
      {
        glGenerateMipmap(m_texID);
      }

      bool HasMipmaps() const
      {
        return m_hasMipMaps;
      }

      int64_t GetMimMapCount() const
      {

      }

      int64_t GetWidth(flIN int64_t mipMap = 0) const
      {
        return m_resolution.x;
      }

      int64_t GetHeight(flIN int64_t mipMap = 0) const
      {
        return m_resolution.y;
      }

      int64_t GetDepth(flIN int64_t mipMap = 0) const
      {
        return 1;
      }

      PixelBufferType GetPixelBufferType() const
      {

      }

      PixelBufferDesc* GetPixelBufferDesc() const
      {

      }

    protected:
      PixelBufferDesc m_desc;
      uint32_t m_texID = 0;
      bool m_hasMipMaps;
      Math::Vec2I m_resolution = { -1, -1 };
    };
  }
}

flPIMPL_IMPL(GLTexture2D)
#define flIMPL flPIMPL(GLTexture2D)

using namespace flEngine;
using namespace flEngine::Graphics;

Texture2D *GLTexture2D::Create()
{

}

bool GLTexture2D::Set(flIN void *pPixels, flIN PixelBufferDesc *pBufferDesc, flIN int64_t mipMap /*= 0*/)
{

}

bool GLTexture2D::Download(flOUT void **ppPixels, flIN flOUT PixelBufferDesc *pBufferDesc, flIN int64_t mipMap /*= 0*/)
{

}

bool GLTexture2D::GenerateMipMaps()
{

}

bool GLTexture2D::HasMipmaps() const
{

}

int64_t GLTexture2D::GetMimMapCount() const
{

}

int64_t GLTexture2D::GetWidth(flIN int64_t mipMap /*= 0*/) const
{

}

int64_t GLTexture2D::GetHeight(flIN int64_t mipMap /*= 0*/) const
{

}

int64_t GLTexture2D::GetDepth(flIN int64_t mipMap /*= 0*/) const
{

}

PixelBufferType GLTexture2D::GetPixelBufferType() const
{

}

PixelBufferDesc *GLTexture2D::GetPixelBufferDesc() const
{

}

bool GLTexture2D::Set(flIN void *pPixels, flIN PixelBufferDesc *pBufferDesc, flIN Math::Vec3I offset /*= Math::Vec3I::zero()*/, flIN int64_t mipMap /*= 0*/)
{

}
