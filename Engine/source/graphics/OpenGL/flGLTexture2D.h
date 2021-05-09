#ifndef flGLTexture2D_h__
#define flGLTexture2D_h__

#include "graphics/flTexture2D.h"

namespace flEngine
{
  namespace Graphics
  {
    class GLTexture2D : public Texture2D
    {
      GLTexture2D();
      GLTexture2D(PixelFormat pixelFormat, PixelComponentType type);
      GLTexture2D(DepthFormat depthFormat);

    public:
      ~GLTexture2D();

      static Texture2D* Create(PixelFormat pixelFormat, PixelComponentType type);
      static Texture2D* Create(DepthFormat depthFormat);

      TextureType GetTextureType() const override;
      bool Set(void *pPixels, const PixelBufferDesc *pBufferDesc, int64_t mipMap = 0) override;
      bool Set(void *pPixels, const PixelBufferDesc *pBufferDesc, int64_t widthOffset = 0, int64_t heightOffset = 0, int64_t depthOffset = 0, int64_t mipMap = 0) override;
      bool Download(void **ppPixels, PixelBufferDesc *pBufferDesc, int64_t mipMap = 0) override;
      bool GenerateMipMaps() override;
      bool HasMipmaps() const override;
      int64_t GetMipMapCount() const override;
      int64_t GetWidth(int64_t mipMap = 0) const override;
      int64_t GetHeight(int64_t mipMap = 0) const override;
      int64_t GetDepth(int64_t mipMap = 0) const override;
      PixelBufferType GetPixelBufferType() const override;
      const PixelBufferDesc *GetPixelBufferDesc() const override;
      void* GetNativeResource() override;

    private:
      bool GetGLFormat(const PixelBufferDesc *pBufferDesc, uint32_t *pInternal, uint32_t *pFmt, uint32_t *pType);

      PixelBufferDesc m_desc;

      PixelBufferType    m_type;
      PixelFormat        m_internalPixelFormat;
      PixelComponentType m_internalComponentType;
      DepthFormat        m_internalDepthFormat;

      uint32_t m_texID = 0;
      bool m_hasMipMaps = false;
      Math::Vec2I m_resolution = { -1, -1 };
    };
  }
}

#endif // flGLTexture2D_h__
