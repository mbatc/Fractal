#pragma once

#include "flConfig.h"

namespace Fractal
{
  enum Type
  {
    Type_Unknown = -1,
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

  template<typename T> inline constexpr Type TypeOf() { return Type_Unknown; }
  template<> inline constexpr Type TypeOf<int8_t>()   { return Type_Int8; }
  template<> inline constexpr Type TypeOf<int16_t>()  { return Type_Int16; }
  template<> inline constexpr Type TypeOf<int32_t>()  { return Type_Int32; }
  template<> inline constexpr Type TypeOf<int64_t>()  { return Type_Int64; }
  template<> inline constexpr Type TypeOf<uint8_t>()  { return Type_UInt8; }
  template<> inline constexpr Type TypeOf<uint16_t>() { return Type_UInt16; }
  template<> inline constexpr Type TypeOf<uint32_t>() { return Type_UInt32; }
  template<> inline constexpr Type TypeOf<uint64_t>() { return Type_UInt64; }
  template<> inline constexpr Type TypeOf<bool>()     { return Type_Bool; }
  template<> inline constexpr Type TypeOf<float>()    { return Type_Float32; }
  template<> inline constexpr Type TypeOf<double>()   { return Type_Float64; }

  template<typename T> inline constexpr Type TypeOf(T const&) { return TypeOf<T>(); }

  flEXPORT int64_t flCCONV SizeOf(flIN Type type);

  flEXPORT char const* flCCONV NameOfType(flIN Type type);

  flEXPORT void flCCONV ConvertPrimitive(void* pDest, Type destType, void const* pSrc, Type srcType, int64_t count);

  flEXPORT int64_t flCCONV GetNextTypeID();

  template<typename T>
  int64_t TypeID()
  {
    static int64_t id = GetNextTypeID();
    return id;
  }
}
