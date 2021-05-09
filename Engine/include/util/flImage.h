#ifndef flImage_h__
#define flImage_h__

#include "../flPImpl.h"
#include "../math/flMath.h"
#include "flColour.h"

namespace flEngine
{
  namespace Util
  {
    enum SampleType : int64_t
    {
      SampleType_Nearest,
      SampleType_Bilinear,
      SampleType_Count,
    };

    class flPIMPL_CLASS(Image);

    class flEXPORT Image
    {
      flPIMPL_DEF(Image);
      flPIMPL_DEF_MOVE(Image);
      flPIMPL_DEF_COPY(Image);

    public:
      Image(flIN const char *path);
      Image(flIN const void *pFileData, flIN int64_t fileLen);
      Image(flIN const Colour *pPixels, flIN int64_t width, flIN int64_t height);
      Image(flIN const ColourU32 *pPixels, flIN int64_t width, flIN int64_t height);
      Image(flIN int64_t width, flIN int64_t height, flIN ColourU32 initialColour = ColourU32_Black);

      void SetData(flIN ColourU32 *pPixels, flIN int64_t width, flIN int64_t height);

      ColourU32* TakeData(flOUT int64_t *pWidth = nullptr, flOUT int64_t *pHeight = nullptr);

      void Resize(flIN int64_t width, flIN int64_t height, flIN const SampleType sampleType = SampleType_Bilinear);

      ColourU32 Sample(flIN float u, flIN float v, flIN const SampleType sampleType = SampleType_Bilinear) const;

      ColourU32* GetPixels();

      const ColourU32* GetPixels() const;

      int64_t GetWidth() const;

      int64_t GetHeight() const;
    };
  }
}

#endif // flImage_h__
