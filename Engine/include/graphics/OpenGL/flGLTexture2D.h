#ifndef flGLTexture2D_h__
#define flGLTexture2D_h__

#include "../flTexture2D.h"

namespace flEngine
{
  namespace Graphics
  {
    class flPIMPL_CLASS(GLTexture2D);

    class GLTexture2D : public Texture2D
    {
      flPIMPL_DEF(GLTexture2D);

    public:
      static Texture2D *Create();

      virtual bool Set(flIN void *pPixels, flIN PixelBufferDesc *pBufferDesc, flIN int64_t mipMap = 0) override;
      virtual bool Set(flIN void *pPixels, flIN PixelBufferDesc *pBufferDesc, flIN Math::Vec3I offset = Math::Vec3I::zero(), flIN int64_t mipMap = 0) override;
      virtual bool Download(flOUT void **ppPixels, flIN flOUT PixelBufferDesc *pBufferDesc, flIN int64_t mipMap = 0) override;
      virtual bool GenerateMipMaps() override;
      virtual bool HasMipmaps() const override;
      virtual int64_t GetMimMapCount() const override;
      virtual int64_t GetWidth(flIN int64_t mipMap = 0) const override;
      virtual int64_t GetHeight(flIN int64_t mipMap = 0) const override;
      virtual int64_t GetDepth(flIN int64_t mipMap = 0) const override;
      virtual PixelBufferType GetPixelBufferType() const override;
      virtual PixelBufferDesc *GetPixelBufferDesc() const override;
    };
  }
}

#endif // flGLTexture2D_h__
