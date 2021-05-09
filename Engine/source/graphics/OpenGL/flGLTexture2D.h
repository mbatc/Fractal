#ifndef flGLTexture2D_h__
#define flGLTexture2D_h__

#include "graphics/flTexture2D.h"

namespace flEngine
{
  namespace Graphics
  {
    class flPIMPL_CLASS(GLTexture2D);

    class GLTexture2D : public Texture2D
    {
      flPIMPL_DEF(GLTexture2D);

      GLTexture2D(flIN PixelFormat pixelFormat, flIN PixelComponentType type);
      GLTexture2D(flIN DepthFormat depthFormat);

    public:
      static Texture2D* Create(flIN PixelFormat pixelFormat, flIN PixelComponentType type);
      static Texture2D* Create(flIN DepthFormat depthFormat);

      virtual TextureType GetTextureType() const override;
      virtual bool Set(flIN void *pPixels, flIN const PixelBufferDesc *pBufferDesc, flIN int64_t mipMap = 0) override;
      virtual bool Set(flIN void *pPixels, flIN const PixelBufferDesc *pBufferDesc, flIN int64_t widthOffset = 0, flIN int64_t heightOffset = 0, flIN int64_t depthOffset = 0, flIN int64_t mipMap = 0) override;
      virtual bool Download(flOUT void **ppPixels, flIN flOUT PixelBufferDesc *pBufferDesc, flIN int64_t mipMap = 0) override;
      virtual bool GenerateMipMaps() override;
      virtual bool HasMipmaps() const override;
      virtual int64_t GetMipMapCount() const override;
      virtual int64_t GetWidth(flIN int64_t mipMap = 0) const override;
      virtual int64_t GetHeight(flIN int64_t mipMap = 0) const override;
      virtual int64_t GetDepth(flIN int64_t mipMap = 0) const override;
      virtual PixelBufferType GetPixelBufferType() const override;
      virtual const PixelBufferDesc *GetPixelBufferDesc() const override;
      virtual void* GetNativeResource() override;
    };
  }
}

#endif // flGLTexture2D_h__
