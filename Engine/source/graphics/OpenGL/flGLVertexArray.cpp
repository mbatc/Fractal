#include "graphics/flVertexBuffer.h"
#include "graphics/flIndexBuffer.h"
#include "graphics/flHardwareBuffer.h"
#include "flGLVertexArray.h"
#include "flGLUtil.h"
#include "flGLAttributeCache.h"
#include "ctLimits.h"

namespace flEngine
{
  namespace Graphics
  {
    GLVertexArray::GLVertexArray()
    {
      glGenVertexArrays(1, &m_vao);
    }

    GLVertexArray::~GLVertexArray()
    {
      glDeleteVertexArrays(1, &m_vao);
    }

    GLVertexArray *GLVertexArray::Create()
    {
      return flNew GLVertexArray;
    }

    void GLVertexArray::Bind()
    {
      glBindVertexArray(m_vao);

      if (m_rebindVBOs)
      {
        for (int64_t i = 0; i < m_numVBOsBounds; ++i)
          glDisableVertexAttribArray((GLuint)i);

        for (int64_t attrib = 0; attrib < GetVertexBufferCount(); ++attrib)
        {
          int32_t location = GLAttributeCache::GetLocation(m_vertexBufferNames[attrib].c_str());
          if (location < 0)
            continue; // Attribute is not used by any shaders

          VertexBuffer* pVertexBuffer = GetVertexBuffer(attrib);

          GLenum glDataType = GLUtil::ToDataType(pVertexBuffer->GetPrimitiveType());
          GLsizei width = (GLsizei)pVertexBuffer->GetPrimitiveWidth();

          glEnableVertexAttribArray(location);
          glBindBuffer(GL_ARRAY_BUFFER, flNativeToGLID(pVertexBuffer->GetBuffer()->GetNativeResource()));
          glVertexAttribPointer(location, width, glDataType, false, 0, nullptr);
        }

        if (m_indexBuffer)
          m_indexBuffer->Bind();
        if (pIndexBuffer)
          glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, flNativeToGLID(pIndexBuffer->GetBuffer()->GetNativeResource()));
        else
          glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
      }
    }

    void GLVertexArray::Unbind()
    {
      glBindVertexArray(0);
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
