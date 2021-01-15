#include "util/flImage.h"
#include "atVector.h"

using namespace flEngine;

static Util::ColourU32 _SampleNearest(float u, float v, const atVector<Util::ColourU32> &pixels, const int64_t &w, const int64_t &h)
{
  return pixels[(int64_t)(uv.x * w + 0.5f) + (int64_t)(uv.y * h + 0.5f) * w];
}

static Util::ColourU32 _SampleBilinear(float u, float v, const atVector<Util::ColourU32> &pixels, const int64_t &w, const int64_t &h)
{
  Math::Vec2F uv(u, v);
  int64_t x = (int64_t)(uv.x * w) % w;
  int64_t y = (int64_t)(uv.y * h) % h;
  int64_t x2 = (x + 1) % w;
  int64_t y2 = (y + 1) % h;

  Math::Vec2F _min = Math::Vec2F{ (float)x / (float)w, (float)y / (float)h };
  Math::Vec2F _max = Math::Vec2F{ (float)(x + 1) / (float)w, (float)(y + 1) / (float)h };
  Math::Vec2F _lower = (_max - uv) / (_max - _min);
  Math::Vec2F _upper = (uv - _min) / (_max - _min);

  Util::Colour a = Util::Colour(pixels[x + y * w])   * (1.f - _lower.x) * (1.f - _lower.y);
  Util::Colour b = Util::Colour(pixels[x + y2 * w])  * (1.f - _lower.x) * (1.f - _upper.y);
  Util::Colour c = Util::Colour(pixels[x2 + y * w])  * (1.f - _upper.x) * (1.f - _lower.y);
  Util::Colour d = Util::Colour(pixels[x2 + y2 * w]) * (1.f - _upper.x) * (1.f - _upper.y);

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

      }

      void Construct(flIN const Colour *pPixels, flIN const Math::Vec2I *pSize)
      {
        m_pixels.reserve(pSize->x * pSize->y);
        for (const Colour &col : atIterate(pPixels, pSize->x * pSize->y))
          m_pixels.push_back(col);
      }

      void Construct(flIN const ColourU32 *pPixels, flIN const Math::Vec2I *pSize)
      {
        m_pixels.insert(0, pPixels, pPixels + pSize->x * pSize->y);
      }

      void Construct(flIN const Math::Vec2I *pSize, flIN ColourU32 initialColour = ColourU32_Black)
      {
        m_pixels.resize(pSize->x * pSize->y, initialColour);
      }

      void Resize(flIN const Math::Vec2I *pSize, flIN const SampleType sampleType)
      {
        atVector<ColourU32> newPixels;
        newPixels.resize(pSize->x * pSize->y);
        Math::Vec2F uv = 0;
        Math::Vec2F uvStep = 1.0f / Math::Vec2F(*pSize);
        for (int64_t y = 0; y < pSize->y; ++y, uv.y += uvStep.y)
          for (int64_t x = 0; x < pSize->x; ++x, uv.x += uvStep.x)
            newPixels[x + y * m_size.x] = Sample(&uv, sampleType);

        m_size = *pSize;
        std::swap(m_pixels, newPixels);
      }

      ColourU32 Sample(flIN const Math::Vec2F *pUV, flIN const SampleType sampleType) const
      {
        switch (sampleType)
        {
        case ST_Nearest: return _SampleNearest(pUV->x, pUV->y, m_pixels, m_size.x, m_size.y);
        case ST_Bilinear: return _SampleBilinear(pUV->x, pUV->y, m_pixels, m_size.x, m_size.y);
        }
      }

      ColourU32* GetPixels() { return m_pixels.data(); }
      const ColourU32* GetPixels() const { return m_pixels.data(); }

      Math::Vec2I GetSize() const { return m_size; }

      Math::Vec2I         m_size;
      atVector<ColourU32> m_pixels;
    };
  }
}

using namespace flEngine::Util;

flPIMPL_IMPL(Image)
flPIMPL_IMPL_COPY(Image)
flPIMPL_IMPL_MOVE(Image)

#define flIMPL flPIMPL(Image)

Image::Image(flIN const char *path)
{
  flIMPL->Construct(path);
}

Image::Image(flIN const Colour *pPixels, flIN const Math::Vec2I *pSize)
{
  flIMPL->Construct(pPixels, pSize);
}

Image::Image(flIN const ColourU32 *pPixels, flIN const Math::Vec2I *pSize)
{
  flIMPL->Construct(pPixels, pSize);
}

Image::Image(flIN const Math::Vec2I *pSize, flIN ColourU32 initialColour)
{
  flIMPL->Construct(pSize, initialColour);
}

void Image::Resize(flIN const Math::Vec2I *pSize, flIN const SampleType sampleType)
{
  flIMPL->Construct(pSize, sampleType);
}

ColourU32 Image::Sample(flIN const Math::Vec2F *pUV, flIN const SampleType sampleType) const
{
  return flIMPL->Sample(pUV, sampleType);
}

ColourU32* Image::GetPixels()
{
  return flIMPL->GetPixels();
}

const ColourU32* Image::GetPixels() const
{
  return flIMPL->GetPixels();
}

Math::Vec2I Image::GetSize() const
{
  return flIMPL->GetSize();
}
