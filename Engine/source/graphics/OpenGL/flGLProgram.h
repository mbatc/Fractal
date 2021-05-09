#ifndef fl_Graphics_GLProgram_h__
#define fl_Graphics_GLProgram_h__

#include "graphics/flProgram.h"
#include "ctFilename.h"
#include "ctHashMap.h"
#include "flRef.h"

namespace flEngine
{
  namespace Graphics
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
        int32_t  location;        // Location in the program
        uint32_t glType;
        Ref<Interface> pResource; // Reference to the resource data
      };

      GLProgram();

    public:
      ~GLProgram();

      static GLProgram* Create();

      void ApplyInputs() override;

      void SetShader(const char *source, ProgramStage stage) override;
      void SetShaderFromFile(const char *path, ProgramStage stage) override;
      bool Compile() override;
      bool Reload() override;
      void SetUniformBuffer(const char *name, HardwareBuffer *pBuffer) override;
      void SetUniform(const char *name, void const * pValue, Util::Type valueType, int64_t valueCount) override;
      void SetTexture(const char *name, Texture *pTexture) override;
      void SetSampler(const char *name, Sampler *pSampler) override;

      int64_t GetUniformCount() const override;
      int64_t GetTextureCount() const override;
      int64_t GetUniformBufferCount() const override;
      int64_t GetAttributeCount() const override;

      char const * GetUniformName(int64_t index) const override;
      char const * GetTextureName(int64_t index) const override;
      char const * GetUniformBufferName(int64_t index) const override;
      char const * GetAttributeName(int64_t index) const override;

      void * GetNativeResource() override;

    private:
      Resource * GetResource(ResourceType const &type, int64_t index);
      Resource * GetResource(ResourceType const &type, char const * name);
      Resource * AddResource(ResourceType const &type, char const * name);
      void SetResource(ResourceType const & type, char const * name, Ref<Interface> pResource);

      void DeleteShader(Shader *pShader);
      void ClearShader(Shader *pShader);
      void SetShader(ProgramStage stage, const char *src, const char *file);
      bool CompileShader(Shader *pShader, ProgramStage programStage);
      void Reflect();

      Shader   m_shaders[ProgramStage_Count];
      uint32_t m_programID = 0;
      bool     m_compiled = false;

      ctVector<uint8_t>  m_uniformCache;
      ctVector<uint8_t>  m_uniformState;
      ctVector<Resource> m_resources[ResourceType_Count];
    };
  }
}

#endif // fl_Graphics_Program_h__
