#include "flPixelFormat.h"

namespace Fractal
{
  flEXPORT int64_t Fractal::GetPixelComponentSize(flIN PixelComponentType type)
  {
    switch (type)
    {
    case PixelComponentType_UInt8:   return 1;
    case PixelComponentType_UInt16:  return 2;
    case PixelComponentType_UInt32:  return 4;
    case PixelComponentType_Int8:    return 1;
    case PixelComponentType_Int16:   return 2;
    case PixelComponentType_Int32:   return 4;
    case PixelComponentType_Norm8:   return 1;
    case PixelComponentType_Norm16:  return 2;
    case PixelComponentType_UNorm8:  return 1;
    case PixelComponentType_UNorm16: return 2;
    case PixelComponentType_Float16: return 2;
    case PixelComponentType_Float32: return 4;
    }
    return PixelComponentType_Unknown;
  }

  flEXPORT int64_t Fractal::GetPixelComponentCount(flIN PixelFormat type)
  {
    switch (type)
    {
    case PixelFormat_Red:  return 1;
    case PixelFormat_RG:   return 2;
    case PixelFormat_RGB:  return 3;
    case PixelFormat_RGBA: return 4;
    }
    return PixelFormat_Unknown;
  }

  flEXPORT int64_t Fractal::GetDepthFormatSize(flIN DepthFormat type)
  {
    switch (type)
    {
    case DepthFormat_Float16:         return 2;
    case DepthFormat_Float24:         return 3;
    case DepthFormat_Float32:         return 4;
    case DepthFormat_Float24Stencil8: return 4;
    case DepthFormat_Float32Stencil8: return 5;
    }
    return DepthFormat_Unknown;
  }

}