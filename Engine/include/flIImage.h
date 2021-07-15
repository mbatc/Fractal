#pragma once

#include "flInterface.h"
#include "flMath.h"
#include "flColour.h"

namespace Fractal
{
  enum SampleType : int64_t
  {
    SampleType_Nearest,
    SampleType_Bilinear,
    SampleType_Count,
  };

  class flEXPORT IImage : public Interface
  {
  public:
    virtual void SetData(flIN ColourU32* pPixels, flIN int64_t width, flIN int64_t height) = 0;

    virtual ColourU32* TakeData(flOUT int64_t* pWidth = nullptr, flOUT int64_t* pHeight = nullptr) = 0;

    virtual void Resize(flIN int64_t width, flIN int64_t height, flIN const SampleType sampleType = SampleType_Bilinear) = 0;

    virtual ColourU32 Sample(flIN float u, flIN float v, flIN const SampleType sampleType = SampleType_Bilinear) const = 0;

    virtual ColourU32* GetPixels() = 0;

    virtual const ColourU32* GetPixels() const = 0;

    virtual int64_t GetWidth() const = 0;

    virtual int64_t GetHeight() const = 0;
  };
}

extern "C" {
  flEXPORT Fractal::IImage* Fractal_CreateImage(flIN int64_t width, flIN int64_t height, flIN Fractal::ColourU32 initialColour);

  flEXPORT Fractal::IImage* Fractal_CreateImageFromFile(flIN char const * path);

  flEXPORT Fractal::IImage* Fractal_CreateImageFromMemory(flIN void const * pFileData, flIN int64_t fileLen);

  flEXPORT Fractal::IImage* Fractal_CreateImageFromPixels(flIN Fractal::Colour const * pPixels, flIN int64_t width, flIN int64_t height);

  flEXPORT Fractal::IImage* Fractal_CreateImageFromPixelsU32(flIN Fractal::ColourU32 const * pPixels, flIN int64_t width, flIN int64_t height);
}
