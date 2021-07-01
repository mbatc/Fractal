#include "flAPI.h"
#include "flGLUniformBuffer.h"
#include "flGLUtil.h"

namespace Fractal
{
  GLUniformBuffer::GLUniformBuffer(API* pAPI, int64_t size, void const* pData, BufferUsage bufferUsage)
    : UniformBuffer(pAPI)
  {
    m_pBuffer = MakeRef(GetAPI()->CreateBuffer(BufferBinding_Uniforms, bufferUsage), false);
    m_pBuffer->Set(pData, size);
  }

  UniformBuffer* GLUniformBuffer::Create(API* pAPI, int64_t size, void const* pData, BufferUsage bufferUsage)
  {
    return flNew GLUniformBuffer(pAPI, size, pData, bufferUsage);
  }

  void GLUniformBuffer::Bind(flIN int64_t index)
  {
    flVerifyGL(glBindBufferRange, GL_UNIFORM_BUFFER, (GLuint)index, flNativeToGLID(m_pBuffer->GetNativeResource()), 0, m_pBuffer->GetSize());
    m_boundIndex = index;
  }

  void GLUniformBuffer::Unbind()
  {
    flVerifyGL(glBindBufferRange, GL_UNIFORM_BUFFER, (GLuint)m_boundIndex, 0, 0, 0);
  }

  HardwareBuffer* GLUniformBuffer::GetBuffer()
  {
    return m_pBuffer;
  }

  HardwareBuffer const* GLUniformBuffer::GetBuffer() const
  {
    return m_pBuffer;
  }
}
