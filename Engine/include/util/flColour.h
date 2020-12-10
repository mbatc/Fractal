#ifndef flColour_h__
#define flColour_h__

#include <stdint.h>
#include <type_traits>
#include "../flConfig.h"

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

namespace flEngine
{
  namespace Util
  {
    typedef uint32_t ColourU32;

    class flEXPORT Colour
    {
    public:
      Colour(const ColourU32 &val = 0xFF000000);

      operator ColourU32() const;

      ColourU32 ToU32() const;

      // Get a component of the Colour
      float& operator[](int idx);
      const float& operator[](int idx) const;

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
}

#endif // flColour_h__
