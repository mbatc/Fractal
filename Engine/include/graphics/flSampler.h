#ifndef flTexture_h__
#define flTexture_h__

#include "../flInterface.h"
#include "../util/flColour.h"

namespace flEngine
{
  namespace Graphics
  {
    enum class WrapMode
    {
      Repeat,
      Mirror,
      ClampToEdge,
    };

    enum class FilterMode
    {
      Linear,
      Nearest,
    };

    class flEXPORT Sampler : public Interface
    {
    public:
      virtual void SetWrapMode(flIN WrapMode wrap) = 0;
      virtual void GetWrapMode(flOUT WrapMode *pWrapX, flOUT WrapMode *pWrapY) const = 0;

      virtual void SetWrapModeX(flIN WrapMode wrap) = 0;
      virtual void SetWrapModeY(flIN WrapMode wrap) = 0;

      virtual void SetFilterMinMode(flIN FilterMode mode) = 0;
      virtual void SetFilterMagMode(flIN FilterMode mode) = 0;

      virtual FilterMode GetFilterMinMode() const = 0;
      virtual FilterMode GetFilterMagMode() const = 0;

      virtual void SetBorderColour(flIN Util::Colour *pColour) = 0;
      virtual void GetBorderColour(flOUT Util::Colour *pColour) const = 0;

      virtual void * GetNativeResource() = 0;
    };
  }
}

#endif // flTexture_h__
