#pragma once

#include "flType.h"
#include "flMath.h"
#include "flProgramDetails.h"
#include "flAPIResource.h"

namespace Fractal
{
    enum TextureType;
    class Sampler;
    class Texture;
    class VertexArray;
    class HardwareBuffer;

    class flEXPORT Program : public APIResource
    {
    protected:
      Program(API *pAPI);

    public:
      /**
       * @brief Bind the program to the graphics API context.
       */
      virtual void Bind() = 0;

      /**
       * @brief Unbind the program from the graphics API context.
       */
      virtual void Unbind() = 0;

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
       * @brief Set the value of an int input.
       */
      virtual void SetInt(const char * name, flIN int value) = 0;

      /**
       * @brief Set the value of a float input.
       */
      virtual void SetFloat(const char * name, flIN float value) = 0;

      /**
       * @brief Set the value of a 2 component float input.
       */
      virtual void SetFloat2(const char * name, flIN float const * pValues) = 0;

      /**
       * @brief Set the value of a 3 component float input.
       */
      virtual void SetFloat3(const char * name, flIN float const * pValues) = 0;

      /**
       * @brief Set the value of a 4 component float input.
       */
      virtual void SetFloat4(const char * name, flIN float const * pValues) = 0;

      /**
       * @brief Set the value of a 4x4 float matrix input.
       */
      virtual void SetMat4(const char * name, flIN float const * pValues) = 0;

      /**
       * @brief Get the value of an int input in the shader.
       */
      virtual int GetInt(const char * name) = 0;

      /**
       * @brief Bind a texture to a texture unit.
       */
      virtual void SetTexture(uint32_t location, Texture *pTexture) = 0;

      /**
       * @brief Bind a sampler to a texture unit.
       */
      virtual void SetSampler(uint32_t location, Sampler *pSampler) = 0;

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
       * @brief Get the index of a uniform buffer
       */
      virtual int64_t FindAttribute(char const *name) const = 0;

      /**
       * @brief Get the index of a uniform buffer
       */
      virtual int64_t FindUniform(char const *name) const = 0;

      /**
       * @brief Get the index of a uniform buffer
       */
      virtual int64_t FindUniformBlock(char const *name) const = 0;

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
       * @brief Get the data type of a uniform.
       */
      virtual bool GetUniformDataType(flIN int64_t index, flOUT Type *pType, flOUT int64_t *pWidth) const = 0;

      /**
       * @brief Get the sampler type of a uniform.
       */
      virtual bool GetUniformSamplerType(flIN int64_t index, flOUT TextureType* pType) const = 0;

      /**
       * @brief Get the size of a uniform block in bytes
       */
      virtual int64_t GetUniformBlockSize(flIN int64_t blockIndex) const = 0;

      /**
       * @brief Get the index of the uniform block that contains the uniform at 'index'
       */
      virtual int64_t GetUniformBlockIndex(flIN int64_t index) const = 0;

      /**
       * @brief Get a uniforms byte offset into the uniform block in belongs to.
       */
      virtual int64_t GetUniformBlockOffset(flIN int64_t index) const = 0;

      /**
       * @brief Get the native resource for the underlying graphics API.
       */
      virtual void * GetNativeResource() = 0;

      inline void SetFloat2(char const * name, Vec2F const & value) {
        SetFloat2(name, value.begin());
      }

      inline void SetFloat3(char const * name, Vec3F const & value) {
        SetFloat3(name, value.begin());
      }

      inline void SetFloat4(char const * name, Vec4F const & value) {
        SetFloat4(name, value.begin());
      }

      inline void SetMat4(char const * name, Mat4F const & value) {
        SetMat4(name, value.m);
      }
    };
}
