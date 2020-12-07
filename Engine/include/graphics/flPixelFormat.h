#ifndef flPixelFormat_h__
#define flPixelFormat_h__

namespace flEngine
{
  namespace Graphics
  {
    enum PixelFormat
    {
      PF_Red,
      PF_RG,
      PF_RGB,
      PF_RGBA,
      PF_Count,
    };

    enum PixelComponentType
    {
      PCT_UInt8,
      PCT_UInt16,
      PCT_UInt32,
      PCT_Int8,
      PCT_Int16,
      PCT_Int32,
      PCT_UNorm8,
      PCT_UNorm16,
      PCT_Float16,
      PCT_Float32,
      PCT_Count,
    };

    enum DepthFormat
    {
      DF_Float16,
      DF_Float24,
      DF_Float32,
      DF_Float24Stencil8,
      DF_Float32Stencil8,
    };
  }
}

#endif // flPixelFormat_h__