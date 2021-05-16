#ifndef fl_Graphics_GLSampler_h__
#define fl_Graphics_GLSampler_h__

#include "graphics/flSampler.h"

namespace flEngine
{
  namespace Graphics
  {
    class API;

    class GLSampler : public Sampler
    {
      GLSampler(API *pAPI);

    public:
      ~GLSampler();

      static Sampler *Create(API *pAPI);

      void Bind(flIN int64_t textureUnit) override;

      void SetWrapMode(WrapMode wrap) override;
      void GetWrapMode(WrapMode *pWrapX, WrapMode *pWrapY) const override;

      void SetWrapModeX(WrapMode wrap) override;
      void SetWrapModeY(WrapMode wrap) override;

      void SetFilterMinMode(FilterMode mode, bool useMipmaps) override;
      void SetFilterMagMode(FilterMode mode) override;

      FilterMode GetFilterMinMode(bool *pUseMipmaps = nullptr) const override;
      FilterMode GetFilterMagMode() const override;

      void SetBorderColour(Util::Colour *pColour) override;
      void GetBorderColour(Util::Colour *pColour) const override;

      void *GetNativeResource() override;

    private:
      uint32_t m_samplerID = 0;
    };
  }
}

#endif // flGLSampler_h__
