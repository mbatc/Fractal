#ifndef fl_Graphics_Program_h__
#define fl_Graphics_Program_h__

#include "../flInterface.h"
#include "../util/flType.h"
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
       * @brief Upload the specified inputs to the GPU
       */
      virtual void ApplyInputs() = 0;

      /**
       * @brief Set the value of a uniform in the shader.
       */
      virtual void SetUniform(const char * name, void const * pValue, Util::Type valueType, int64_t valueCount) = 0;

      /**
       * @brief Set uniform data using a Uniform Buffer.
       */
      virtual void SetUniformBuffer(flIN const char * name, flIN HardwareBuffer * pBuffer) = 0;

      /**
       * @brief Set a texture in the shader
       */
      virtual void SetTexture(flIN const char * name, flIN Texture * pTexture) = 0;

      /**
       * @brief Set a texture in the shader.
       */
      virtual void SetSampler(flIN const char * name, flIN Sampler * pTexture) = 0;

      /**
       * @brief Get the number of vertex attributes in the shader
       */
      virtual int64_t GetAttributeCount() const = 0;

      /**
       * @brief Get the number of active uniforms in the shader.
       */
      virtual int64_t GetUniformCount() const = 0;

      /**
       *@brief Get the number of samplers in the shader.
       */
      virtual int64_t GetUniformBufferCount() const = 0;

      /**
       *@brief Get the number of samplers in the shader.
       * 
       * NOTE: In this case, Sampler is synonymous with Texture
       */
      virtual int64_t GetTextureCount() const = 0;

      /**
       * @brief Get the name of a vertex attribute.
       */
      virtual char const * GetAttributeName(flIN int64_t index) const = 0;

      /**
       * @brief Get the name of a uniform.
       */
      virtual char const * GetUniformName(flIN int64_t index) const = 0;

      /**
       * @brief Get the name of a uniform buffer.
       */
      virtual char const * GetUniformBufferName(flIN int64_t index) const = 0;

      /**
       * @breif Get the name of a sampler in the shader.
       */
      virtual char const * GetTextureName(flIN int64_t index) const = 0;

      /**
       * @brief Get the native resource for the underlying graphics API.
       */
      virtual void * GetNativeResource() = 0;
    };
  }
}

#endif // fl_Graphics_Program_h__
