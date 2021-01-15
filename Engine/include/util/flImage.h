#ifndef flImage_h__
#define flImage_h__

#include "../flPImpl.h"
#include "../math/flMath.h"
#include "flColour.h"

namespace flEngine
{
  namespace Util
  {
    enum SampleType
    {
      ST_Nearest,
      ST_Bilinear
    };

    class flPIMPL_CLASS(Image);

    class flEXPORT Image
    {
      flPIMPL_DEF(Image);
      flPIMPL_DEF_MOVE(Image);
      flPIMPL_DEF_COPY(Image);
    public:
      Image(flIN const char *path);
      Image(flIN const Colour *pPixels, flIN const Math::Vec2I *pSize);
      Image(flIN const ColourU32 *pPixels, flIN const Math::Vec2I *pSize);
      Image(flIN const Math::Vec2I *pSize, flIN ColourU32 initialColour = ColourU32_Black);

      void Resize(flIN const Math::Vec2I *pSize, flIN const SampleType sampleType = ST_Bilinear);

      ColourU32 Sample(flIN const Math::Vec2F *pUV, flIN const SampleType sampleType = ST_Bilinear) const;

      ColourU32* GetPixels();

      const ColourU32* GetPixels() const;

      Math::Vec2I GetSize() const;
    };
  }
}

#endif // flImage_h__
