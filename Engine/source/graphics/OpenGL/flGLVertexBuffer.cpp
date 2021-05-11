#include "graphics/OpenGL/flGLVertexBuffer.h"
#include "graphics/flHardwareBuffer.h"

using namespace flEngine::Util;

namespace flEngine
{
  namespace Graphics
  {
    GLVertexBuffer::GLVertexBuffer(HardwareBuffer *pBuffer, Util::Type primitiveType, int64_t primitiveWidth, int64_t elementCount, void const * pInitialData)
      : m_pBuffer(pBuffer)
    {
      SetFormat(primitiveType, primitiveWidth);
      GetBuffer()->Set(pInitialData, elementCount * m_elementSize);
    }

    VertexBuffer* GLVertexBuffer::Create(HardwareBuffer * pBuffer, Util::Type primitiveType, int64_t primitiveWidth, int64_t elementCount, void const * pInitialData)
    {
      return flNew GLVertexBuffer(pBuffer, primitiveType, primitiveWidth, elementCount, pInitialData);
    }

    void GLVertexBuffer::SetFormat(Util::Type primitiveType, int64_t primitiveWidth)
    {
      m_elementSize = Util::SizeOf(primitiveType) * primitiveWidth;
      m_primitiveType = primitiveType;
      m_primitiveWidth = primitiveWidth;
    }

    int64_t GLVertexBuffer::GetElementCount() const
    {
      return m_elementSize == 0 ? GetBuffer()->GetSize() / m_elementSize : 0;
    }

    Util::Type GLVertexBuffer::GetPrimitiveType() const
    {
      return m_primitiveType;
    }

    int64_t GLVertexBuffer::GetPrimitiveWidth() const
    {
      return m_primitiveWidth;
    }

    HardwareBuffer* GLVertexBuffer::GetBuffer()
    {
      return m_pBuffer.Get();
    }

    HardwareBuffer const * GLVertexBuffer::GetBuffer() const
    {
      return m_pBuffer.Get();
    }

  }
}