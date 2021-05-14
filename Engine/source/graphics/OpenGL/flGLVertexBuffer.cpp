#include "graphics/OpenGL/flGLVertexBuffer.h"
#include "graphics/flHardwareBuffer.h"
#include "flGLUtil.h"

using namespace flEngine::Util;

namespace flEngine
{
  namespace Graphics
  {

    GLVertexBuffer::GLVertexBuffer(HardwareBuffer * pBuffer, Util::Type primitiveType, int64_t primitiveWidth, int64_t elementCount, void const * pInitialData)
      : m_pBuffer(pBuffer)
    {}

    VertexBuffer* GLVertexBuffer::Create(HardwareBuffer* pBuffer, Util::Type primitiveType /*= Util::Type_Unknown*/, int64_t primitiveWidth /*= 0*/, int64_t elementCount /*= 0*/, void const* pInitialData /*= nullptr*/)
    {
      return flNew GLVertexBuffer(pBuffer, primitiveType, primitiveWidth, elementCount, pInitialData);
    }

    void GLVertexBuffer::Bind()
    {
      uint32_t vao = flNativeToGLID(GetBuffer()->GetNativeResource());
      glBindBuffer(GL_ARRAY_BUFFER, vao);
    }

    void GLVertexBuffer::Unbind()
    {
      glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void GLVertexBuffer::SetLayout(VertexElement const * pElements, int64_t elementCount)
    {
      m_layout.resize(elementCount);
      m_stride = 0;
      for (int64_t i = 0; i < elementCount; ++i)
      {
        m_layout[i].name   = pElements[i].name;
        m_layout[i].type   = pElements[i].type;
        m_layout[i].width  = pElements[i].width;
        m_layout[i].offset = m_stride;
        m_stride += Util::SizeOf(pElements[i].type) * pElements[i].width;
      }
    }

    int64_t GLVertexBuffer::GetVertexCount() const
    {
      return GetBuffer()->GetSize() / GetVertexStride();
    }

    int64_t GLVertexBuffer::GetVertexStride() const
    {
      return m_stride;
    }

    int64_t GLVertexBuffer::GetLayoutElementCount() const
    {
      return m_layout.size();
    }

    void GLVertexBuffer::GetLayoutElement(int64_t index, VertexElement * pElement) const
    {
      Element const& elem = m_layout[index];
      pElement->name = elem.name.c_str();
      pElement->type = elem.type;
      pElement->width = elem.width;
    }

    HardwareBuffer* GLVertexBuffer::GetBuffer()
    {
      return m_pBuffer.Get();
    }

    HardwareBuffer const* GLVertexBuffer::GetBuffer() const
    {
      return m_pBuffer.Get();
    }
  }
}
