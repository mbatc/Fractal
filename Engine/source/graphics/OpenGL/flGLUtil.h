#ifndef fl_Graphics_GLUtil_h__
#define fl_Graphics_GLUtil_h__

#include "flConfig.h"
#include "GL/glew.h"
#include "GL/wglew.h"
#include "GL/GL.h"

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

    class flEXPORT GLUtil
    {
    public:
      GLUtil() = delete;

      static bool GetPixelFormat(flIN uint32_t format, flOUT PixelFormat *pFormat, flOUT PixelComponentType *pComponentType);
      static PixelFormat  GetPixelFormat(flIN uint32_t pixelFormat);
      static DepthFormat  GetDepthFormat(flIN uint32_t format);
      static PixelComponentType GetPixelComponentType(flIN uint32_t format);
      static ProgramStage GetProgramStage(flIN uint32_t shader);
      static AccessFlags  GetAccessFlags(flIN uint32_t accessFlags);
      static BufferBinding GetBufferBinding(flIN uint32_t bufferBinding);
      static BufferUsage GetBufferUsage(flIN uint32_t bufferBinding);
      static Util::Type GetType(flIN uint32_t dataType);

      static uint32_t ToShaderType(flIN ProgramStage stage);
      static uint32_t ToPixelFormat(flIN PixelFormat depthFormat);
      static uint32_t ToPixelFormat(flIN DepthFormat pixelFormat);
      static uint32_t ToPixelFormatSized(flIN PixelFormat pixelFormat, flIN PixelComponentType pixelComponentType);
      static uint32_t ToPixelDataType(flIN DepthFormat depthFormat);
      static uint32_t ToPixelDataType(flIN PixelComponentType pixelComponentType);
      static uint32_t ToAccessFlags(flIN AccessFlags accessFlag);
      static uint32_t ToBufferBinding(flIN BufferBinding binding);
      static uint32_t ToBufferUsage(flIN BufferUsage stage);
      static uint32_t ToDataType(flIN Util::Type dataType);
    };
  }
}

#endif // flGLUtil_h__
