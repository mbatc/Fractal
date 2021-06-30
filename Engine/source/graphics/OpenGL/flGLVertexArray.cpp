#include "graphics/flVertexBuffer.h"
#include "graphics/flIndexBuffer.h"
#include "graphics/flHardwareBuffer.h"
#include "flGLVertexArray.h"
#include "flGLUtil.h"
#include "ctLimits.h"

namespace flEngine
{
  namespace Graphics
  {
    GLVertexArray::GLVertexArray(API * pAPI)
      : VertexArray(pAPI)
    {
      flVerifyGL(glGenVertexArrays, 1, &m_vao);
    }

    GLVertexArray::~GLVertexArray()
    {
      flVerifyGL(glDeleteVertexArrays, 1, &m_vao);
    }

    GLVertexArray *GLVertexArray::Create(API *pAPI)
    {
      return flNew GLVertexArray(pAPI);
    }

    void GLVertexArray::Bind()
    {
      flVerifyGL(glBindVertexArray, m_vao);

      if (m_rebindVBOs)
      {
        for (uint32_t &loc : m_boundLocations)
          flVerifyGL(glDisableVertexAttribArray, (GLuint)loc);
        m_boundLocations.clear();

        for (int64_t bufferIndex = 0; bufferIndex < GetVertexBufferCount(); ++bufferIndex)
        {
          VertexElement element;
          VertexBuffer* pVertexBuffer = GetVertexBuffer(bufferIndex);
          for (int64_t i = 0; i < pVertexBuffer->GetLayoutElementCount(); ++i)
          {
            pVertexBuffer->GetLayoutElement(i, &element);

            GLenum glDataType = GLUtil::ToDataType(element.type);
            GLsizei width = (GLsizei)element.width;

            flVerifyGL(glEnableVertexAttribArray, element.location);
            pVertexBuffer->Bind();
            flVerifyGL(glVertexAttribPointer, element.location, width, glDataType, element.normalize, (GLsizei)pVertexBuffer->GetVertexStride(), (void const *)element.offset);
            m_boundLocations.push_back(element.location);
          }
        }

        if (m_indexBuffer)
          m_indexBuffer->Bind();
        else
          flVerifyGL(glBindBuffer, GL_ELEMENT_ARRAY_BUFFER, 0);

        m_rebindVBOs = false;
      }
    }

    void GLVertexArray::Unbind()
    {
      flVerifyGL(glBindVertexArray, 0);
    }

    void GLVertexArray::AddVertexBuffer(flIN VertexBuffer* pBuffer)
    {
      m_vertexBuffers.emplace_back(pBuffer, true);
      m_rebindVBOs = true;
    }

    void GLVertexArray::SetIndexBuffer(flIN IndexBuffer *pBuffer)
    {
      pBuffer->IncRef();
      m_indexBuffer = MakeRef(pBuffer, true);
      m_rebindVBOs = true;
    }

    void GLVertexArray::RemoveVertexBuffer(flIN int64_t index)
    {
      if (index < 0 || index >= GetVertexBufferCount())
        return;
      m_vertexBuffers.erase(index);
      m_rebindVBOs = true;
    }

    int64_t GLVertexArray::GetVertexBufferCount()
    {
      return m_vertexBuffers.size();
    }

    VertexBuffer *GLVertexArray::GetVertexBuffer(flIN int64_t index)
    {
      return index >= 0 && index < GetVertexBufferCount() ? m_vertexBuffers[index].Get() : nullptr;
    }

    IndexBuffer *GLVertexArray::GetIndexBuffer()
    {
      return m_indexBuffer.Get();
    }

    int64_t GLVertexArray::GetVertexCount() const
    {
      int64_t numVerts = m_vertexBuffers.size() > 0 ? ctLimitsMax<int64_t>() : 0;
      for (Ref<VertexBuffer> const & vertBuffer : m_vertexBuffers)
        numVerts = ctMin(numVerts, vertBuffer->GetVertexCount());
      return numVerts;
    }

    int64_t GLVertexArray::GetIndexCount() const
    {
      return m_indexBuffer ? m_indexBuffer->GetIndexCount() : 0;
    }

    void *GLVertexArray::GetNativeResource()
    {
      return flNativeFromGLID(m_vao);
    }
  }
}
