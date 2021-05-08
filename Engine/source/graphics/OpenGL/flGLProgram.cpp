#include "graphics/flHardwareBuffer.h"
#include "graphics/flTexture.h"
#include "graphics/flSampler.h"
#include "flGLProgram.h"
#include "util/flType.h"
#include "ctFilename.h"
#include "flGLUtil.h"
#include "ctFile.h"

namespace flEngine
{
  namespace Graphics
  {
    class Uniform : public Interface
    {
      Uniform(ctVector<uint8_t> *pCache, ctVector<uint8_t> *pActiveState, Util::Type dataType, int64_t width, int64_t height, int64_t offset = -1)
      {
        // Set the uniform properties
        m_width = width;
        m_height = height;
        m_primCount = width * height;
        m_dataType = dataType;

        // Calculate the size of the uniforms in bytes
        m_size = m_width * m_height * Util::SizeOf(m_dataType);

        // Set the offset
        m_offset = offset;

        // If no offset is specified, append this uniform the back of the uniform data buffer
        if (m_offset == -1)
          m_offset = pCache->size();

        // Ensure there is enough space in the cache for this uniform
        pCache->resize(m_offset + GetSize());
        pActiveState->resize(pCache->size());

        m_pUniformCache = pCache;
        m_pActiveState = pActiveState;
      }

    public:
      static Uniform * Create(ctVector<uint8_t> *pCache, ctVector<uint8_t> *pActiveState, Util::Type dataType, int64_t width, int64_t height, int64_t offset = -1)
      {
        return flNew Uniform(pCache, pActiveState, dataType, width, height, offset);
      }

      int64_t GetSize() const
      {
        return m_size;
      }

      int64_t GetWidth() const
      {
        return m_width;
      }

      int64_t GetHeight() const
      {
        return m_height;
      }

      Util::Type GetType() const
      {
        return m_dataType;
      }

      bool HasChanged() const
      {
        return memcmp(CachePtr(), ActivePtr(), GetSize()) == 0;
      }

      void Set(void const *pValue, Util::Type valueType, int64_t count)
      {
        Util::ConvertPrimitive(CachePtr(), m_dataType, pValue, valueType, min(count, m_primCount));
      }

      void * CachePtr() const
      {
        return m_pUniformCache->data() + m_offset;
      }

      void * ActivePtr() const
      {
        return m_pActiveState->data() + m_offset;
      }

    private:
      Util::Type m_dataType = Util::Type_Unknown;
      int64_t    m_width = 0;
      int64_t    m_height = 0;
      int64_t    m_size = 0;
      int64_t    m_primCount = 0;
      int64_t    m_offset = -1;
      ctVector<uint8_t> *m_pUniformCache = nullptr;
      ctVector<uint8_t> *m_pActiveState  = nullptr;
    };

    GLProgram::GLProgram()
    {
      m_programID = glCreateProgram();
    }

    GLProgram::~GLProgram()
    {
      for (int64_t i = 0; i < ProgramStage_Count; ++i)
        ClearShader(&m_shaders[i]);
      glDeleteProgram(m_programID);
      m_programID = 0;
    }

    GLProgram *GLProgram::Create()
    {
      return flNew GLProgram;
    }

    void GLProgram::ApplyInputs()
    {
      for (Resource &uniform : m_resources[ResourceType_Uniform])
      {

      }
    }

    void GLProgram::SetShader(const char *source, ProgramStage stage)
    {
      SetShader(stage, source, nullptr);
    }

    void GLProgram::SetShaderFromFile(const char *path, ProgramStage stage)
    {
      SetShader(stage, nullptr, path);
    }

    bool GLProgram::Reload()
    {
      for (int64_t stage = 0; stage < ProgramStage_Count; ++stage)
        DeleteShader(&m_shaders[stage]);

      m_compiled = false;

      return Compile();
    }

    bool GLProgram::Compile()
    {
      if (m_compiled)
        return true;

      bool success = true;
      for (int64_t stage = 0; stage < ProgramStage_Count; ++stage)
        if (m_shaders[stage].isActive)
          success &= CompileShader(&m_shaders[stage]);

      if (!success) // Compiling shaders failed
        return false;

      int status = 0;
      glLinkProgram(m_programID);
      glGetProgramiv(m_programID, GL_LINK_STATUS, &status);
      if (status == GL_FALSE)
      {
        int logLen = 0;
        ctVector<char> logBuffer;
        logBuffer.resize(logLen + 1, 0);

        // Get the length of the compilation log
        glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &logLen);

        // Get the compilation log
        glGetProgramInfoLog(m_programID, logLen, &logLen, logBuffer.data());

        // TODO: Report in error compilation log

        return false; // TODO: Report GL error
      }

      // Get shader details
      Reflect();

      m_compiled = true;
      return true;
    }

    void GLProgram::SetUniformBuffer(const char * name, HardwareBuffer *pBuffer)
    {
      Resource *pBlock = GetResource(ResourceType_UniformBlock, name);
      if (pBlock)
        pBlock->pResource = pBuffer;
    }

    void GLProgram::SetUniform(const char * name, void const *pValue, Util::Type valueType, int64_t valueCount)
    {
      Resource *pResource = GetResource(ResourceType_Uniform, name);
      if (pResource)
      {
        Ref<Uniform> pUniform = (Uniform*)pResource->pResource.Get();
        pUniform->Set(pValue, valueType, valueCount);
      }
    }

    void GLProgram::SetSampler(const char * name, Texture *pTexture)
    {
      Resource *pResource = GetResource(ResourceType_Sampler, name);
      if (pResource)
      {
        pResource->isSampler = false;
        pResource->pResource = pTexture;
      }
    }

    void GLProgram::SetSampler(const char * name, Sampler *pSampler)
    {
      Resource *pResource = GetResource(ResourceType_Sampler, name);
      if (pResource)
      {
        pResource->isSampler = true;
        pResource->pResource = pSampler;
      }
    }

    int64_t GLProgram::GetUniformCount() const
    {
      return m_resources[ResourceType_Uniform].size();
    }

    int64_t GLProgram::GetSamplerCount() const
    {
      return m_resources[ResourceType_Sampler].size();
    }

    int64_t GLProgram::GetUniformBlockCount() const
    {
      return m_resources[ResourceType_UniformBlock].size();
    }

    char const * GLProgram::GetUniformName(int64_t index) const
    {
      return m_resources[ResourceType_Uniform][index].name;
    }

    char const * GLProgram::GetUniformBufferName(int64_t index) const
    {
      return m_resources[ResourceType_UniformBlock][index].name;
    }

    char const * GLProgram::GetSamplerName(int64_t index) const
    {
      return m_resources[ResourceType_Sampler][index].name;
    }

    void * GLProgram::GetNativeResource()
    {
      return flNativeFromGLID(m_programID);
    }

    GLProgram::Resource * GLProgram::GetResource(ResourceType const & type, char const * name)
    {
      for (Resource &resource : m_resources[type])
        if (resource.name == name)
          return &resource;
      return nullptr;
    }

    GLProgram::Resource * GLProgram::AddResource(ResourceType const &type, char const * name)
    {
      for (Resource &resource : m_resources[type])
        if (resource.name == name)
          return &resource;

      m_resources[type].emplace_back();
      m_resources[type].back().name = name;
      return &m_resources[type].back();
    }

    void GLProgram::SetResource(ResourceType const & type, char const * name, Ref<Interface> pResource)
    {
      Resource *pData = GetResource(type, name);
      pData->pResource = pResource;
    }

    void GLProgram::DeleteShader(Shader *pShader)
    {
      if (pShader->glID != 0)
      {
        if (pShader->isLinked)
          glDetachShader(m_programID, pShader->glID);
        glDeleteShader(pShader->glID);
      }

      pShader->isLinked = false;
      pShader->glID = 0;
    }

    void GLProgram::ClearShader(Shader * pShader)
    {
      DeleteShader(pShader);
      *pShader = Shader();
    }

    void GLProgram::SetShader(ProgramStage stage, const char *src, const char *file)
    {
      // Delete the old shader
      ClearShader(&m_shaders[stage]);

      // Set the source
      if (file) m_shaders[stage].file = file;
      if (src) m_shaders[stage].src = src;
      m_shaders[stage].isActive = true;
    }

    bool GLProgram::CompileShader(Shader *pShader)
    {
      if (pShader->isLinked)
        return true;

      if (pShader->file.Path().length() > 0)
      {
        bool success = false;
        pShader->src = ctFile::ReadText(pShader->file, &success);
        if (!success)
          return false; // TODO: Report failed to read file
      }

      if (pShader->src.length() == 0)
        return false; // TODO: Report no source available

      const char *src = pShader->src.c_str();
      int length = (int)pShader->src.length();

      // Attach the shader source
      glShaderSource(pShader->glID, 1, &src, &length);

      // Compile the shader
      glCompileShader(pShader->glID);

      // Check if the shader compiled successfully
      int status = 0;
      glGetShaderiv(pShader->glID, GL_COMPILE_STATUS, &status);
      if (status == GL_FALSE)
      { // GL error, report error
        int logLen = 0;
        ctVector<char> logBuffer;
        logBuffer.resize(logLen + 1, 0);

        // Get the length of the compilation log
        glGetShaderiv(pShader->glID, GL_INFO_LOG_LENGTH, &logLen);

        // Get the compilation log
        glGetShaderInfoLog(pShader->glID, logLen, &logLen, logBuffer.data());

        // TODO: Report in error compilation log

        return false; // TODO: Report GL error
      }

      glAttachShader(m_programID, pShader->glID);

      pShader->isLinked = true;

      return true;
    }

    void GLProgram::Reflect()
    {
      int32_t uniformCount = 0;
      int32_t attributeCount = 0;
      int32_t uniformBlockCount = 0;
      glGetProgramiv(m_programID, GL_ACTIVE_UNIFORMS, &uniformCount);
      glGetProgramiv(m_programID, GL_ACTIVE_ATTRIBUTES, &attributeCount);
      glGetProgramiv(m_programID, GL_ACTIVE_UNIFORM_BLOCKS, &uniformBlockCount);

      int32_t maxNameLen = 0;
      ctVector<char> nameBuffer;
      glGetProgramiv(m_programID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxNameLen);
      nameBuffer.resize(ctMax(nameBuffer.size(), maxNameLen + 1));
      glGetProgramiv(m_programID, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxNameLen);
      nameBuffer.resize(ctMax(nameBuffer.size(), maxNameLen + 1));
      glGetProgramiv(m_programID, GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH, &maxNameLen);
      nameBuffer.resize(ctMax(nameBuffer.size(), maxNameLen + 1));
      maxNameLen = (int32_t)nameBuffer.size() - 1;

      int32_t len = 0; int32_t size = 0; uint32_t type = 0;

      for (int32_t attrib = 0; attrib < attributeCount; ++attrib)
      { // Query geometry inputs
        glGetActiveAttrib(m_programID, attrib, maxNameLen, &len, &size, &type, nameBuffer.data());
      }

      for (int32_t uniform = 0; uniform < uniformCount; ++uniform)
      {
        glGetActiveUniform(m_programID, uniform, maxNameLen, &len, &size, &type, nameBuffer.data());

        int64_t width;
        int64_t height;
        Util::Type type = GLUtil::GetType(type, &width, &height);
        if (type != Util::Type_Unknown)
        { // Uniform variable
          Ref<Uniform> pUniform = Uniform::Create(&m_uniformCache, &m_uniformState, type, width, height);
          Resource *pUniformResource = AddResource(ResourceType_Uniform, nameBuffer.data());
          pUniformResource->pResource = pUniform.Get();
          pUniformResource->location = glGetUniformLocation(m_programID, nameBuffer.data());
          pUniform->DecRef();
        }
        else
        { // Possibly a texture/sampler

        }
      }

      for (int32_t block = 0; block < uniformBlockCount; ++block)
      { // Query available uniform blocks
        int32_t blockSize = 0; int32_t numUniforms = 0; ctVector<int32_t> uniformIndices;
        glGetActiveUniformBlockName(m_programID, (int)block, maxNameLen, &len, nameBuffer.data());
        glGetActiveUniformBlockiv(m_programID, block, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);
        glGetActiveUniformBlockiv(m_programID, block, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &blockSize);
        uniformIndices.resize(numUniforms);
        glGetActiveUniformBlockiv(m_programID, block, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, uniformIndices.data());
      }
    }
  }
}
