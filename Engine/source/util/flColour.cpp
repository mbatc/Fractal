#include "util/flColour.h"

using namespace flEngine::Util;

Colour::Colour(const ColourU32 &val)
{
  r = flCOLOUR_UNPACK_RED(val) / 255.0f;
  g = flCOLOUR_UNPACK_GREEN(val) / 255.0f;
  b = flCOLOUR_UNPACK_BLUE(val) / 255.0f;
  a = flCOLOUR_UNPACK_ALPHA(val) / 255.0f;
}

Colour::operator ColourU32() const
{
  return ToU32();
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
