#include "flGLUtil.h"
#include "flType.h"
#include "flPixelFormat.h"
#include "flProgramDetails.h"
#include "flBufferDetails.h"
#include "flTexture.h"
#include "flSampler.h"

namespace Fractal
{
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

  bool GLUtil::GetPixelFormat(flIN uint32_t format, flOUT PixelFormat* pFormat, flOUT PixelComponentType* pComponentType)
  {
    if (pFormat)
      *pFormat = GetPixelFormat(format);
    if (pComponentType)
      *pComponentType = GetPixelComponentType(format);
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
    AccessFlags flags = AccessFlag_None;
    if (flHasFlag(accessFlags, GL_MAP_READ_BIT))
      flags = AccessFlags(flags | AccessFlag_Read);
    if (flHasFlag(accessFlags, GL_MAP_WRITE_BIT))
      flags = AccessFlags(flags | AccessFlag_Write);
    return flags;
  }

  BufferBinding GLUtil::GetBufferBinding(flIN uint32_t bufferBinding)
  {
    switch (bufferBinding)
    {
    case GL_ELEMENT_ARRAY_BUFFER: return BufferBinding_Indices;
    case GL_ARRAY_BUFFER:         return BufferBinding_Vertices;
    case GL_UNIFORM_BUFFER:       return BufferBinding_Uniforms;
    }

    return BufferBinding_Unknown;
  }

  BufferUsage GLUtil::GetBufferUsage(flIN uint32_t bufferBinding)
  {
    switch (bufferBinding)
    {
    case GL_STATIC_DRAW:  return BufferUsage_Immutable;
    case GL_DYNAMIC_DRAW: return BufferUsage_Dynamic;
    case GL_STREAM_DRAW:  return BufferUsage_Staging;
    }

    return BufferUsage_Default;
  }

  Type GLUtil::GetType(flIN uint32_t dataType, flOUT int64_t* pWidth, flOUT int64_t* pHeight)
  {
    int64_t width = 1;
    int64_t height = 1;
    Type    type = Type_Unknown;

    switch (dataType)
    {
    case GL_FLOAT_VEC2:    width = 2;             type = Type_Float32; break;
    case GL_FLOAT_VEC3:    width = 3;             type = Type_Float32; break;
    case GL_FLOAT_VEC4:    width = 4;             type = Type_Float32; break;
    case GL_FLOAT_MAT2:    width = 2; height = 2; type = Type_Float32; break;
    case GL_FLOAT_MAT2x3:  width = 2; height = 3; type = Type_Float32; break;
    case GL_FLOAT_MAT2x4:  width = 2; height = 4; type = Type_Float32; break;
    case GL_FLOAT_MAT3x2:  width = 3; height = 2; type = Type_Float32; break;
    case GL_FLOAT_MAT3:    width = 3; height = 3; type = Type_Float32; break;
    case GL_FLOAT_MAT3x4:  width = 3; height = 4; type = Type_Float32; break;
    case GL_FLOAT_MAT4x2:  width = 4; height = 2; type = Type_Float32; break;
    case GL_FLOAT_MAT4x3:  width = 4; height = 3; type = Type_Float32; break;
    case GL_FLOAT_MAT4:    width = 4; height = 4; type = Type_Float32; break;
    case GL_FLOAT:                                type = Type_Float32; break;

    case GL_DOUBLE_VEC2:   width = 2;             type = Type_Float64; break;
    case GL_DOUBLE_VEC3:   width = 3;             type = Type_Float64; break;
    case GL_DOUBLE_VEC4:   width = 4;             type = Type_Float64; break;
    case GL_DOUBLE_MAT2:   width = 2; height = 2; type = Type_Float64; break;
    case GL_DOUBLE_MAT2x3: width = 2; height = 3; type = Type_Float64; break;
    case GL_DOUBLE_MAT2x4: width = 2; height = 4; type = Type_Float64; break;
    case GL_DOUBLE_MAT3x2: width = 3; height = 2; type = Type_Float64; break;
    case GL_DOUBLE_MAT3:   width = 3; height = 3; type = Type_Float64; break;
    case GL_DOUBLE_MAT3x4: width = 3; height = 4; type = Type_Float64; break;
    case GL_DOUBLE_MAT4x2: width = 4; height = 2; type = Type_Float64; break;
    case GL_DOUBLE_MAT4x3: width = 4; height = 3; type = Type_Float64; break;
    case GL_DOUBLE_MAT4:   width = 4; height = 4; type = Type_Float64; break;

    case GL_BYTE:           type = Type_Int8;    break;
    case GL_SHORT:          type = Type_Int16;   break;
    case GL_INT:            type = Type_Int32;   break;
    case GL_UNSIGNED_BYTE:  type = Type_UInt8;   break;
    case GL_UNSIGNED_SHORT: type = Type_UInt16;  break;
    case GL_UNSIGNED_INT:   type = Type_UInt32;  break;
    case GL_DOUBLE:         type = Type_Float64; break;
    }

    if (pWidth)
      *pWidth = width;
    if (pHeight)
      *pHeight = width;

    return type;
  }

  TextureType GLUtil::GetTextureType(flIN uint32_t glType)
  {
    switch (glType)
    {
    case GL_SAMPLER_1D_ARRAY:
    case GL_SAMPLER_1D_ARRAY_SHADOW:
    case GL_SAMPLER_2D_MULTISAMPLE:
    case GL_SAMPLER_2D: return TextureType_2D;
    }

    return TextureType_Unknown;
  }

  WrapMode GLUtil::GetWrapMode(flIN uint32_t wrapMode)
  {
    switch (wrapMode)
    {
    case GL_REPEAT:          return WrapMode_Repeat;
    case GL_CLAMP:           return WrapMode_ClampToEdge;
    case GL_MIRRORED_REPEAT: return WrapMode_Repeat;
    }
    return WrapMode();
  }

  FilterMode GLUtil::GetFilterMode(flIN uint32_t filterMode, bool* pMipMaps)
  {
    bool       mipmaps = false;
    FilterMode mode = FilterMode_Unknown;

    switch (filterMode)
    {
    case GL_LINEAR:                 mode = FilterMode_Linear;  mipmaps = false; break;
    case GL_NEAREST:                mode = FilterMode_Nearest; mipmaps = false; break;
    case GL_NEAREST_MIPMAP_LINEAR:  mode = FilterMode_Linear;  mipmaps = true;  break;
    case GL_NEAREST_MIPMAP_NEAREST: mode = FilterMode_Nearest; mipmaps = true;  break;
    case GL_LINEAR_MIPMAP_LINEAR:   mode = FilterMode_Linear;  mipmaps = true;  break;
    case GL_LINEAR_MIPMAP_NEAREST:  mode = FilterMode_Nearest; mipmaps = true;  break;
    }

    if (pMipMaps)
      *pMipMaps = mipmaps;

    return mode;
  }

  bool GLUtil::IsSamplerType(flIN uint32_t glType)
  {
    return Is1DSampler(glType) || Is2DSampler(glType) || Is3DSampler(glType);
  }

  bool GLUtil::Is1DSampler(flIN uint32_t glType)
  {
    return glType == GL_SAMPLER_1D
           || glType == GL_SAMPLER_1D_SHADOW
           || glType == GL_INT_SAMPLER_1D
           || glType == GL_UNSIGNED_INT_SAMPLER_1D;
  }

  bool GLUtil::Is2DSampler(flIN uint32_t glType)
  {
    return glType == GL_SAMPLER_2D
           || glType == GL_SAMPLER_2D_MULTISAMPLE
           || glType == GL_SAMPLER_2D_SHADOW
           || glType == GL_SAMPLER_1D_ARRAY
           || glType == GL_SAMPLER_1D_ARRAY_SHADOW
           || glType == GL_INT_SAMPLER_2D
           || glType == GL_INT_SAMPLER_1D_ARRAY
           || glType == GL_UNSIGNED_INT_SAMPLER_2D
           || glType == GL_UNSIGNED_INT_SAMPLER_1D_ARRAY;
  }

  bool GLUtil::Is3DSampler(flIN uint32_t glType)
  {
    return glType == GL_SAMPLER_3D
           || glType == GL_INT_SAMPLER_3D
           || glType == GL_UNSIGNED_INT_SAMPLER_3D
           || glType == GL_SAMPLER_2D_ARRAY
           || glType == GL_SAMPLER_2D_MULTISAMPLE_ARRAY
           || glType == GL_INT_SAMPLER_2D_ARRAY
           || glType == GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY
           || glType == GL_UNSIGNED_INT_SAMPLER_2D_ARRAY
           || glType == GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY;
  }

  uint32_t GLUtil::ToShaderType(flIN ProgramStage stage)
  {
    switch (stage)
    {
    case ProgramStage_Compute:     return GL_COMPUTE_SHADER;
    case ProgramStage_Fragment:    return GL_FRAGMENT_SHADER;
    case ProgramStage_Geometry:    return GL_GEOMETRY_SHADER;
    case ProgramStage_Vertex:      return GL_VERTEX_SHADER;
    case ProgramStage_TessControl: return GL_TESS_CONTROL_SHADER;
    case ProgramStage_TessEval:    return GL_TESS_EVALUATION_SHADER;
    }

    return GL_NONE;
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

    return GL_NONE;
  }

  uint32_t GLUtil::ToPixelFormat(flIN DepthFormat depthFormat)
  {
    switch (depthFormat)
    {
    case DepthFormat_Float16:         return GL_DEPTH_COMPONENT16;
    case DepthFormat_Float24:         return GL_DEPTH_COMPONENT24;
    case DepthFormat_Float24Stencil8: return GL_DEPTH_STENCIL;
    case DepthFormat_Float32:         return GL_DEPTH_COMPONENT;
    case DepthFormat_Float32Stencil8: return GL_DEPTH_STENCIL;
    }

    return GL_NONE;
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
    case DepthFormat_Float24Stencil8: return GL_UNSIGNED_INT_24_8;
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
    uint32_t glFlags = 0;
    if (flHasFlag(stage, AccessFlag_Read))
      glFlags &= GL_MAP_READ_BIT;
    if (flHasFlag(stage, AccessFlag_Write))
      glFlags &= GL_MAP_WRITE_BIT;
    return glFlags;
  }

  uint32_t GLUtil::ToBufferBinding(flIN BufferBinding stage)
  {
    switch (stage)
    {
    case BufferBinding_Indices:  return GL_ELEMENT_ARRAY_BUFFER;
    case BufferBinding_Vertices: return GL_ARRAY_BUFFER;
    case BufferBinding_Uniforms: return GL_UNIFORM_BUFFER;
    }

    return GL_NONE;
  }

  uint32_t GLUtil::ToBufferUsage(flIN BufferUsage stage)
  {
    switch (stage)
    {
    case BufferUsage_Default:   // Fall-through
    case BufferUsage_Dynamic:   return GL_DYNAMIC_DRAW;
    case BufferUsage_Staging:   return GL_STREAM_DRAW;
    case BufferUsage_Immutable: return GL_STATIC_DRAW;
    }

    return GL_NONE;
  }

  uint32_t GLUtil::ToDataType(flIN Type dataType, flOUT int64_t width, flOUT int64_t height)
  {
    switch (dataType)
    {
    case Type_Int8:    return width != 1 || height != 1 ? GL_NONE : GL_BYTE;
    case Type_Int16:   return width != 1 || height != 1 ? GL_NONE : GL_SHORT;
    case Type_Int32:   return width != 1 || height != 1 ? GL_NONE : GL_INT;
    case Type_UInt8:   return width != 1 || height != 1 ? GL_NONE : GL_UNSIGNED_BYTE;
    case Type_UInt16:  return width != 1 || height != 1 ? GL_NONE : GL_UNSIGNED_SHORT;
    case Type_UInt32:  return width != 1 || height != 1 ? GL_NONE : GL_UNSIGNED_INT;
    case Type_Bool:    return width != 1 || height != 1 ? GL_NONE : GL_BOOL;
    case Type_Float32:
      switch (width)
      {
      case 1:
        switch (height)
        {
        case 1: return GL_FLOAT;
        case 2: return GL_FLOAT_VEC2;
        case 3: return GL_FLOAT_VEC3;
        case 4: return GL_FLOAT_VEC4;
        }
        break;
      case 2:
        switch (height)
        {
        case 1: return GL_FLOAT_VEC2;
        case 2: return GL_FLOAT_MAT2;
        case 3: return GL_FLOAT_MAT2x3;
        case 4: return GL_FLOAT_MAT2x4;
        }
        break;
      case 3:
        switch (height)
        {
        case 1: return GL_FLOAT_VEC3;
        case 2: return GL_FLOAT_MAT3x2;
        case 3: return GL_FLOAT_MAT3;
        case 4: return GL_FLOAT_MAT3x4;
        }
        break;
      case 4:
        switch (height)
        {
        case 1: return GL_FLOAT_VEC4;
        case 2: return GL_FLOAT_MAT4x2;
        case 3: return GL_FLOAT_MAT4x3;
        case 4: return GL_FLOAT_MAT4;
        }
        break;
      }
      break;
    case Type_Float64:
      switch (width)
      {
      case 1:
        switch (height)
        {
        case 1: return GL_DOUBLE;
        case 2: return GL_DOUBLE_VEC2;
        case 3: return GL_DOUBLE_VEC3;
        case 4: return GL_DOUBLE_VEC4;
        }
        break;
      case 2:
        switch (height)
        {
        case 1: return GL_DOUBLE_VEC2;
        case 2: return GL_DOUBLE_MAT2;
        case 3: return GL_DOUBLE_MAT2x3;
        case 4: return GL_DOUBLE_MAT2x4;
        }
        break;
      case 3:
        switch (height)
        {
        case 1: return GL_DOUBLE_VEC3;
        case 2: return GL_DOUBLE_MAT3x2;
        case 3: return GL_DOUBLE_MAT3;
        case 4: return GL_DOUBLE_MAT3x4;
        }
        break;
      case 4:
        switch (height)
        {
        case 1: return GL_DOUBLE_VEC4;
        case 2: return GL_DOUBLE_MAT4x2;
        case 3: return GL_DOUBLE_MAT4x3;
        case 4: return GL_DOUBLE_MAT4;
        }
        break;
      }
      break;
    }

    return GL_NONE;
  }

  uint32_t GLUtil::ToWrapMode(flIN WrapMode wrapMode)
  {
    switch (wrapMode)
    {
    case WrapMode_Mirror:      return GL_MIRRORED_REPEAT;
    case WrapMode_Repeat:      return GL_REPEAT;
    case WrapMode_ClampToEdge: return GL_CLAMP_TO_EDGE;
    }

    return GL_NONE;
  }

  uint32_t GLUtil::ToFilterMode(flIN FilterMode filterMode, bool mipmaps)
  {
    if (mipmaps)
    {
      switch (filterMode)
      {
      case FilterMode_Linear:  return GL_LINEAR_MIPMAP_LINEAR;
      case FilterMode_Nearest: return GL_LINEAR_MIPMAP_NEAREST;
      }
    }
    else
    {
      switch (filterMode)
      {
      case FilterMode_Linear:  return GL_LINEAR;
      case FilterMode_Nearest: return GL_NEAREST;
      }
    }

    return GL_NONE;
  }
}