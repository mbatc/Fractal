#include "graphics/flVertexBuffer.h"
#include "graphics/flIndexBuffer.h"
#include "graphics/flHardwareBuffer.h"
#include "flGLGeometry.h"
#include "flGLUtil.h"
#include "flGLAttributeCache.h"
#include "ctLimits.h"

namespace flEngine
{
  namespace Graphics
  {
    GLGeometry::GLGeometry()
    {
      m_vaos.push_back(0);
      glGenVertexArrays(1, &m_vaos.back());
    }

    GLGeometry::~GLGeometry()
    {
      glDeleteVertexArrays((GLsizei)m_vaos.size(), m_vaos.data());
    }

    GLGeometry *GLGeometry::Create()
    {
      return flNew GLGeometry;
    }

    void GLGeometry::AddVertexBuffer(flIN char const* name, flIN VertexBuffer *pBuffer)
    {
      if (GetVertexBuffer(name) != nullptr)
        return; // TODO: Report Error

      m_vertexBufferNames.push_back(name);
      m_vertexBuffers.emplace_back(pBuffer);
      m_rebindVBOs = true;
    }

    void GLGeometry::AddIndexBuffer(flIN IndexBuffer *pBuffer)
    {
      m_indexBuffers.emplace_back(pBuffer);
      m_vaos.resize(m_indexBuffers.size(), 0);
      if (m_vaos.back() == 0)
        glGenVertexArrays(1, &m_vaos.back());
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

    char const * GLGeometry::GetVertexBufferName(flIN int64_t index)
    {
      return m_vertexBufferNames[index].c_str();
    }

    int64_t GLGeometry::GetIndexBufferCount()
    {
      return m_indexBuffers.size();
    }

    VertexBuffer* GLGeometry::GetVertexBuffer(flIN char const* name)
    {
      for (int64_t i = 0; i < m_vertexBufferNames.size(); ++i)
        if (m_vertexBufferNames[i] == name)
          return m_vertexBuffers[i].Get();
      return nullptr;
    }

    VertexBuffer *GLGeometry::GetVertexBuffer(flIN int64_t index)
    {
      return index >= 0 && index < GetVertexBufferCount() ? m_vertexBuffers[index].Get() : nullptr;
    }

    IndexBuffer *GLGeometry::GetIndexBuffer(flIN int64_t index)
    {
      return index >= 0 && index < GetIndexBufferCount() ? m_indexBuffers[index].Get() : nullptr;
    }

    int64_t GLGeometry::GetVertexCount() const
    {
      int64_t numVerts = m_vertexBuffers.size() > 0 ? ctLimitsMax<int64_t>() : 0;
      for (Ref<VertexBuffer> const & vertBuffer : m_vertexBuffers)
        numVerts = ctMin(numVerts, vertBuffer->GetElementCount());
      return numVerts;
    }

    int64_t GLGeometry::GetIndexCount(flIN int64_t indexBuffer) const
    {
      return m_indexBuffers[indexBuffer]->GetIndexCount();
    }

    bool GLGeometry::Update()
    {
      if (m_rebindVBOs || m_attributeRound != GLAttributeCache::GetChangeRound())
      {
        for (int64_t subMesh = 0; subMesh < ctMax(1, GetIndexBufferCount()); ++subMesh)
        {
          glBindVertexArray(m_vaos[subMesh]);
          for (int64_t i = 0; i < m_numVBOsBounds; ++i)
            glDisableVertexAttribArray((GLuint)i);

          IndexBuffer* pIndexBuffer = GetIndexBuffer(subMesh);

          for (int64_t attrib = 0; attrib < GetVertexBufferCount(); ++attrib)
          {
           int32_t location = GLAttributeCache::GetLocation(m_vertexBufferNames[attrib].c_str());
            if (location < 0)
              continue; // Attribute is not used by any shaders

            VertexBuffer* pVertexBuffer = GetVertexBuffer(attrib);

            GLenum glDataType = GLUtil::ToDataType(pVertexBuffer->GetPrimitiveType());
            GLsizei width     = (GLsizei)pVertexBuffer->GetPrimitiveWidth();

            glEnableVertexAttribArray(location);
            glBindBuffer(GL_ARRAY_BUFFER, flNativeToGLID(pVertexBuffer->GetBuffer()->GetNativeResource()));
            glVertexAttribPointer(location, width, glDataType, false, 0, nullptr);
          }

          if (pIndexBuffer)
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, flNativeToGLID(pIndexBuffer->GetBuffer()->GetNativeResource()));
          else
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

          glBindVertexArray(0);
          glBindBuffer(GL_ARRAY_BUFFER, 0);
          glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
        return true; // VAO was rebuilt
      }

      return false; // Nothing changed
    }

    void *GLGeometry::GetNativeResource()
    {
      return (void*)m_vaos.data();
    }
  }
}
