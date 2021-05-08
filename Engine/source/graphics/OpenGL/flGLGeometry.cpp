#include "graphics/flVertexBuffer.h"
#include "graphics/flIndexBuffer.h"
#include "graphics/flHardwareBuffer.h"
#include "flGLGeometry.h"
#include "flGLUtil.h"

namespace flEngine
{
  namespace Graphics
  {
    GLGeometry::GLGeometry()
    {
      glGenVertexArrays(1, &m_vao);
    }

    GLGeometry::~GLGeometry()
    {
      glDeleteVertexArrays(1, &m_vao);
    }

    GLGeometry *GLGeometry::Create()
    {
      return flNew GLGeometry;
    }

    void GLGeometry::AddVertexBuffer(flIN int64_t id, flIN VertexBuffer *pBuffer)
    {
      if (GetVertexBufferByID(id) != nullptr)
        return; // TODO: Report Error

      m_vertexBufferIDs.push_back(id);
      m_vertexBuffers.emplace_back(pBuffer);
      m_rebindVBOs = true;
    }

    void GLGeometry::AddIndexBuffer(flIN IndexBuffer *pBuffer)
    {
      m_indexBuffers.emplace_back(pBuffer);
      m_rebindVBOs = true;
    }

    void GLGeometry::RemoveVertexBuffer(flIN int64_t index)
    {
      if (index < 0 || index >= GetVertexBufferCount())
        return;
      m_vertexBuffers.erase(index);
      m_rebindVBOs = true;
    }

    void GLGeometry::RemoveIndexBuffer(flIN int64_t index)
    {
      if (index < 0 || index >= GetIndexBufferCount())
        return;
      m_indexBuffers.erase(index);
      m_rebindVBOs = true;
    }

    int64_t GLGeometry::GetVertexBufferCount()
    {
      return m_vertexBuffers.size();
    }

    int64_t GLGeometry::GetVertexBufferID(flIN int64_t index)
    {
      return m_vertexBufferIDs[index];
    }

    int64_t GLGeometry::GetIndexBufferCount()
    {
      return m_indexBuffers.size();
    }

    VertexBuffer *GLGeometry::GetVertexBufferByID(flIN int64_t id)
    {
      return GetVertexBuffer(ctIndexOf(m_vertexBufferIDs.begin(), m_vertexBufferIDs.end(), id));
    }

    VertexBuffer *GLGeometry::GetVertexBuffer(flIN int64_t index)
    {
      return index >= 0 && index < GetVertexBufferCount() ? m_vertexBuffers[index].Get() : nullptr;
    }

    IndexBuffer *GLGeometry::GetIndexBuffer(flIN int64_t index)
    {
      return index >= 0 && index < GetIndexBufferCount() ? m_indexBuffers[index].Get() : nullptr;
    }

    void GLGeometry::Bind(flIN int64_t indexBuffer)
    {
      glBindVertexArray(m_vao);

      if (m_rebindVBOs)
      {
        for (int64_t i = 0; i < m_numVBOsBounds; ++i)
          glDisableVertexAttribArray((GLuint)i);

        IndexBuffer *pIndexBuffer = GetIndexBuffer(indexBuffer);

        for (int64_t i = 0; i < GetVertexBufferCount(); ++i)
        {
          VertexBuffer *pVertexBuffer = GetVertexBuffer(i);
          GLenum glDataType = GLUtil::ToDataType(pVertexBuffer->GetPrimitiveType());
          GLsizei width = (GLsizei)pVertexBuffer->GetPrimitiveWidth();

          glEnableVertexAttribArray((GLuint)i);
          glBindBuffer(GL_ARRAY_BUFFER, flNativeToGLID(pVertexBuffer->GetBuffer()->GetNativeResource()));
          glVertexAttribPointer((GLuint)i, width, glDataType, false, 0, nullptr);
        }

        if (pIndexBuffer)
          glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, flNativeToGLID(pIndexBuffer->GetBuffer()->GetNativeResource()));
      }
    }

    void *GLGeometry::GetNativeResource()
    {
      return flNativeFromGLID(m_vao);
    }
  }
}
