#ifndef flUtil_Colour_h__
#define flUtil_Colour_h__

#include "flMath.h"

namespace flEngine
{
  namespace Util
  {
    namespace Colour
    {
      inline Math::Vec4D ToVec4(uint32_t col);
      inline Math::Vec3D ToVec3(uint32_t col);

      inline uint32_t FromVec3(const Math::Vec3D &colour);
      inline uint32_t FromVec4(const Math::Vec4D &colour);

      inline uint8_t GetChannel(uint32_t col, int64_t c);
    };
  }
};

#include "flUtil_Colour.inl"

#endif // flUtil_Colour_h__
