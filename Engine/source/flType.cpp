#include "flType.h"
#include <string.h>

namespace Fractal
{
  int64_t SizeOf(flIN Type type)
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

  char const* NameOfType(flIN Type type)
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

  template<typename To, typename From>
  void _Convert(void* pDest, void const* pSrc, int64_t count)
  {
    To* pTo = (To*)pDest;
    From const* pFrom = (From const*)pSrc;
    while (count-- > 0)
      *(pTo++) =  To(*(pFrom++));
  }

  template<typename To>
  void _Convert(void* pDest, void const* pSrc, Type srcType, int64_t count)
  {
    switch (srcType)
    {
    case Type_Bool:    // Fall-through
    case Type_Int8:    return _Convert<To, int8_t>(pDest, pSrc, count);
    case Type_Int16:   return _Convert<To, int16_t>(pDest, pSrc, count);
    case Type_Int32:   return _Convert<To, int32_t>(pDest, pSrc, count);
    case Type_Int64:   return _Convert<To, int64_t>(pDest, pSrc, count);
    case Type_UInt8:   return _Convert<To, uint8_t>(pDest, pSrc, count);
    case Type_UInt16:  return _Convert<To, uint16_t>(pDest, pSrc, count);
    case Type_UInt32:  return _Convert<To, uint32_t>(pDest, pSrc, count);
    case Type_UInt64:  return _Convert<To, uint64_t>(pDest, pSrc, count);
    case Type_Float32: return _Convert<To, float>(pDest, pSrc, count);
    case Type_Float64: return _Convert<To, double>(pDest, pSrc, count);
    }
  }

  void ConvertPrimitive(void* pDest, Type destType, void const* pSrc, Type srcType, int64_t count)
  {
    if (destType == srcType)
    {
      memcpy(pDest, pSrc, count * SizeOf(srcType));
      return;
    }

    switch (destType)
    {
    case Type_Bool:    // Fall-through
    case Type_Int8:    return _Convert<int8_t>(pDest, pSrc, srcType, count);
    case Type_Int16:   return _Convert<int16_t>(pDest, pSrc, srcType, count);
    case Type_Int32:   return _Convert<int32_t>(pDest, pSrc, srcType, count);
    case Type_Int64:   return _Convert<int64_t>(pDest, pSrc, srcType, count);
    case Type_UInt8:   return _Convert<uint8_t>(pDest, pSrc, srcType, count);
    case Type_UInt16:  return _Convert<uint16_t>(pDest, pSrc, srcType, count);
    case Type_UInt32:  return _Convert<uint32_t>(pDest, pSrc, srcType, count);
    case Type_UInt64:  return _Convert<uint64_t>(pDest, pSrc, srcType, count);
    case Type_Float32: return _Convert<float>(pDest, pSrc, srcType, count);
    case Type_Float64: return _Convert<double>(pDest, pSrc, srcType, count);
    }
  }
}

