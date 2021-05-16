#ifndef flTexture_h__
#define flTexture_h__

#include "../flInterface.h"
#include "../util/flColour.h"
#include "flAPIResource.h"

namespace flEngine
{
  namespace Graphics
  {
    enum WrapMode
    {
      WrapMode_Unknown = -1,
      WrapMode_Repeat,
      WrapMode_Mirror,
      WrapMode_ClampToEdge,
      WrapMode_Count,
    };

    enum FilterMode
    {
      FilterMode_Unknown = -1,
      FilterMode_Linear,
      FilterMode_Nearest,
      FilterMode_Count,
    };

    class flEXPORT Sampler : public APIResource
    {
    protected:
      Sampler(API *pAPI);

    public:
      virtual void Bind(flIN int64_t textureUnit) = 0;

      virtual void SetWrapMode(flIN WrapMode wrap) = 0;
      virtual void GetWrapMode(flOUT WrapMode *pWrapX, flOUT WrapMode *pWrapY) const = 0;

      virtual void SetWrapModeX(flIN WrapMode wrap) = 0;
      virtual void SetWrapModeY(flIN WrapMode wrap) = 0;

      virtual void SetFilterMinMode(flIN FilterMode mode, flIN bool useMipmaps = false) = 0;
      virtual void SetFilterMagMode(flIN FilterMode mode) = 0;

      virtual FilterMode GetFilterMinMode(bool *pUseMipmaps = nullptr) const = 0;
      virtual FilterMode GetFilterMagMode() const = 0;

      virtual void SetBorderColour(flIN Util::Colour *pColour) = 0;
      virtual void GetBorderColour(flOUT Util::Colour *pColour) const = 0;

      virtual void * GetNativeResource() = 0;
    };
  }
}

#endif // flTexture_h__
