#include "graphics/flAPI.h"
#include "flGLUniformBuffer.h"
#include "flGLUtil.h"

namespace flEngine
{
  namespace Graphics
  {
    GLUniformBuffer::GLUniformBuffer(API *pAPI, int64_t size, void const * pData)
      : UniformBuffer(pAPI)
    {
      m_pBuffer = MakeRef(GetAPI()->CreateBuffer(BufferBinding_Uniforms, AccessFlag_Write), false);
      m_pBuffer->Set(pData, size);
    }

    UniformBuffer * GLUniformBuffer::Create(API * pAPI, int64_t size, void const * pData)
    {
      return flNew GLUniformBuffer(pAPI, size, pData);
    }

    void GLUniformBuffer::Bind(flIN int64_t index)
    {
      glBindBufferRange(GL_UNIFORM_BUFFER, (GLuint)index, flNativeToGLID(m_pBuffer->GetNativeResource()), 0, m_pBuffer->GetSize());
      m_boundIndex = index;
    }

    void GLUniformBuffer::Unbind()
    {
      glBindBufferRange(GL_UNIFORM_BUFFER, (GLuint)m_boundIndex, 0, 0, 0);
    }

    HardwareBuffer *GLUniformBuffer::GetBuffer()
    {
      return m_pBuffer;
    }

    HardwareBuffer const *GLUniformBuffer::GetBuffer() const
    {
      return m_pBuffer;
    }
  }
}
