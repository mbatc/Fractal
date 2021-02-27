#ifndef fl_Graphics_Program_h__
#define fl_Graphics_Program_h__

#include "../flInterface.h"
#include "flProgramDetails.h"

namespace flEngine
{
  namespace Graphics
  {
    class Program : public Interface
    {
    public:
      /**
       * @brief Set a shader stage from source.
       */
      bool SetShader(flIN const char *source, flIN ProgramStage stage);

      /**
       * @brief Set a shader stage from a file.
       */
      bool SetShaderFromFile(flIN const char *path, flIN ProgramStage stage);

      /**
       * @brief Compile and link the shader program.
       */
      bool Compile();

      /**
       * @brief Set uniform data using a Uniform Buffer
       */
      void SetUniformBuffer(flIN const char *name, flIN HardwareBuffer *pBuffer);

      /**
       * @brief Set a texture in the shader
       */
      void SetTexture(flIN const char *name, flIN Texture *pTexture);

      /**
       * @brief Set a texture in the shader
       */
      void SetSampler(flIN const char *name, flIN Texture *pTexture);

      /**
       * @brief Set the geometry to render for this shader
       */
      void SetGeometry(flIN Geometry *pGeometry);
    };
  }
}

#endif // fl_Graphics_Program_h__
