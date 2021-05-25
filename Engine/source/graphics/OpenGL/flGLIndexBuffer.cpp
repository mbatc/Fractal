#include "graphics/OpenGL/flGLIndexBuffer.h"
#include "graphics/flHardwareBuffer.h"
#include "graphics/flAPI.h"
#include "flGLUtil.h"

namespace flEngine
{
  namespace Graphics
  {
    GLIndexBuffer::GLIndexBuffer(API *pAPI, int64_t indexCount, uint32_t const* pValues, BufferUsage usage)
      : IndexBuffer(pAPI)
    {
      m_pBuffer = MakeRef(GetAPI()->CreateBuffer(BufferBinding_Indices, usage), false);
      if (indexCount > 0)
        m_pBuffer->Set(pValues, indexCount * GetElementSize());
    }

    IndexBuffer* GLIndexBuffer::Create(API *pAPI, int64_t indexCount, uint32_t const * pData, BufferUsage usage)
    {
      return flNew GLIndexBuffer(pAPI, indexCount, pData, usage);
    }

    void GLIndexBuffer::Bind()
    {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, flNativeToGLID(m_pBuffer->GetNativeResource()));
    }

    void GLIndexBuffer::Unbind()
    {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void GLIndexBuffer::Resize(int64_t indexCount, bool discardData)
    {
      GetBuffer()->Resize(indexCount * GetElementSize(), true);
    }

    void GLIndexBuffer::SetIndices(uint32_t const * pValues, int64_t count, int64_t offset)
    {
      GetBuffer()->Set(pValues, count * GetElementSize());
    }

    int64_t GLIndexBuffer::GetIndexCount() const
    {
      return GetBuffer()->GetSize() / GetElementSize();
    }

    Util::Type GLIndexBuffer::GetIndexType() const
    {
      return Util::Type_UInt32;
    }

    int64_t GLIndexBuffer::GetElementSize() const
    {
      return Util::SizeOf(GetIndexType());
    }

    HardwareBuffer * GLIndexBuffer::GetBuffer()
    {
      return m_pBuffer.Get();
    }

    HardwareBuffer const * GLIndexBuffer::GetBuffer() const
    {
      return m_pBuffer.Get();
    }
  }
}
