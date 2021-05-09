#ifndef fl_Graphics_GLUtil_h__
#define fl_Graphics_GLUtil_h__

#include "flConfig.h"
#include "GL/glew.h"
#include "GL/wglew.h"
#include "GL/GL.h"

#define flNativeToGLID(nativeResource) ((uint32_t)(uint64_t)nativeResource)
#define flNativeFromGLID(nativeResource) ((void*)(uint64_t)nativeResource)

namespace flEngine
{
  namespace Util { enum Type; }

  namespace Graphics
  {
    enum BufferUsage;
    enum BufferBinding;
    enum AccessFlags;
    enum PixelComponentType;
    enum PixelFormat;
    enum DepthFormat;
    enum ProgramStage;
    enum TextureType;

    class GLUtil
    {
    public:
      GLUtil() = delete;

      static PixelComponentType GetPixelComponentType(flIN uint32_t format);
      static bool          GetPixelFormat(flIN uint32_t format, flOUT PixelFormat *pFormat, flOUT PixelComponentType *pComponentType);
      static PixelFormat   GetPixelFormat(flIN uint32_t pixelFormat);
      static DepthFormat   GetDepthFormat(flIN uint32_t format);
      static ProgramStage  GetProgramStage(flIN uint32_t shader);
      static AccessFlags   GetAccessFlags(flIN uint32_t accessFlags);
      static BufferBinding GetBufferBinding(flIN uint32_t bufferBinding);
      static BufferUsage   GetBufferUsage(flIN uint32_t bufferBinding);
      static Util::Type    GetType(flIN uint32_t dataType, flOUT int64_t *pWidth, flOUT int64_t *pHeight);
      static TextureType   GetTextureType(flIN uint32_t glType);

      static bool IsSamplerType(flIN uint32_t glType);
      static bool Is2DSampler(flIN uint32_t glType);
      static bool Is3DSampler(flIN uint32_t glType);
      static bool Is1DSampler(flIN uint32_t glType);

      static uint32_t ToShaderType(flIN ProgramStage stage);
      static uint32_t ToPixelFormat(flIN PixelFormat depthFormat);
      static uint32_t ToPixelFormat(flIN DepthFormat pixelFormat);
      static uint32_t ToPixelFormatSized(flIN PixelFormat pixelFormat, flIN PixelComponentType pixelComponentType);
      static uint32_t ToPixelDataType(flIN DepthFormat depthFormat);
      static uint32_t ToPixelDataType(flIN PixelComponentType pixelComponentType);
      static uint32_t ToAccessFlags(flIN AccessFlags accessFlag);
      static uint32_t ToBufferBinding(flIN BufferBinding binding);
      static uint32_t ToBufferUsage(flIN BufferUsage stage);
      static uint32_t ToDataType(flIN Util::Type dataType, flOUT int64_t width = 1, flOUT int64_t height = 1);
    };
  }
}

#endif // flGLUtil_h__
