#ifndef fl_Graphics_Program_h__
#define fl_Graphics_Program_h__

#include "../flInterface.h"
#include "flProgramDetails.h"

namespace flEngine
{
  namespace Graphics
  {
    class Sampler;
    class Texture;
    class Geometry;
    class HardwareBuffer;

    class Program : public Interface
    {
    public:
      /**
       * @brief Set a shader stage from source.
       */
      virtual void SetShader(flIN const char *source, flIN ProgramStage stage) = 0;

      /**
       * @brief Set a shader stage from a file.
       */
      virtual void SetShaderFromFile(flIN const char *path, flIN ProgramStage stage) = 0;

      /**
       * @brief Compile and link the shader program.
       */
      virtual bool Compile() = 0;

      /**
       * @brief Reload the shader.
       */
      virtual bool Reload() = 0;

      /**
       * @brief Set uniform data using a Uniform Buffer
       */
      virtual void SetUniformBuffer(flIN const char *name, flIN HardwareBuffer *pBuffer) = 0;

      /**
       * @brief Set a texture in the shader
       */
      virtual void SetTexture(flIN const char *name, flIN Texture *pTexture) = 0;

      /**
       * @brief Set a texture in the shader
       */
      virtual void SetSampler(flIN const char *name, flIN Sampler *pTexture) = 0;

      /**
       * @brief Get the native resource for the underlying graphics API.
       */
      virtual void *GetNativeResource() = 0;
    };
  }
}

#endif // fl_Graphics_Program_h__
