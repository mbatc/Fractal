#pragma once

#include <stdint.h>
#include <type_traits>
#include "flConfig.h"
#include "flMath.h"

#define flCOLOUR_MASK_RED(x)     (0x000000FF & uint32_t(x))
#define flCOLOUR_MASK_GREEN(x)   (0x0000FF00 & uint32_t(x))
#define flCOLOUR_MASK_BLUE(x)    (0x00FF0000 & uint32_t(x))
#define flCOLOUR_MASK_ALPHA(x)   (0xFF000000 & uint32_t(x))

#define flCOLOUR_PACK_RED(x)     flCOLOUR_MASK_RED(uint8_t(x))
#define flCOLOUR_PACK_GREEN(x)   flCOLOUR_MASK_GREEN(uint8_t(x) << 8)
#define flCOLOUR_PACK_BLUE(x)    flCOLOUR_MASK_BLUE(uint8_t(x) << 16)
#define flCOLOUR_PACK_ALPHA(x)   flCOLOUR_MASK_ALPHA(uint8_t(x) << 24)

#define flCOLOUR_UNPACK_RED(x)   flCOLOUR_MASK_RED(uint32_t(x))
#define flCOLOUR_UNPACK_GREEN(x) flCOLOUR_MASK_RED(uint32_t(x) >> 8)
#define flCOLOUR_UNPACK_BLUE(x)  flCOLOUR_MASK_RED(uint32_t(x) >> 16)
#define flCOLOUR_UNPACK_ALPHA(x) flCOLOUR_MASK_RED(uint32_t(x) >> 24)

namespace Fractal
{
  typedef uint32_t ColourU32;

  enum : uint32_t
  {
    ColourU32_Black = 0xFF000000,
    ColourU32_White = 0xFFFFFFFF,
    ColourU32_Red = 0xFF0000FF,
    ColourU32_Green = 0xFF00FF00,
    ColourU32_Blue = 0xFFFF0000,
  };

  class flEXPORT Colour
  {
  public:
    Colour(float r, float g, float b, float a = 1.0f);
    Colour(const Colour& o);
    Colour(const ColourU32& val = ColourU32_White);

    inline Colour(const Vec3F& vec) : Colour(vec.x, vec.y, vec.z, 1) {}
    inline Colour(const Vec4F& vec) : Colour(vec.x, vec.y, vec.z, vec.w) {}

    Colour& operator=(const Colour& rhs);
    bool operator==(const Colour& rhs) const;
    bool operator!=(const Colour& rhs) const;

    operator ColourU32() const;
    operator Vec4F() const;
    ColourU32 ToU32() const;

    // Get a component of the Colour
    float& operator[](int idx);
    const float& operator[](int idx) const;

    Colour operator+(const float& rhs) const;
    Colour operator-(const float& rhs) const;
    Colour operator/(const float& rhs) const;
    Colour operator*(const float& rhs) const;

    Colour operator+(const Colour& rhs) const;
    Colour operator-(const Colour& rhs) const;
    Colour operator/(const Colour& rhs) const;
    Colour operator*(const Colour& rhs) const;

    union
    {
      float channel[4];
      struct
      {
        float r;
        float g;
        float b;
        float a;
      };
    };
  };
}
