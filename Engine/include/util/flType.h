#ifndef fl_Util_Type_h__
#define fl_Util_Type_h__

#include "../flConfig.h"

namespace flEngine
{
  namespace Util
  {
    enum Type
    {
      Type_Unknown,
      Type_Int8,
      Type_Int16,
      Type_Int32,
      Type_Int64,
      Type_UInt8,
      Type_UInt16,
      Type_UInt32,
      Type_UInt64,
      Type_Bool,
      Type_Float32,
      Type_Float64,
    };

    inline constexpr Type TypeOf(int8_t)   { return Type_Int8;    }
    inline constexpr Type TypeOf(int16_t)  { return Type_Int16;   }
    inline constexpr Type TypeOf(int32_t)  { return Type_Int32;   }
    inline constexpr Type TypeOf(int64_t)  { return Type_Int64;   }
    inline constexpr Type TypeOf(uint8_t)  { return Type_UInt8;   }
    inline constexpr Type TypeOf(uint16_t) { return Type_UInt16;  }
    inline constexpr Type TypeOf(uint32_t) { return Type_UInt32;  }
    inline constexpr Type TypeOf(uint64_t) { return Type_UInt64;  }
    inline constexpr Type TypeOf(bool)     { return Type_Bool;    }
    inline constexpr Type TypeOf(float)    { return Type_Float32; }
    inline constexpr Type TypeOf(double)   { return Type_Float64; }
    inline constexpr Type TypeOf(...)      { return Type_Unknown; }

    flEXPORT int64_t SizeOf(flIN Type type);

    flEXPORT char const * NameOfType(flIN Type type);
  }
}

#endif // fl_Util_Type_h__
