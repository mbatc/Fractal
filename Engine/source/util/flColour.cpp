#include "util/flColour.h"
#include <string.h>

using namespace flEngine;
using namespace flEngine::Util;

Colour::Colour(float r, float g, float b, float a)
  : r(r)
  , b(b)
  , g(g)
  , a(a)
{}

Colour::Colour(const Colour &o) { *this = o; }

Colour::Colour(const ColourU32 &val)
{
  r = flCOLOUR_UNPACK_RED(val) / 255.0f;
  g = flCOLOUR_UNPACK_GREEN(val) / 255.0f;
  b = flCOLOUR_UNPACK_BLUE(val) / 255.0f;
  a = flCOLOUR_UNPACK_ALPHA(val) / 255.0f;
}

Colour& Colour::operator=(const Colour &rhs)
{
  memcpy(channel, rhs.channel, sizeof(channel));
  return *this;
}

bool Colour::operator==(const Colour &rhs) const
{
  return memcmp(channel, rhs.channel, sizeof(channel)) == 0;
}

bool Colour::operator!=(const Colour &rhs) const
{
  return !(*this == rhs);
}

Colour::operator ColourU32() const
{
  return ToU32();
}

Colour::operator Math::Vec4F() const
{
  return Math::Vec4F(r, g, b, a);
}

ColourU32 Colour::ToU32() const
{
  ColourU32 u32 = 0;
  u32 |= flCOLOUR_PACK_RED(r / 255.0f);
  u32 |= flCOLOUR_PACK_GREEN(r / 255.0f);
  u32 |= flCOLOUR_PACK_BLUE(r / 255.0f);
  u32 |= flCOLOUR_PACK_ALPHA(r / 255.0f);
  return u32;
}

float& Colour::operator[](int idx)
{
  return channel[idx];
}

const float& Colour::operator[](int idx) const
{
  return channel[idx];
}

Colour Colour::operator+(const float &rhs) const
{
  return Colour(r + rhs, g + rhs, b + rhs, a + rhs);
}

Colour Colour::operator-(const float &rhs) const
{
  return Colour(r - rhs, g - rhs, b - rhs, a - rhs);
}

Colour Colour::operator/(const float &rhs) const
{
  return Colour(r / rhs, g / rhs, b / rhs, a / rhs);
}

Colour Colour::operator*(const float &rhs) const
{
  return Colour(r * rhs, g * rhs, b * rhs, a * rhs);
}

Colour Colour::operator+(const Colour &rhs) const
{
  return Colour(r + rhs.r, g + rhs.g, b + rhs.b, a + rhs.a);
}

Colour Colour::operator-(const Colour &rhs) const
{
  return Colour(r - rhs.r, g - rhs.g, b - rhs.b, a - rhs.a);
}

Colour Colour::operator/(const Colour &rhs) const
{
  return Colour(r / rhs.r, g / rhs.g, b / rhs.b, a / rhs.a);
}

Colour Colour::operator*(const Colour &rhs) const
{
  return Colour(r * rhs.r, g * rhs.g, b * rhs.b, a * rhs.a);
}
