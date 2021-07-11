#pragma once

#include "flProgram.h"
#include "ctFilename.h"
#include "ctHashMap.h"
#include "flRef.h"

namespace Fractal
{
  enum ResourceType
  {
    ResourceType_Unknown = -1,
    ResourceType_Uniform,
    ResourceType_Texture,
    ResourceType_Sampler,
    ResourceType_Attribute,
    ResourceType_UniformBlock,
    ResourceType_Count,
  };

  class GLProgram : public Program
  {
    struct Shader
    {
      ctFilename file = "";
      ctString   src = "";
      uint32_t   glID = 0;

      bool isActive = false;
      bool isLinked = false;
    };

    struct Resource
    {
      ctString name;            // Name of the resource
      int32_t  location = -1;   // Location in the program
      uint32_t glType = 0;      // The OpenGL data type

      int64_t blockOffset = 0;  // Offset into a uniform block
      int64_t blockIndex  = -1; // Uniform block index

      bool isSampler = false;   // Is this resource a sampler

      union
      {
        struct
        {
          Type primitive;
          int64_t    width;
        } dataType;

        TextureType samplerType;
      };
    };

    GLProgram(API* pAPI);

  public:
    ~GLProgram();

    static GLProgram* Create(API* pAPI);

    void Bind() override;
    void Unbind() override;

    void SetShader(const char* source, ProgramStage stage) override;
    void SetShaderFromFile(const char* path, ProgramStage stage) override;
    bool Compile() override;
    bool Reload() override;

    void SetInt(const char* name, int value) override;
    void SetFloat(const char* name, float value) override;
    void SetFloat2(const char* name, float const* pValues) override;
    void SetFloat3(const char* name, float const* pValues) override;
    void SetFloat4(const char* name, float const* pValues) override;
    void SetMat4(const char* name, float const* pValues) override;

    int GetInt(const char* name) override;

    void SetTexture(uint32_t location, Texture* pTexture) override;
    void SetSampler(uint32_t location, Sampler* pSampler) override;

    int64_t GetAttributeCount() const override;
    int64_t GetUniformCount() const override;
    int64_t GetUniformBufferCount() const override;

    int64_t FindAttribute(char const* name) const override;
    int64_t FindUniform(char const* name) const override;
    int64_t FindUniformBlock(char const* name) const override;

    char const* GetAttributeName(int64_t index) const override;
    char const* GetUniformName(int64_t index) const override;
    char const* GetUniformBufferName(int64_t index) const override;

    bool GetUniformDataType(int64_t index, Type* pType, int64_t* pWidth) const override;
    bool GetUniformSamplerType(int64_t index, TextureType* pType) const override;
    int64_t GetUniformBlockSize(int64_t blockIndex) const override;
    int64_t GetUniformBlockIndex(int64_t index) const override;
    int64_t GetUniformBlockOffset(int64_t index) const override;

    void* GetNativeResource() override;

  private:
    int64_t Find(ResourceType const& type, char const* name) const;

    Resource* GetResource(ResourceType const& type, int64_t index);
    Resource const* GetResource(ResourceType const& type, int64_t index) const;

    Resource* GetResource(ResourceType const& type, char const* name);
    Resource const* GetResource(ResourceType const& type, char const* name) const;

    Resource* AddResource(ResourceType const& type, char const* name);

    int32_t GetLocation(ResourceType const& type, char const* name) const;
    int32_t GetUniformLocation(char const* name) const;

    void DeleteShader(Shader* pShader);
    void ClearShader(Shader* pShader);
    void SetShader(ProgramStage stage, const char* src, const char* file);
    bool CompileShader(Shader* pShader, ProgramStage programStage);
    void Reflect();

    uint32_t m_programID = 0;
    Shader   m_shaders[ProgramStage_Count];
    bool     m_compiled = false;
    bool     m_failed = false;
    ctVector<Resource> m_resources[ResourceType_Count];
  };
}
