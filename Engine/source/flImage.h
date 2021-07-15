#pragma once

#include "flIImage.h"
#include "ctVector.h"
#include "ctFile.h"

namespace Fractal
{
  namespace Impl
  {
    class Image : public IImage
    {
      FRACTAL_DEFAULT_INTERFACE;

    public:
      Image(flIN char const* path);
      Image(flIN void const* pFileData, flIN int64_t fileLen);
      Image(flIN Colour const * pPixels, flIN int64_t width, flIN int64_t height);
      Image(flIN ColourU32 const * pPixels, flIN int64_t width, flIN int64_t height);
      Image(flIN Vec2I const& size, flIN ColourU32 initialColour = ColourU32_Black);

      virtual void SetData(flIN ColourU32* pPixels, flIN int64_t width, flIN int64_t height) override;

      virtual ColourU32* TakeData(flOUT int64_t* pWidth = nullptr, flOUT int64_t* pHeight = nullptr) override;

      virtual void Resize(flIN int64_t width, flIN int64_t height, flIN const SampleType sampleType) override;

      virtual ColourU32 Sample(flIN float u, flIN float v, flIN SampleType const sampleType) const override;

      virtual ColourU32* GetPixels() override;

      virtual const ColourU32* GetPixels() const  override;

      virtual int64_t GetWidth() const  override;
     
      virtual int64_t GetHeight() const  override;

    private:
      void LoadFileFromMemory(flIN void const* pFileData, flIN int64_t fileLen);

      Vec2I m_size;
      ctVector<ColourU32> m_pixels;
    };
  }
}
