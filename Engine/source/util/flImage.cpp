#include "util/flImage.h"
#include "ctVector.h"
#include "ctFile.h"

#define STBI_FAILURE_USERMSG
#define STB_IMAGE_IMPLEMENTATION
#define STBI_MALLOC(sz)           flAlloc(sz)
#define STBI_REALLOC(p,newsz)     flRealloc(p,newsz)
#define STBI_FREE(p)              flFree(p)
#include "stb/stb_image.h"

using namespace flEngine;
using namespace flEngine::Math;
using namespace flEngine::Util;

static ColourU32 _SampleNearest(float u, float v, const ctVector<ColourU32> &pixels, const int64_t &w, const int64_t &h)
{
  return pixels[(int64_t)((double)u * w + 0.5) + (int64_t)((double)v * h + 0.5) * w];
}

static ColourU32 _SampleBilinear(float u, float v, const ctVector<ColourU32> &pixels, const int64_t &w, const int64_t &h)
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

  Colour a = Colour(pixels[x + y * w])   * (1.f - _lower.x) * (1.f - _lower.y);
  Colour b = Colour(pixels[x + y2 * w])  * (1.f - _lower.x) * (1.f - _upper.y);
  Colour c = Colour(pixels[x2 + y * w])  * (1.f - _upper.x) * (1.f - _lower.y);
  Colour d = Colour(pixels[x2 + y2 * w]) * (1.f - _upper.x) * (1.f - _upper.y);

  return a + b + c + d;
}

namespace flEngine
{
  namespace Util
  {
    class flPIMPL_CLASS(Image)
    {
    public:
      void Construct(flIN const char *path)
      {
        ctVector<uint8_t> data = ctFile::ReadFile(path);
        Construct(data.data(), data.size());
      }

      void Construct(flIN const void *pFileData, flIN int64_t fileLen)
      {
        int x, y, ncomp;
        uint8_t *pPixels = stbi_load_from_memory((uint8_t*)pFileData, (int)fileLen, &x, &y, &ncomp, 4);
        if (!pPixels)
        {
          printf("Failed to load image: %s\n", stbi_failure_reason());
          return;
        }

        SetData((ColourU32 *)pPixels, x, y);
      }

      void Construct(flIN const Colour *pPixels, flIN const Math::Vec2I &size)
      {
        m_pixels.reserve((int64_t)size.x * size.y);
        for (const Colour &col : ctIterate(pPixels, size.x * size.y))
          m_pixels.push_back(col);
      }

      void Construct(flIN const ColourU32 *pPixels, flIN const Math::Vec2I &size)
      {
        m_pixels.insert(0, pPixels, pPixels + (int64_t)size.x * size.y);
      }

      void Construct(flIN const Math::Vec2I &size, flIN ColourU32 initialColour = ColourU32_Black)
      {
        m_pixels.resize((int64_t)size.x * size.y, initialColour);
      }

      void SetData(flIN ColourU32 *pPixels, flIN int64_t width, flIN int64_t height)
      {
        int64_t len = width * height;
        m_pixels.set_data(pPixels, len, len);
        m_size = { width, height };
      }

      ColourU32* TakeData(flOUT int64_t *pWidth = nullptr, flOUT int64_t *pHeight = nullptr)
      {
        ColourU32 *pData = m_pixels.take_data();
        if (pWidth)  *pWidth  = m_size.x;
        if (pHeight) *pHeight = m_size.y;
        m_size = { 0 };
        return pData;
      }

      void Resize(flIN const Math::Vec2I &size, flIN const SampleType sampleType)
      {
        ctVector<ColourU32> newPixels;
        newPixels.resize((int64_t)size.x * size.y);
        Vec2F uv = 0;
        Vec2F uvStep = 1.0f / Vec2F(size);
        for (int64_t y = 0; y < size.y; ++y, uv.y += uvStep.y)
          for (int64_t x = 0; x < size.x; ++x, uv.x += uvStep.x)
            newPixels[x + y * m_size.x] = Sample(uv, sampleType);

        m_size = size;
        std::swap(m_pixels, newPixels);
      }

      ColourU32 Sample(flIN const Math::Vec2F &uv, flIN const SampleType sampleType) const
      {
        switch (sampleType)
        {
        case SampleType_Nearest:  return _SampleNearest(uv.x, uv.y, m_pixels, m_size.x, m_size.y);
        case SampleType_Bilinear: return _SampleBilinear(uv.x, uv.y, m_pixels, m_size.x, m_size.y);
        }
        return ColourU32_Black;
      }

      ColourU32* GetPixels() { return m_pixels.data(); }
      const ColourU32* GetPixels() const { return m_pixels.data(); }

      Math::Vec2I GetSize() const { return m_size; }

      Math::Vec2I         m_size;
      ctVector<ColourU32> m_pixels;
    };

    flPIMPL_IMPL(Image);
    flPIMPL_IMPL_COPY(Image);
    flPIMPL_IMPL_MOVE(Image);

    Image::Image(flIN const char* path)
    {
      Impl()->Construct(path);
    }

    Image::Image(flIN const void* pFileData, flIN int64_t fileLen)
    {
      Impl()->Construct(pFileData, fileLen);
    }

    Image::Image(flIN const Colour* pPixels, flIN int64_t width, flIN int64_t height)
    {
      Impl()->Construct(pPixels, Vec2I(width, height));
    }

    Image::Image(flIN const ColourU32* pPixels, flIN int64_t width, flIN int64_t height)
    {
      Impl()->Construct(pPixels, Vec2I(width, height));
    }

    Image::Image(flIN int64_t width, flIN int64_t height, flIN ColourU32 initialColour)
    {
      Impl()->Construct(Vec2I(width, height), initialColour);
    }

    void Image::SetData(flIN ColourU32* pPixels, flIN int64_t width, flIN int64_t height)
    {
      Impl()->SetData(pPixels, width, height);
    }

    ColourU32* Image::TakeData(flOUT int64_t* pWidth, flOUT int64_t* pHeight)
    {
      return Impl()->TakeData(pWidth, pHeight);
    }

    void Image::Resize(flIN int64_t width, flIN int64_t height, flIN const SampleType sampleType)
    {
      Impl()->Construct(Vec2I(width, height), sampleType);
    }

    ColourU32 Image::Sample(flIN float u, flIN float v, flIN const SampleType sampleType) const
    {
      return Impl()->Sample(Vec2F(u, v), sampleType);
    }

    ColourU32* Image::GetPixels()
    {
      return Impl()->GetPixels();
    }

    const ColourU32* Image::GetPixels() const
    {
      return Impl()->GetPixels();
    }

    int64_t Image::GetWidth() const
    {
      return Impl()->GetSize().x;
    }

    int64_t Image::GetHeight() const
    {
      return Impl()->GetSize().y;
    }
  }
}
