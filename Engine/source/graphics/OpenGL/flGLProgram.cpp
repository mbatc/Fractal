#include "graphics/OpenGL/flGLProgram.h"
#include "util/flType.h"
#include "ctFilename.h"
#include "flGLUtil.h"
#include "ctFile.h"

using namespace flEngine;

enum ResourceType
{
  ResourceType_Unknown = -1,
  ResourceType_Uniform,
  ResourceType_Texture,
  ResourceType_Attribute,
  ResourceType_UniformBlock,
  ResourceType_Count,
};

class ProgramUniform
{
public:
  ProgramUniform(int64_t uniformIndex);

  void Set(void *pResource);
  bool Bind();
  bool Reflect();
};

class ProgramTexture
{
public:
  ProgramTexture(int64_t texIndex);

  void Set(void *pResource);
  bool Bind();
  bool Reflect();
};

class ProgramUniformBlock
{
public:
  ProgramUniformBlock(int64_t blockIndex);

  void Set(void *pResource);
  bool Bind();
  bool Reflect();
};

class ProgramAttribute
{
public:
  void Set(void *pResource);
  bool Bind();
  bool Reflect();
};

namespace flEngine
{
  namespace Graphics
  {
    class Impl_GLProgram
    {
      struct Shader
      {
        ctFilename file = "";
        ctString   src = "";
        uint32_t   glID = 0;

        bool isActive = false;
        bool isLinked = false;
      };

    public:
      Impl_GLProgram()
      {
        m_programID = glCreateProgram();
      }

      ~Impl_GLProgram()
      {
        for (int64_t i = 0; i < ProgramStage_Count; ++i)
          ClearShader(&m_shaders[i]);
        glDeleteProgram(m_programID);
        m_programID = 0;
      }

      void SetShader(flIN const char *source, flIN ProgramStage stage)
      {
        SetShader(stage, source, nullptr);
      }

      void SetShaderFromFile(flIN const char *path, flIN ProgramStage stage)
      {
        SetShader(stage, nullptr, path);
      }

      bool Reload()
      {
        for (int64_t stage = 0; stage < ProgramStage_Count; ++stage)
          DeleteShader(&m_shaders[stage]);

        m_compiled = false;

        return Compile();
      }

      bool Compile()
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

      void SetUniformBuffer(flIN const char *name, flIN HardwareBuffer *pBuffer)
      {

      }

      void SetTexture(flIN const char *name, flIN Texture *pTexture)
      {

      }

      void SetSampler(flIN const char *name, flIN Sampler *pTexture)
      {

      }

      void SetGeometry(flIN Geometry *pGeometry)
      {

      }

      void *GetNativeResource()
      {
        return (void *)int64_t(m_programID);
      }

    protected:
      void DeleteShader(Shader *pShader)
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

      void ClearShader(Shader *pShader)
      {
        DeleteShader(pShader);
        *pShader = Shader();
      }

      void SetShader(ProgramStage stage, const char *src, const char *file)
      {
        // Delete the old shader
        ClearShader(&m_shaders[stage]);

        // Set the source
        if (file) m_shaders[stage].file = file;
        if (src) m_shaders[stage].src = src;
        m_shaders[stage].isActive = true;
      }

      bool CompileShader(Shader *pShader)
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
        int length = pShader->src.length();

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

      void Reflect()
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
        maxNameLen = nameBuffer.size() - 1;

        int32_t len = 0; int32_t size = 0; uint32_t type = 0;
        for (int64_t attrib = 0; attrib < attributeCount; ++attrib)
        {
          glGetActiveAttrib(m_programID, attrib, maxNameLen, &len, &size, &type, nameBuffer.data());
          GLUtil::GetType(type);
        }

        for (int64_t uniform = 0; uniform < uniformCount; ++uniform)
        {
          glGetActiveUniform(m_programID, uniform, maxNameLen, &len, &size, &type, nameBuffer.data());

        }
;
        for (int64_t block = 0; block < uniformBlockCount; ++block)
        {
          glGetActiveUniformBlockName(m_programID, block, maxNameLen, &len, nameBuffer.data());
          glGetActiveUniformBlockiv(m_programID, block, maxNameLen, &len, );
        }
      }

      Shader   m_shaders[ProgramStage_Count];
      uint32_t m_programID = 0;
      bool     m_compiled  = false;
    };
  }

  ctHashMap<ctString, void*> m_resources[ResourceType_Count];
}

using namespace flEngine::Graphics;

flPIMPL_IMPL(GLProgram);
#define flIMPL flPIMPL(GLProgram)

GLProgram* GLProgram::Create()
{
  return flNew GLProgram;
}

void GLProgram::SetShader(flIN const char *source, flIN ProgramStage stage)
{
  return flIMPL->SetShader(source, stage);
}

void GLProgram::SetShaderFromFile(flIN const char *path, flIN ProgramStage stage)
{
  return flIMPL->SetShaderFromFile(path, stage);
}

bool GLProgram::Compile()
{
  return flIMPL->Compile();
}

bool GLProgram::Reload()
{
  return flIMPL->Reload();
}

void GLProgram::SetUniformBuffer(flIN const char *name, flIN HardwareBuffer *pBuffer)
{
  flIMPL->SetUniformBuffer(name, pBuffer);
}

void GLProgram::SetTexture(flIN const char *name, flIN Texture *pTexture)
{
  flIMPL->SetTexture(name, pTexture);
}

void GLProgram::SetSampler(flIN const char *name, flIN Sampler *pSampler)
{
  flIMPL->SetSampler(name, pSampler);
}

void GLProgram::SetGeometry(flIN Geometry *pGeometry)
{
  flIMPL->SetGeometry(pGeometry);
}

void* GLProgram::GetNativeResource()
{
  return flIMPL->GetNativeResource();
}
