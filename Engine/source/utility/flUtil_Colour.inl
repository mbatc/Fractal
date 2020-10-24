#include "atColor.h"

namespace flEngine
{
  namespace Util
  {
    namespace Colour
    {
      inline Math::Vec4D ToVec4(uint32_t colour) { return atColor::UnPack<double>(col); }
      inline Math::Vec3D ToVec3(uint32_t colour) { return atColor::UnPack<double>(col); }

      inline uint32_t FromVec3(const Math::Vec3D &colour) { return atColor::Pack(colour); }
      inline uint32_t FromVec4(const Math::Vec4D &colour) { return atColor::Pack(colour); }

      inline uint8_t GetChannel(uint32_t colour, int64_t c) { return colour >> (c * 8) & 0xFF; }
    };
  }
};
