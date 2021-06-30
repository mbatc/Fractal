#include "graphics/flHardwareBuffer.h"
#include "graphics/flAPI.h"
#include "flGLVertexBuffer.h"
#include "flGLUtil.h"

using namespace flEngine::Util;

namespace flEngine
{
  namespace Graphics
  {
    GLVertexBuffer::GLVertexBuffer(API * pAPI, int64_t size, void const *pInitialData, BufferUsage bufferUsage)
      : VertexBuffer(pAPI)
    {
      m_pBuffer = MakeRef(GetAPI()->CreateBuffer(BufferBinding_Vertices, bufferUsage), false);
      m_pBuffer->Set(pInitialData, size);
    }

    VertexBuffer* GLVertexBuffer::Create(API *pAPI, int64_t size, void const *pInitialData, BufferUsage bufferUsage)
    {
      return flNew GLVertexBuffer(pAPI, size, pInitialData, bufferUsage);
    }

    void GLVertexBuffer::Bind()
    {
      uint32_t vao = flNativeToGLID(GetBuffer()->GetNativeResource());
      flVerifyGL(glBindBuffer, GL_ARRAY_BUFFER, vao);
    }

    void GLVertexBuffer::Unbind()
    {
      flVerifyGL(glBindBuffer, GL_ARRAY_BUFFER, 0);
    }

    void GLVertexBuffer::SetLayout(VertexElement const * pElements, int64_t elementCount)
    {
      m_layout.resize(elementCount);
      m_stride = 0;
      for (int64_t i = 0; i < elementCount; ++i)
      {
        m_layout[i].location  = pElements[i].location;
        m_layout[i].type      = pElements[i].type;
        m_layout[i].width     = pElements[i].width;
        m_layout[i].normalize = pElements[i].normalize;
        m_layout[i].offset    = m_stride;

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
      pElement->location  = elem.location;
      pElement->type      = elem.type;
      pElement->width     = elem.width;
      pElement->offset    = elem.offset;
      pElement->normalize = elem.normalize;
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
