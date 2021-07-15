#include "flImage.h"
#include "flLog.h"

#define STBI_FAILURE_USERMSG
#define STB_IMAGE_IMPLEMENTATION
#define STBI_MALLOC(sz)           flAlloc(sz)
#define STBI_REALLOC(p,newsz)     flRealloc(p,newsz)
#define STBI_FREE(p)              flFree(p)
#include "stb/stb_image.h"

extern "C" {
  Fractal::IImage* Fractal_CreateImage(flIN int64_t width, flIN int64_t height, flIN Fractal::ColourU32 initialColour)
  {
    return flNew Fractal::Impl::Image({ (int32_t)width, (int32_t)height }, initialColour);
  }

  Fractal::IImage* Fractal_CreateImageFromFile(flIN char const* path)
  {
    return flNew Fractal::Impl::Image(path);
  }

  Fractal::IImage* Fractal_CreateImageFromMemory(flIN void const* pFileData, flIN int64_t fileLen)
  {
    return flNew Fractal::Impl::Image(pFileData, fileLen);
  }

  Fractal::IImage* Fractal_CreateImageFromPixels(flIN Fractal::Colour const* pPixels, flIN int64_t width, flIN int64_t height)
  {
    return flNew Fractal::Impl::Image(pPixels, width, height);
  }

  Fractal::IImage* Fractal_CreateImageFromPixelsU32(flIN Fractal::ColourU32 const* pPixels, flIN int64_t width, flIN int64_t height)
  {
    return flNew Fractal::Impl::Image(pPixels, width, height);
  }
}

namespace Fractal
{
  namespace Impl
  {
    static ColourU32 _SampleNearest(float u, float v, const ctVector<ColourU32>& pixels, const int64_t& w, const int64_t& h)
    {
      return pixels[(int64_t)((double)u * w + 0.5) + (int64_t)((double)v * h + 0.5) * w];
    }

    static ColourU32 _SampleBilinear(float u, float v, const ctVector<ColourU32>& pixels, const int64_t& w, const int64_t& h)
    {
      Vec2F uv(u, v);
      int64_t x = (int64_t)((double)uv.x * w) % w;
      int64_t y = (int64_t)((double)uv.y * h) % h;
      int64_t x2 = (x + 1) % w;
      int64_t y2 = (y + 1) % h;

      Vec2F _min = Vec2F{ (float)x / (float)w, (float)y / (float)h };
      Vec2F _max = Vec2F{ (float)(x + 1) / (float)w, (float)(y + 1) / (float)h };
      Vec2F _lower = (_max - uv) / (_max - _min);
      Vec2F _upper = (uv - _min) / (_max - _min);

      Colour a = Colour(pixels[x + y * w]) * (1.f - _lower.x) * (1.f - _lower.y);
      Colour b = Colour(pixels[x + y2 * w]) * (1.f - _lower.x) * (1.f - _upper.y);
      Colour c = Colour(pixels[x2 + y * w]) * (1.f - _upper.x) * (1.f - _lower.y);
      Colour d = Colour(pixels[x2 + y2 * w]) * (1.f - _upper.x) * (1.f - _upper.y);

      return a + b + c + d;
    }

    Image::Image(flIN char const* path)
    {
      ctVector<uint8_t> data = ctFile::ReadFile(path);
      LoadFileFromMemory(data.data(), data.size());
    }

    Image::Image(flIN void const* pFileData, flIN int64_t fileLen)
    {
      LoadFileFromMemory(pFileData, fileLen);
    }

    Image::Image(flIN Colour const* pPixels, flIN int64_t width, flIN int64_t height)
    {
      m_pixels.reserve(width * height);
      for (const Colour& col : ctIterate(pPixels, width * height))
        m_pixels.push_back(col);
    }

    Image::Image(flIN ColourU32 const* pPixels, flIN int64_t width, flIN int64_t height)
    {
      m_pixels.insert(0, pPixels, pPixels + (int64_t)width * height);
      m_size = { (int32_t)width, (int32_t)height };
    }

    Image::Image(flIN Vec2I const& size, flIN ColourU32 initialColour)
    {
      m_pixels.resize((int64_t)size.x * size.y, initialColour);
      m_size = size;
    }

    void Image::SetData(flIN ColourU32* pPixels, flIN int64_t width, flIN int64_t height)
    {
      int64_t len = width * height;
      m_pixels.set_data(pPixels, len, len);
      m_size = { width, height };
    }

    ColourU32* Image::TakeData(flOUT int64_t* pWidth, flOUT int64_t* pHeight)
    {
      ColourU32* pData = m_pixels.take_data();
      if (pWidth)
        *pWidth = m_size.x;
      if (pHeight)
        *pHeight = m_size.y;
      m_size = { 0 };
      return pData;
    }

    void Image::Resize(flIN int64_t width, flIN int64_t height, flIN const SampleType sampleType)
    {
      ctVector<ColourU32> newPixels;
      newPixels.resize(width * height);
      Vec2F uv = 0;
      Vec2F uvStep = 1.0f / Vec2F((float)width, (float)height);
      for (int64_t y = 0; y < height; ++y, uv.y += uvStep.y)
        for (int64_t x = 0; x < width; ++x, uv.x += uvStep.x)
          newPixels[x + y * m_size.x] = Sample(uv.x, uv.y, sampleType);

      m_size = { (int32_t)width, (int32_t)height };
      std::swap(m_pixels, newPixels);
    }

    ColourU32 Image::Sample(flIN float u, flIN float v, flIN SampleType const sampleType) const
    {
      switch (sampleType)
      {
      case SampleType_Nearest:  return _SampleNearest(u, v, m_pixels, m_size.x, m_size.y);
      case SampleType_Bilinear: return _SampleBilinear(u, v, m_pixels, m_size.x, m_size.y);
      }
      return ColourU32_Black;
    }

    ColourU32* Image::GetPixels() { return m_pixels.data(); }

    const ColourU32* Image::GetPixels() const { return m_pixels.data(); }

    int64_t Image::GetWidth() const { return m_size.x; }

    int64_t Image::GetHeight() const { return m_size.y; }

    void Image::LoadFileFromMemory(flIN void const* pFileData, flIN int64_t fileLen)
    {
      int x, y, ncomp;
      uint8_t* pPixels = stbi_load_from_memory((uint8_t*)pFileData, (int)fileLen, &x, &y, &ncomp, 4);
      if (!pPixels)
      {
        flError("Failed to load image: %s\n", stbi_failure_reason());
        return;
      }

      SetData((ColourU32*)pPixels, x, y);
    }
  }
}
