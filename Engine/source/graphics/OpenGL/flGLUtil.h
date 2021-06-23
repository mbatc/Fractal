#ifndef fl_Graphics_GLUtil_h__
#define fl_Graphics_GLUtil_h__

#include "flLog.h"
#include <graphics/flSampler.h>

#include "GL/glew.h"
#include "GL/wglew.h"
#include "GL/GL.h"
#include <functional>

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
    enum WrapMode;
    enum FilterMode;

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
      static WrapMode      GetWrapMode(flIN uint32_t wrapMode);
      static FilterMode    GetFilterMode(flIN uint32_t filterMode, bool *pMipMaps = nullptr);

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
      static uint32_t ToWrapMode(flIN WrapMode wrapMode);
      static uint32_t ToFilterMode(flIN FilterMode filterMode, bool mipmaps = false);
    };

    template<typename... Args, size_t... Indices>
    std::string TupleToString(std::tuple<Args...> const &args, std::index_sequence<Indices...>)
    {
      return flEngine::Join(", ", std::get<Indices>(args)...);
    }

    template<typename ReturnT, typename... Args, typename... Args2>
    ReturnT GLAPICall(char const *callingFunc, int line, char const *apiFunc, ReturnT(*func)(Args...), Args2&&... args) {
      class GLLogger
      {
      public:
        GLLogger(std::function<void(GLenum)> onError) : m_onError(onError) {}

        ~GLLogger() {
          GLenum err = glGetError();
          if (err != GL_NO_ERROR)
            m_onError(err);
        }

        std::function<void(GLenum)> m_onError;
        std::tuple<Args...> m_args;
      };

#ifdef _DEBUG
      GLLogger logger([callingFunc, line, apiFunc, args = std::make_tuple(args...)](GLenum err) {
        flEngine::Logging::Log(flEngine::Logging::LogLevel_Error, callingFunc, line, "OpenGL error %d occurred in %s(%s)", err, apiFunc, TupleToString(args, std::make_index_sequence<sizeof...(Args)>{}).c_str());
      });
#else
      GLLogger logger([&](GLenum err) {
        flEngine::Logging::Log(flEngine::Logging::LogLevel_Error, callingFunc, line, "OpenGL error %d occurred in %s(...)", err, apiFunc);
        });
#endif

      return func((Args)std::forward<Args2>(args)...);
    }
  }
}

#define flVerifyGL(func, ...)  flEngine::Graphics::GLAPICall(__FUNCTION__, __LINE__, #func, func, __VA_ARGS__)

#endif // flGLUtil_h__
