#include "graphics/OpenGL/flGLGeometry.h"
#include "graphics/flVertexBuffer.h"
#include "graphics/flIndexBuffer.h"
#include "ctVector.h"
#include "flGLUtil.h"
#include "flRef.h"

namespace flEngine
{
  namespace Graphics
  {
    class Impl_GLGeometry
    {
    public:
      Impl_GLGeometry()
      {
        glGenVertexArrays(1, &m_vao);
      }

      uint32_t m_vao    = 0;
      bool m_rebindVBOs = true;
      ctVector<int64_t>           m_vertexBufferIDs;
      ctVector<Ref<VertexBuffer>> m_vertexBuffers;
      ctVector<Ref<IndexBuffer>>  m_indexBuffers;
    };
  }
}

using namespace flEngine;
using namespace flEngine::Graphics;

flPIMPL_IMPL(GLGeometry)

GLGeometry* GLGeometry::Create() { return flNew GLGeometry; }

void GLGeometry::AddVertexBuffer(flIN int64_t id, flIN VertexBuffer *pBuffer)
{
  if (GetVertexBufferByID(id) != nullptr)
    return; // TODO: Report Error

  Impl()->m_vertexBufferIDs.push_back(id);
  Impl()->m_vertexBuffers.emplace_back(pBuffer);
  Impl()->m_rebindVBOs = true;
}

void GLGeometry::AddIndexBuffer(flIN IndexBuffer *pBuffer)
{
  Impl()->m_indexBuffers.emplace_back(pBuffer);
  Impl()->m_rebindVBOs = true;
}

void GLGeometry::RemoveVertexBuffer(flIN int64_t index)
{
  if (index < 0 || index >= GetVertexBufferCount())
    return;
  Impl()->m_vertexBuffers.erase(index);
  Impl()->m_rebindVBOs = true;
}

void GLGeometry::RemoveIndexBuffer(flIN int64_t index)
{
  if (index < 0 || index >= GetIndexBufferCount())
    return;
  Impl()->m_indexBuffers.erase(index);
  Impl()->m_rebindVBOs = true;
}

int64_t GLGeometry::GetVertexBufferCount()
{
  return Impl()->m_vertexBuffers.size();
}

int64_t GLGeometry::GetVertexBufferID(flIN int64_t index)
{
  return Impl()->m_vertexBufferIDs[index];
}

int64_t GLGeometry::GetIndexBufferCount()
{
  return Impl()->m_indexBuffers.size();
}

VertexBuffer* GLGeometry::GetVertexBufferByID(flIN int64_t id)
{
  return GetVertexBuffer(ctIndexOf(Impl()->m_vertexBufferIDs.begin(), Impl()->m_vertexBufferIDs.end(), id));
}

VertexBuffer* GLGeometry::GetVertexBuffer(flIN int64_t index)
{
  return index >= 0 && index < GetVertexBufferCount() ? Impl()->m_vertexBuffers[index] : nullptr;
}

IndexBuffer* GLGeometry::GetIndexBuffer(flIN int64_t index)
{
  return index >= 0 && index < GetIndexBufferCount() ? Impl()->m_indexBuffers[index] : nullptr;
}

void GLGeometry::Bind(flIN int64_t indexBuffer)
{
  glBindVertexArray(Impl()->m_vao);

  if (Impl()->m_rebindVBOs)
  {
    IndexBuffer *pIndexBuffer = GetIndexBuffer(indexBuffer);

    for (int64_t i = 0; i < GetVertexBufferCount(); ++i)
    {
      VertexBuffer* pVertexBuffer = GetVertexBuffer(i);
      GLenum glDataType = GLUtil::ToDataType(pVertexBuffer->GetPrimitiveType());
      GLsizei width = (GLsizei)pVertexBuffer->GetPrimitiveWidth();

      glEnableVertexAttribArray((GLuint)i);
      glBindBuffer(GL_ARRAY_BUFFER, flNativeToGLID(pVertexBuffer->GetNativeResource()));
      glVertexAttribPointer((GLuint)i, width, glDataType, false, 0, nullptr);
    }

    if (pIndexBuffer)
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, flNativeToGLID(pIndexBuffer->GetNativeResource()));
  }
}

void* GLGeometry::GetNativeResource()
{
  return flNativeFromGLID(Impl()->m_vao);
}
