#include "util/flType.h"

using namespace flEngine::Util;

int64_t flEngine::Util::SizeOf(flIN Type type)
{
  switch (type)
  {
  case Type_Int8:    return sizeof(int8_t);
  case Type_Int16:   return sizeof(int16_t);
  case Type_Int32:   return sizeof(int32_t);
  case Type_Int64:   return sizeof(int64_t);
  case Type_UInt8:   return sizeof(uint8_t);
  case Type_UInt16:  return sizeof(uint16_t);
  case Type_UInt32:  return sizeof(uint32_t);
  case Type_UInt64:  return sizeof(uint64_t);
  case Type_Bool:    return sizeof(bool);
  case Type_Float32: return sizeof(float);
  case Type_Float64: return sizeof(double);
  }

  return 0;
}

char const* flEngine::Util::NameOfType(flIN Type type)
{
  switch (type)
  {
  case Type_Int8:    return "int8";
  case Type_Int16:   return "int16";
  case Type_Int32:   return "int32";
  case Type_Int64:   return "int64";
  case Type_UInt8:   return "uint8";
  case Type_UInt16:  return "uint16";
  case Type_UInt32:  return "uint32";
  case Type_UInt64:  return "uint64";
  case Type_Bool:    return "bool";
  case Type_Float32: return "float";
  case Type_Float64: return "double";
  }
  return "unknown";
}
