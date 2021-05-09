#include "graphics/OpenGL/flGLIndexBuffer.h"
#include "graphics/flHardwareBuffer.h"

namespace flEngine
{
  namespace Graphics
  {
    GLIndexBuffer::GLIndexBuffer(HardwareBuffer* pBuffer, int64_t indexCount, uint32_t const* pValues)
      : m_pBuffer(pBuffer)
    {
      if (indexCount > 0)
        m_pBuffer->Set(pValues, indexCount * GetElementSize());
    }

    IndexBuffer* GLIndexBuffer::Create(HardwareBuffer* pBuffer, int64_t indexCount, uint32_t const * pData)
    {
      return flNew GLIndexBuffer(pBuffer, indexCount, pData);
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
