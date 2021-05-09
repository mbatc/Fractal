#include "graphics/flHardwareBuffer.h"
#include "graphics/flTexture.h"
#include "graphics/flSampler.h"
#include "flGLAttributeCache.h"
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
        return memcmp(CachePtr(), ActivePtr(), GetSize()) != 0;
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

      template<typename T> T As()     const { return *AsPtr<T>(); }
      template<typename T> T* AsPtr() const { return (T*)CachePtr(); }

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
      // Update shader uniforms if needed
      for (Resource & uniformResource : m_resources[ResourceType_Uniform])
      {
        Uniform* pUniform = (Uniform*)uniformResource.pResource.Get();
        if (!pUniform->HasChanged())
          continue;

        uint32_t  l  = uniformResource.location;
        float*    f  = pUniform->AsPtr<float>();
        double*   d  = pUniform->AsPtr<double>();
        int32_t*  i  = pUniform->AsPtr<int32_t>();
        uint32_t* ui = pUniform->AsPtr<uint32_t>();

        switch (uniformResource.glType)
        {
        case GL_INT:               glUniform1i(l,  i[0]); break;
        case GL_BOOL:              glUniform1i(l,  i[0]); break;
        case GL_FLOAT:             glUniform1f(l,  f[0]); break;
        case GL_DOUBLE:            glUniform1d(l,  d[0]); break;
        case GL_UNSIGNED_INT:      glUniform1ui(l, ui[0]); break;
        case GL_INT_VEC2:          glUniform2i(l, i[0], i[1]); break;
        case GL_INT_VEC3:          glUniform3i(l, i[0], i[1], i[2]); break;
        case GL_INT_VEC4:          glUniform4i(l, i[0], i[1], i[2], i[3]); break;
        case GL_BOOL_VEC2:         glUniform2i(l, i[0], i[1]); break;
        case GL_BOOL_VEC3:         glUniform3i(l, i[0], i[1], i[2]); break;
        case GL_BOOL_VEC4:         glUniform4i(l, i[0], i[1], i[2], i[3]); break;
        case GL_FLOAT_VEC2:        glUniform2f(l, f[0], f[1]); break;
        case GL_FLOAT_VEC3:        glUniform3f(l, f[0], f[1], f[2]); break;
        case GL_FLOAT_VEC4:        glUniform4f(l, f[0], f[1], f[2], f[3]); break;
        case GL_DOUBLE_VEC2:       glUniform2d(l, d[0], d[1]); break;
        case GL_DOUBLE_VEC3:       glUniform3d(l, d[0], d[1], d[2]); break;
        case GL_DOUBLE_VEC4:       glUniform4d(l, d[0], d[1], d[2], d[3]); break;
        case GL_UNSIGNED_INT_VEC2: glUniform2i(l, ui[0], ui[1]); break;
        case GL_UNSIGNED_INT_VEC3: glUniform3i(l, ui[0], ui[1], ui[2]); break;
        case GL_UNSIGNED_INT_VEC4: glUniform4i(l, ui[0], ui[1], ui[2], ui[3]); break;
        case GL_FLOAT_MAT2:        glUniformMatrix2fv(l, 1, GL_TRUE, f); break;
        case GL_FLOAT_MAT3:        glUniformMatrix3fv(l, 1, GL_TRUE, f); break;
        case GL_FLOAT_MAT4:        glUniformMatrix4fv(l, 1, GL_TRUE, f); break;
        case GL_DOUBLE_MAT2:       glUniformMatrix2dv(l, 1, GL_TRUE, d); break;
        case GL_DOUBLE_MAT3:       glUniformMatrix3dv(l, 1, GL_TRUE, d); break;
        case GL_DOUBLE_MAT4:       glUniformMatrix4dv(l, 1, GL_TRUE, d); break;
        default:
          // Unsupported uniform type
          // TODO: Report Error
          break;
        }
      }

      memcpy(m_uniformState.data(), m_uniformCache.data(), m_uniformCache.size());

      for (Resource & uniformBlock : m_resources[ResourceType_UniformBlock])
      {
        uniformBlock;
        // TODO: Implement uniform block support;
      }

      // Bind textures to texture units
      int64_t textureUnit = 0;
      for (Resource& textureResource : m_resources[ResourceType_Texture])
      {
        Texture* pTexture = (Texture*)textureResource.pResource.Get();
        if (pTexture && pTexture->GetTextureType() == GLUtil::GetTextureType(textureResource.glType))
        {
          uint32_t glID = flNativeToGLID(pTexture->GetNativeResource());

          switch (pTexture->GetTextureType())
          { // A switch is used in anticipation of supporting more texture types
          case TextureType_2D: glBindTexture(GL_TEXTURE_2D, glID); break;
          }
        }

        ++textureUnit;
      }

      // Bind samplers to texture units
      textureUnit = 0;
      for (Resource &samplerResource : m_resources[ResourceType_Sampler])
      {
        glActiveTexture(GLenum(GL_TEXTURE0 + textureUnit));
        Sampler * pSampler = (Sampler*)samplerResource.pResource.Get();
        if (pSampler)
          glBindSampler((GLuint)textureUnit, flNativeToGLID(pSampler->GetNativeResource()));
        else
          glBindSampler((GLuint)textureUnit, 0); // Use the default sampler
        ++textureUnit;
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
          success &= CompileShader(&m_shaders[stage], (ProgramStage)stage);

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

      // Assign texture units
      for (int64_t i = 0; i < GetTextureCount(); ++i)
      {
        Resource *pSamplerResource = GetResource(ResourceType_Sampler, i);
        pSamplerResource->glType;
        glUniform1i(pSamplerResource->location, (GLint)i);
      }

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

    void GLProgram::SetTexture(const char * name, Texture *pTexture)
    {
      Resource *pResource = GetResource(ResourceType_Texture, name);
      if (pResource)
        pResource->pResource = pTexture;
    }

    void GLProgram::SetSampler(const char * name, Sampler *pSampler)
    {
      Resource *pResource = GetResource(ResourceType_Sampler, name);
      if (pResource)
        pResource->pResource = pSampler;
    }

    int64_t GLProgram::GetUniformCount() const
    {
      return m_resources[ResourceType_Uniform].size();
    }

    int64_t GLProgram::GetTextureCount() const
    {
      return m_resources[ResourceType_Sampler].size();
    }

    int64_t GLProgram::GetUniformBufferCount() const
    {
      return m_resources[ResourceType_UniformBlock].size();
    }

    int64_t GLProgram::GetAttributeCount() const
    {
      return m_resources[ResourceType_Attribute].size();
    }

    char const * GLProgram::GetUniformName(int64_t index) const
    {
      return m_resources[ResourceType_Uniform][index].name;
    }

    char const * GLProgram::GetUniformBufferName(int64_t index) const
    {
      return m_resources[ResourceType_UniformBlock][index].name;
    }

    char const* GLProgram::GetAttributeName(int64_t index) const
    {
      return m_resources[ResourceType_Attribute][index].name;
    }

    char const * GLProgram::GetTextureName(int64_t index) const
    {
      return m_resources[ResourceType_Sampler][index].name;
    }

    void * GLProgram::GetNativeResource()
    {
      return flNativeFromGLID(m_programID);
    }

    GLProgram::Resource * GLProgram::GetResource(ResourceType const & type, int64_t index)
    {
      return &m_resources[type][index];
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

    void GLProgram::SetShader(ProgramStage stage, const char * src, const char *file)
    {
      // Delete the old shader
      ClearShader(&m_shaders[stage]);

      // Set the source
      if (src)  m_shaders[stage].src  = src;
      if (file) m_shaders[stage].file = file;
      m_shaders[stage].isActive = true;
    }

    bool GLProgram::CompileShader(Shader *pShader, ProgramStage programStage)
    {
      if (pShader->isLinked)
        return true;

      // Apply cached attribute locations
      for (ctString const& name : GLAttributeCache::GetNames())
        glBindAttribLocation(m_programID, (GLuint)GLAttributeCache::GetLocation(name), name.c_str());

      if (pShader->file.Path().length() > 0)
      {
        bool success = false;
        pShader->src = ctFile::ReadText(pShader->file, &success);
        if (!success)
        {
          printf("Could not load source file: %s", pShader->file.c_str());
          return false; // TODO: Report failed to read file
        }
      }

      if (pShader->src.length() == 0)
        return false; // TODO: Report no source available

      const char *src = pShader->src.c_str();
      int length = (int)pShader->src.length();

      // Create the shader object
      pShader->glID = glCreateShader(GLUtil::ToShaderType(programStage));

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
        printf("Shader Compilation Failed:\n%s", logBuffer.data());

        return false; // TODO: Report GL error
      }

      // Attach the compiled shader to the program
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

      int32_t len = 0; int32_t size = 0; uint32_t glType = 0;

      for (int32_t attrib = 0; attrib < attributeCount; ++attrib)
      { // Query geometry inputs
        glGetActiveAttrib(m_programID, attrib, maxNameLen, &len, &size, &glType, nameBuffer.data());
        Resource* pAttribResource  = AddResource(ResourceType_Attribute, nameBuffer.data());
        pAttribResource->location  = glGetAttribLocation(m_programID, nameBuffer.data());
        pAttribResource->pResource = nullptr; // No resource
        pAttribResource->glType = glType;

        GLAttributeCache::AddLocation(nameBuffer.data(), pAttribResource->location);
      }

      for (int32_t uniform = 0; uniform < uniformCount; ++uniform)
      {
        glGetActiveUniform(m_programID, uniform, maxNameLen, &len, &size, &glType, nameBuffer.data());

        int64_t width;
        int64_t height;
        Util::Type type = GLUtil::GetType(glType, &width, &height);
        if (type != Util::Type_Unknown)
        { // Uniform variable
          Ref<Uniform> pUniform = Uniform::Create(&m_uniformCache, &m_uniformState, type, width, height);
          Resource *pUniformResource  = AddResource(ResourceType_Uniform, nameBuffer.data());

          pUniformResource->pResource = pUniform.Get();
          pUniformResource->location  = glGetUniformLocation(m_programID, nameBuffer.data());
          pUniformResource->glType    = glType;

          pUniform->DecRef();
        }
        else if (GLUtil::GetTextureType(type) != TextureType_Unknown)
        { // Possibly a texture/sampler
          Resource* pSamplerResource = AddResource(ResourceType_Sampler, nameBuffer.data());
          Resource* pTextureResource = AddResource(ResourceType_Texture, nameBuffer.data());
          pSamplerResource->location = pTextureResource->location = glGetUniformLocation(m_programID, nameBuffer.data());
          pSamplerResource->glType   = pTextureResource->glType = type;
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
