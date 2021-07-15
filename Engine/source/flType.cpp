#include "flType.h"
#include <string.h>

template<typename To, typename From>
void _Convert(void* pDest, void const* pSrc, int64_t count)
{
  To* pTo = (To*)pDest;
  From const* pFrom = (From const*)pSrc;
  while (count-- > 0)
    *(pTo++) = To(*(pFrom++));
}

template<typename To>
void _Convert(void* pDest, void const* pSrc, Fractal::Type srcType, int64_t count)
{
  switch (srcType)
  {
  case Fractal::Type_Bool:    // Fall-through
  case Fractal::Type_Int8:    return _Convert<To, int8_t>(pDest, pSrc, count);
  case Fractal::Type_Int16:   return _Convert<To, int16_t>(pDest, pSrc, count);
  case Fractal::Type_Int32:   return _Convert<To, int32_t>(pDest, pSrc, count);
  case Fractal::Type_Int64:   return _Convert<To, int64_t>(pDest, pSrc, count);
  case Fractal::Type_UInt8:   return _Convert<To, uint8_t>(pDest, pSrc, count);
  case Fractal::Type_UInt16:  return _Convert<To, uint16_t>(pDest, pSrc, count);
  case Fractal::Type_UInt32:  return _Convert<To, uint32_t>(pDest, pSrc, count);
  case Fractal::Type_UInt64:  return _Convert<To, uint64_t>(pDest, pSrc, count);
  case Fractal::Type_Float32: return _Convert<To, float>(pDest, pSrc, count);
  case Fractal::Type_Float64: return _Convert<To, double>(pDest, pSrc, count);
  }
}
extern "C" {
  int64_t Fractal_GetNextTypeID()
  {
    static int64_t nextID = 0;
    return nextID++;
  }

  void Fractal_ConvertPrimitive(void* pDest, Fractal::Type destType, void const* pSrc, Fractal::Type srcType, int64_t count)
  {
    if (destType == srcType)
    {
      memcpy(pDest, pSrc, count * Fractal_SizeOf(srcType));
      return;
    }

    switch (destType)
    {
    case Fractal::Type_Bool:    // Fall-through
    case Fractal::Type_Int8:    return _Convert<int8_t>(pDest, pSrc, srcType, count);
    case Fractal::Type_Int16:   return _Convert<int16_t>(pDest, pSrc, srcType, count);
    case Fractal::Type_Int32:   return _Convert<int32_t>(pDest, pSrc, srcType, count);
    case Fractal::Type_Int64:   return _Convert<int64_t>(pDest, pSrc, srcType, count);
    case Fractal::Type_UInt8:   return _Convert<uint8_t>(pDest, pSrc, srcType, count);
    case Fractal::Type_UInt16:  return _Convert<uint16_t>(pDest, pSrc, srcType, count);
    case Fractal::Type_UInt32:  return _Convert<uint32_t>(pDest, pSrc, srcType, count);
    case Fractal::Type_UInt64:  return _Convert<uint64_t>(pDest, pSrc, srcType, count);
    case Fractal::Type_Float32: return _Convert<float>(pDest, pSrc, srcType, count);
    case Fractal::Type_Float64: return _Convert<double>(pDest, pSrc, srcType, count);
    }
  }

  int64_t Fractal_SizeOf(flIN Fractal::Type type)
  {
    switch (type)
    {
    case Fractal::Type_Int8:    return sizeof(int8_t);
    case Fractal::Type_Int16:   return sizeof(int16_t);
    case Fractal::Type_Int32:   return sizeof(int32_t);
    case Fractal::Type_Int64:   return sizeof(int64_t);
    case Fractal::Type_UInt8:   return sizeof(uint8_t);
    case Fractal::Type_UInt16:  return sizeof(uint16_t);
    case Fractal::Type_UInt32:  return sizeof(uint32_t);
    case Fractal::Type_UInt64:  return sizeof(uint64_t);
    case Fractal::Type_Bool:    return sizeof(bool);
    case Fractal::Type_Float32: return sizeof(float);
    case Fractal::Type_Float64: return sizeof(double);
    }

    return 0;
  }

  char const* Fractal_NameOfType(flIN Fractal::Type type)
  {
    switch (type)
    {
    case Fractal::Type_Int8:    return "int8";
    case Fractal::Type_Int16:   return "int16";
    case Fractal::Type_Int32:   return "int32";
    case Fractal::Type_Int64:   return "int64";
    case Fractal::Type_UInt8:   return "uint8";
    case Fractal::Type_UInt16:  return "uint16";
    case Fractal::Type_UInt32:  return "uint32";
    case Fractal::Type_UInt64:  return "uint64";
    case Fractal::Type_Bool:    return "bool";
    case Fractal::Type_Float32: return "float";
    case Fractal::Type_Float64: return "double";
    }
    return "unknown";
  }
}
