#include "flGLUtil.h"
#include "util/flType.h"
#include "graphics/flPixelFormat.h"
#include "graphics/flProgramDetails.h"
#include "graphics/flBufferDetails.h"

using namespace flEngine;
using namespace flEngine::Util;
using namespace flEngine::Graphics;

ProgramStage GLUtil::GetProgramStage(flIN uint32_t shader)
{
  switch (shader)
  {
  case GL_VERTEX_SHADER:          return ProgramStage_Vertex;
  case GL_FRAGMENT_SHADER:        return ProgramStage_Fragment;
  case GL_GEOMETRY_SHADER:        return ProgramStage_Geometry;
  case GL_TESS_CONTROL_SHADER:    return ProgramStage_TessControl;
  case GL_TESS_EVALUATION_SHADER: return ProgramStage_TessEval;
  case GL_COMPUTE_SHADER:         return ProgramStage_Compute;
  }
  return ProgramStage_Unknown;
}

DepthFormat GLUtil::GetDepthFormat(flIN uint32_t depthFormat)
{
  switch (depthFormat)
  {
  case GL_DEPTH_COMPONENT:       return DepthFormat_Float32;
  case GL_DEPTH_STENCIL:         return DepthFormat_Float24Stencil8;
  case GL_DEPTH_COMPONENT16:     return DepthFormat_Float16;
  case GL_DEPTH_COMPONENT32:     return DepthFormat_Float32;
  case GL_DEPTH24_STENCIL8:      return DepthFormat_Float24Stencil8;
  case GL_DEPTH32F_STENCIL8_NV:  return DepthFormat_Float32Stencil8;
  }
  return DepthFormat_Unknown;
}

PixelFormat GLUtil::GetPixelFormat(flIN uint32_t format)
{
  switch (format)
  {
  case GL_R8:           // Fall-through
  case GL_R8I:          // Fall-through
  case GL_R8UI:         // Fall-through
  case GL_R8_SNORM:     // Fall-through
  case GL_R16:          // Fall-through
  case GL_R16F:         // Fall-through
  case GL_R16I:         // Fall-through
  case GL_R16UI:        // Fall-through
  case GL_R16_SNORM:    // Fall-through
  case GL_R32I:         // Fall-through
  case GL_R32UI:        // Fall-through
  case GL_R32F:         // Fall-through
  case GL_RED:          return PixelFormat_Red;

  case GL_RG8:          // Fall-through
  case GL_RG8I:         // Fall-through
  case GL_RG8UI:        // Fall-through
  case GL_RG8_SNORM:    // Fall-through
  case GL_RG16:         // Fall-through
  case GL_RG16F:        // Fall-through
  case GL_RG16I:        // Fall-through
  case GL_RG16UI:       // Fall-through
  case GL_RG16_SNORM:   // Fall-through
  case GL_RG32I:        // Fall-through
  case GL_RG32UI:       // Fall-through
  case GL_RG32F:        // Fall-through
  case GL_RG:           return PixelFormat_RG;

  case GL_RGB8:         // Fall-through
  case GL_RGB8I:        // Fall-through
  case GL_RGB8UI:       // Fall-through
  case GL_RGB8_SNORM:   // Fall-through
  case GL_RGB16:        // Fall-through
  case GL_RGB16F:       // Fall-through
  case GL_RGB16I:       // Fall-through
  case GL_RGB16UI:      // Fall-through
  case GL_RGB16_SNORM:  // Fall-through
  case GL_RGB32I:       // Fall-through
  case GL_RGB32UI:      // Fall-through
  case GL_RGB32F:       // Fall-through
  case GL_RGB:          return PixelFormat_RGB;

  case GL_RGBA8:        // Fall-through
  case GL_RGBA8I:       // Fall-through
  case GL_RGBA8UI:      // Fall-through
  case GL_RGBA8_SNORM:  // Fall-through
  case GL_RGBA16:       // Fall-through
  case GL_RGBA16F:      // Fall-through
  case GL_RGBA16I:      // Fall-through
  case GL_RGBA16UI:     // Fall-through
  case GL_RGBA16_SNORM: // Fall-through
  case GL_RGBA32I:      // Fall-through
  case GL_RGBA32UI:     // Fall-through
  case GL_RGBA32F:      // Fall-through
  case GL_RGBA:         return PixelFormat_RGBA;
  }

  return PixelFormat_Unknown;
}

bool GLUtil::GetPixelFormat(flIN uint32_t format, flOUT PixelFormat *pFormat, flOUT PixelComponentType *pComponentType)
{
  if (pFormat) *pFormat = GetPixelFormat(format);
  if (pComponentType) *pComponentType = GetPixelComponentType(format);
  return (!pFormat || *pFormat != PixelFormat_Unknown) && (!pComponentType || *pComponentType != PixelComponentType_Unknown);
}

PixelComponentType GLUtil::GetPixelComponentType(flIN uint32_t format)
{
  switch (format)
  {
  case GL_R8_SNORM:       // Fall-through
  case GL_RG8_SNORM:      // Fall-through
  case GL_RGB8_SNORM:     // Fall-through
  case GL_RGBA8_SNORM:    return PixelComponentType_Norm8;
                          
  case GL_R8I:            // Fall-through
  case GL_RG8I:           // Fall-through
  case GL_RGB8I:          // Fall-through
  case GL_RGBA8I:         // Fall-through
  case GL_BYTE:           return PixelComponentType_Int8;
                          
  case GL_R16_SNORM:      // Fall-through
  case GL_RG16_SNORM:     // Fall-through
  case GL_RGB16_SNORM:    // Fall-through
  case GL_RGBA16_SNORM:   return PixelComponentType_Norm16;
                          
  case GL_R16I:           // Fall-through
  case GL_RG16I:          // Fall-through
  case GL_RGB16I:         // Fall-through
  case GL_RGBA16I:        // Fall-through
  case GL_SHORT:          return PixelComponentType_Int16;
                          
  case GL_R32I:           // Fall-through
  case GL_RG32I:          // Fall-through
  case GL_RGB32I:         // Fall-through
  case GL_RGBA32I:        // Fall-through
  case GL_INT:            return PixelComponentType_Int32;
                          
  case GL_R8:             // Fall-through
  case GL_RG8:            // Fall-through
  case GL_RGB8:           // Fall-through
  case GL_RGBA8:          return PixelComponentType_UNorm8;

  case GL_R8UI:           // Fall-through
  case GL_RG8UI:          // Fall-through
  case GL_RGB8UI:         // Fall-through
  case GL_RGBA8UI:        // Fall-through
  case GL_UNSIGNED_BYTE:  return PixelComponentType_UInt8;

  case GL_R16:            // Fall-through
  case GL_RG16:           // Fall-through
  case GL_RGB16:          // Fall-through
  case GL_RGBA16:         return PixelComponentType_UNorm16;

  case GL_R16UI:          // Fall-through
  case GL_RG16UI:         // Fall-through
  case GL_RGB16UI:        // Fall-through
  case GL_RGBA16UI:       // Fall-through
  case GL_UNSIGNED_SHORT: return PixelComponentType_UInt16;

  case GL_R32UI:          // Fall-through
  case GL_RGB32UI:        // Fall-through
  case GL_RG32UI:         // Fall-through
  case GL_RGBA32UI:       // Fall-through
  case GL_UNSIGNED_INT:   return PixelComponentType_UInt32;

  case GL_R16F:           // Fall-through
  case GL_RG16F:          // Fall-through
  case GL_RGB16F:         // Fall-through
  case GL_RGBA16F:        // Fall-through
  case GL_HALF_FLOAT:     return PixelComponentType_Float16;
                          
  case GL_R32F:           // Fall-through
  case GL_RG32F:          // Fall-through
  case GL_RGB32F:         // Fall-through
  case GL_RGBA32F:        // Fall-through
  case GL_FLOAT:          return PixelComponentType_Float32;
  }

  return PixelComponentType_Unknown;
}

AccessFlags GLUtil::GetAccessFlags(flIN uint32_t accessFlags)
{
}

BufferBinding GLUtil::GetBufferBinding(flIN uint32_t bufferBinding)
{

}

BufferUsage GLUtil::GetBufferUsage(flIN uint32_t bufferBinding)
{

}

Type GLUtil::GetType(flIN uint32_t dataType)
{
  switch (dataType)
  {
  case GL_BYTE:           return Type_Int8;
  case GL_SHORT:          return Type_Int16;
  case GL_INT:            return Type_Int32;
  case GL_UNSIGNED_BYTE:  return Type_UInt8;
  case GL_UNSIGNED_SHORT: return Type_UInt16;
  case GL_UNSIGNED_INT:   return Type_UInt32;
  case GL_FLOAT:          return Type_Float32;
  case GL_DOUBLE:         return Type_Float64;
  }
}

uint32_t GLUtil::ToShaderType(flIN ProgramStage stage)
{

}

uint32_t GLUtil::ToPixelFormat(flIN PixelFormat pixelFormat)
{
  switch (pixelFormat)
  {
  case PixelFormat_Red:  return GL_R;
  case PixelFormat_RG:   return GL_RG;
  case PixelFormat_RGB:  return GL_RGB;
  case PixelFormat_RGBA: return GL_RGBA;
  }
}

uint32_t GLUtil::ToPixelFormat(flIN DepthFormat depthFormat)
{
  switch (depthFormat)
  {
  case DepthFormat_Float16:         return GL_DEPTH_COMPONENT16;
  case DepthFormat_Float24:         return GL_DEPTH_COMPONENT24;
  case DepthFormat_Float24Stencil8: return GL_DEPTH24_STENCIL8;
  case DepthFormat_Float32:         return GL_DEPTH_COMPONENT;
  case DepthFormat_Float32Stencil8: return GL_DEPTH32F_STENCIL8;
  }
}

#define SWITCH_COMPONENT_TYPE(val, comp)\
switch (val)\
{\
case PixelComponentType_UNorm8:  return GL_ ## comp ## 8;\
case PixelComponentType_UNorm16: return GL_ ## comp ## 16;\
case PixelComponentType_Norm8:   return GL_ ## comp ## 8_SNORM;\
case PixelComponentType_Norm16:  return GL_ ## comp ## 16_SNORM;\
case PixelComponentType_Int8:    return GL_ ## comp ## 8I;\
case PixelComponentType_Int16:   return GL_ ## comp ## 16I;\
case PixelComponentType_Int32:   return GL_ ## comp ## 32I;\
case PixelComponentType_UInt8:   return GL_ ## comp ## 8UI;\
case PixelComponentType_UInt16:  return GL_ ## comp ## 16UI;\
case PixelComponentType_UInt32:  return GL_ ## comp ## 32UI;\
case PixelComponentType_Float16: return GL_ ## comp ## 16F;\
case PixelComponentType_Float32: return GL_ ## comp ## 32F;\
}

uint32_t GLUtil::ToPixelFormatSized(flIN PixelFormat pixelFormat, flIN PixelComponentType pixelComponentType)
{
  switch (pixelFormat)
  {
  case PixelFormat_Red:
    SWITCH_COMPONENT_TYPE(pixelComponentType, R)
  case PixelFormat_RG:
    SWITCH_COMPONENT_TYPE(pixelComponentType, RG)
  case PixelFormat_RGB:
    SWITCH_COMPONENT_TYPE(pixelComponentType, RGB)
  case PixelFormat_RGBA:
    SWITCH_COMPONENT_TYPE(pixelComponentType, RGBA)
  }
  return GL_NONE;
}

uint32_t GLUtil::ToPixelDataType(flIN DepthFormat depthFormat)
{
  switch (depthFormat)
  {
  case DepthFormat_Float16:         return GL_HALF_FLOAT;
  case DepthFormat_Float24:         return GL_FLOAT;
  case DepthFormat_Float24Stencil8: return GL_FLOAT;
  case DepthFormat_Float32:         return GL_FLOAT;
  case DepthFormat_Float32Stencil8: return GL_FLOAT;
  }
  return GL_NONE;
}

uint32_t GLUtil::ToPixelDataType(flIN PixelComponentType pixelComponentType)
{
  switch (pixelComponentType)
  {
  case PixelComponentType_Int8:    // Fall-through
  case PixelComponentType_Norm8:   return GL_BYTE;
  case PixelComponentType_Int16:   // Fall-through
  case PixelComponentType_Norm16:  return GL_SHORT;
  case PixelComponentType_UNorm8:  return GL_UNSIGNED_BYTE;
  case PixelComponentType_UNorm16: return GL_UNSIGNED_SHORT;
  case PixelComponentType_Int32:   return GL_INT;
  case PixelComponentType_UInt8:   return GL_UNSIGNED_BYTE;
  case PixelComponentType_UInt16:  return GL_UNSIGNED_SHORT;
  case PixelComponentType_UInt32:  return GL_UNSIGNED_INT;
  case PixelComponentType_Float16: return GL_HALF_FLOAT;
  case PixelComponentType_Float32: return GL_FLOAT;
  }
  return GL_NONE;
}

uint32_t GLUtil::ToAccessFlags(flIN AccessFlags stage)
{

}

uint32_t GLUtil::ToBufferBinding(flIN BufferBinding stage)
{

}

uint32_t GLUtil::ToDataType(flIN Util::Type stage)
{

}

uint32_t GLUtil::ToBufferUsage(flIN BufferUsage stage)
{

}