#include "graphics/flHardwareBuffer.h"
#include "graphics/flTexture.h"
#include "graphics/flSampler.h"
#include "util/flType.h"
#include "flGLProgram.h"
#include "flGLUtil.h"
#include "flLog.h"

#include "ctFilename.h"
#include "ctFile.h"

namespace flEngine
{
  namespace Graphics
  {
    GLProgram::GLProgram(API *pAPI)
      : Program(pAPI)
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

    GLProgram *GLProgram::Create(API *pAPI)
    {
      return flNew GLProgram(pAPI);
    }

    void GLProgram::Bind()
    {
      glUseProgram(m_programID);
    }

    void GLProgram::Unbind()
    {
      glUseProgram(0);
    }

    void GLProgram::SetShader(const char *source, ProgramStage stage)
    {
      SetShader(stage, source, nullptr);
    }

    void GLProgram::SetShaderFromFile(const char *path, ProgramStage stage)
    {
      SetShader(stage, nullptr, path);
    }

    void GLProgram::SetInt(const char* name, int value)
    {
      glProgramUniform1i(m_programID, GetUniformLocation(name), value);
    }

    void GLProgram::SetFloat(const char* name, float value)
    {
      glProgramUniform1f(m_programID, GetUniformLocation(name), value);
    }

    void GLProgram::SetFloat2(const char* name, float const* pValues)
    {
      glProgramUniform2f(m_programID, GetUniformLocation(name), pValues[0], pValues[1]);
    }

    void GLProgram::SetFloat3(const char* name, float const* pValues)
    {
      glProgramUniform3f(m_programID, GetUniformLocation(name), pValues[0], pValues[1], pValues[2]);
    }

    void GLProgram::SetFloat4(const char* name, float const* pValues)
    {
      glProgramUniform4f(m_programID, GetUniformLocation(name), pValues[0], pValues[1], pValues[2], pValues[3]);
    }

    void GLProgram::SetMat4(const char* name, float const* pValues)
    {
      glProgramUniformMatrix4fv(m_programID, GetUniformLocation(name), 1, GL_TRUE, pValues);
    }

    int GLProgram::GetInt(const char* name)
    {
      int value = 0;
      glGetUniformiv(m_programID, GetUniformLocation(name), &value);
      return value;
    }

    void GLProgram::SetTexture(uint32_t location, Texture *pTexture)
    {
      glActiveTexture(GL_TEXTURE0 + location);
      pTexture->Bind();
    }

    void GLProgram::SetSampler(uint32_t location, Sampler *pSampler)
    {
      pSampler->Bind(location);
    }

    int64_t GLProgram::GetUniformCount() const
    {
      return m_resources[ResourceType_Uniform].size();
    }

    int64_t GLProgram::GetUniformBufferCount() const
    {
      return m_resources[ResourceType_UniformBlock].size();
    }

    int64_t GLProgram::FindAttribute(char const *name) const
    {
      return Find(ResourceType_Attribute, name);
    }

    int64_t GLProgram::FindUniform(char const *name) const
    {
      return Find(ResourceType_Uniform, name);
    }

    int64_t GLProgram::FindUniformBlock(char const *name) const
    {
      return Find(ResourceType_UniformBlock, name);
    }

    int64_t GLProgram::GetAttributeCount() const
    {
      return m_resources[ResourceType_Attribute].size();
    }

    char const * GLProgram::GetUniformName(int64_t index) const
    {
      return m_resources[ResourceType_Uniform][index].name;
    }

    char const* GLProgram::GetUniformBufferName(int64_t index) const
    {
      return m_resources[ResourceType_UniformBlock][index].name;
    }

    bool GLProgram::GetUniformDataType(int64_t index, Util::Type* pType, int64_t* pWidth) const
    {
      Resource const *pResource = GetResource(ResourceType_Uniform, index);
      if (!pResource || m_resources[ResourceType_Uniform][index].isSampler)
        return false;

      if (pType)  *pType = pResource->dataType.primitive;
      if (pWidth) *pWidth = pResource->dataType.width;

      return true;
    }

    bool GLProgram::GetUniformSamplerType(int64_t index, TextureType* pType) const
    {
      Resource const *pResource = GetResource(ResourceType_Uniform, index);
      if (!pResource || !m_resources[ResourceType_Uniform][index].isSampler)
        return false;
      if (pType)
        *pType = pResource->samplerType;
      return true;
    }

    int64_t GLProgram::GetUniformBlockSize(int64_t blockIndex) const
    {
      Resource const *pResource = GetResource(ResourceType_UniformBlock, blockIndex);
      return pResource ? pResource->dataType.width : 0;
    }

    int64_t GLProgram::GetUniformBlockIndex(int64_t index) const
    {
      Resource const *pResource = GetResource(ResourceType_Uniform, index);
      return pResource ? pResource->blockIndex: 0;
    }

    int64_t GLProgram::GetUniformBlockOffset(int64_t index) const
    {
      Resource const *pResource = GetResource(ResourceType_Uniform, index);
      return pResource ? pResource->blockOffset : 0;
    }

    char const* GLProgram::GetAttributeName(int64_t index) const
    {
      Resource const *pResource = GetResource(ResourceType_Attribute, index);
      return pResource ? pResource->name : "";
    }

    void * GLProgram::GetNativeResource()
    {
      return flNativeFromGLID(m_programID);
    }

    GLProgram::Resource * GLProgram::GetResource(ResourceType const & type, int64_t index)
    {
      return index >= 0 && index < m_resources[type].size() ? &m_resources[type][index] : nullptr;
    }

    GLProgram::Resource const * GLProgram::GetResource(ResourceType const &type, int64_t index) const
    {
      return index >= 0 && index < m_resources[type].size() ? &m_resources[type][index] : nullptr;
    }

    GLProgram::Resource * GLProgram::GetResource(ResourceType const & type, char const * name)
    {
      return GetResource(type, Find(type, name));
    }

    GLProgram::Resource const * GLProgram::GetResource(ResourceType const &type, char const * name) const
    {
      return GetResource(type, Find(type, name));
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

    int32_t GLProgram::GetLocation(ResourceType const & type, char const* name) const
    {
      Resource const * pResource = GetResource(type, name);
      return pResource ? pResource->location : -1;
    }

    int32_t GLProgram::GetUniformLocation(char const * name) const
    {
      return GetLocation(ResourceType_Uniform, name);
    }

    int64_t GLProgram::Find(ResourceType const &type, char const * name) const
    {
      ctVector<Resource> const & resList = m_resources[type];
      for (int64_t i = 0; i < resList.size(); ++i)
        if (resList[i].name == name)
          return i;
      return -1;
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
        flError("Failed to link shader: %s", logBuffer.data());

        return false; // TODO: Report GL error
      }

      // Get shader details
      Reflect();

      m_compiled = true;
      return true;
    }

    bool GLProgram::CompileShader(Shader *pShader, ProgramStage programStage)
    {
      if (pShader->isLinked)
        return true;

      if (pShader->file.Path().length() > 0)
      {
        bool success = false;
        pShader->src = ctFile::ReadText(pShader->file, &success);
        if (!success)
        {
          flError("Could not load source file: %s", pShader->file.c_str());
          return false;
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

        flError("Shader Compilation Failed: %s", logBuffer.data());

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
        pAttribResource->glType = glType;

        int64_t w, h;
        pAttribResource->dataType.primitive = GLUtil::GetType(glType, &w, &h);
        pAttribResource->dataType.width     = w * h;
      }

      int32_t textureCount = 0;
      for (int32_t uniform = 0; uniform < uniformCount; ++uniform)
      {
        glGetActiveUniform(m_programID, uniform, maxNameLen, &len, &size, &glType, nameBuffer.data());

        Resource* pUniformResource = AddResource(ResourceType_Uniform, nameBuffer.data());
        pUniformResource->location = glGetUniformLocation(m_programID, nameBuffer.data());
        pUniformResource->glType = glType;

        int64_t width, height;
        Util::Type  type    = GLUtil::GetType(glType, &width, &height);
        TextureType texType = GLUtil::GetTextureType(glType);
        
        if (type != Util::Type_Unknown)
        { // Uniform variable
          pUniformResource->dataType.primitive = type;
          pUniformResource->dataType.width     = width * height;
        }
        else if (texType != TextureType_Unknown)
        { // Texture sampler
          pUniformResource->samplerType = texType;
          pUniformResource->isSampler   = true;
          // Assign a texture unit to this sampler
          glProgramUniform1i(m_programID, pUniformResource->location, textureCount++);
        }
        else
        { // Unrecognized data type
          // TODO: Report this error
        }
      }

      for (int32_t block = 0; block < uniformBlockCount; ++block)
      { // Query available uniform blocks

        int32_t blockSize = 0; int32_t numUniforms = 0; ctVector<int32_t> uniformIndices;
        glGetActiveUniformBlockName(m_programID, (int)block, maxNameLen, &len, nameBuffer.data());
        glGetActiveUniformBlockiv(m_programID, block, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);
        glGetActiveUniformBlockiv(m_programID, block, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &numUniforms);

        Resource *pUniformBlock = AddResource(ResourceType_UniformBlock, nameBuffer.data());
        pUniformBlock->location           = (int32_t)block;
        pUniformBlock->dataType.primitive = Util::Type_UInt8;
        pUniformBlock->dataType.width     = blockSize;

        uniformIndices.resize(numUniforms);
        glGetActiveUniformBlockiv(m_programID, block, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, uniformIndices.data());
        for (int64_t i = 0; i < numUniforms; ++i)
        {
          GLuint uniformIndex = uniformIndices[i];
          GLint blockOffset; GLint blockIndex;
          glGetActiveUniformsiv(m_programID, 1, &uniformIndex, GL_UNIFORM_OFFSET, &blockOffset);
          glGetActiveUniformsiv(m_programID, 1, &uniformIndex, GL_UNIFORM_BLOCK_INDEX, &blockIndex);
          glGetActiveUniform(m_programID, uniformIndex, maxNameLen, &len, &size, &glType, nameBuffer.data());

          Resource *pUniformResource    = GetResource(ResourceType_Uniform, nameBuffer.data());
          pUniformResource->blockOffset = blockOffset;
          pUniformResource->blockIndex  = blockIndex;
          pUniformResource->location    = -1;
        }

        glUniformBlockBinding(m_programID, (uint32_t)block, (uint32_t)block);
      }
    }
  }
}
