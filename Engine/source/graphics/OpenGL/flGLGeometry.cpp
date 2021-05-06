#include "graphics/OpenGL/flGLGeometry.h"
#include "graphics/flVertexBuffer.h"
#include "graphics/flIndexBuffer.h"
#include "ctVector.h"
#include "flRef.h"

namespace flEngine
{
  namespace Graphics
  {
    class Impl_GLGeometry
    {
    public:
      ctVector<int64_t>           m_vertexBufferIDs;
      ctVector<Ref<VertexBuffer>> m_vertexBuffers;
      ctVector<Ref<IndexBuffer>>  m_indexBuffers;
    };
  }
}

using namespace flEngine;
using namespace flEngine::Graphics;

flPIMPL_IMPL(GLGeometry)

#define flIMPL flPIMPL(GLGeometry)

GLGeometry* GLGeometry::Create() { return flNew GLGeometry; }

void GLGeometry::AddVertexBuffer(flIN int64_t id, flIN VertexBuffer *pBuffer)
{
  if (GetVertexBufferByID(id) != nullptr)
    return; // TODO: Report Error

  flIMPL->m_vertexBufferIDs.push_back(id);
  flIMPL->m_vertexBuffers.emplace_back(pBuffer);
}

void GLGeometry::AddIndexBuffer(flIN IndexBuffer *pBuffer)
{
  flIMPL->m_indexBuffers.emplace_back(pBuffer);
}

int64_t GLGeometry::GetVertexBufferCount()
{
  return flIMPL->m_vertexBuffers.size();
}

int64_t GLGeometry::GetVertexBufferID(flIN int64_t index)
{
  return flIMPL->m_vertexBufferIDs[index];
}

int64_t GLGeometry::GetIndexBufferCount()
{
  return flIMPL->m_indexBuffers.size();
}

VertexBuffer* GLGeometry::GetVertexBufferByID(flIN int64_t id)
{
  return GetVertexBuffer(ctIndexOf(flIMPL->m_vertexBufferIDs.begin(), flIMPL->m_vertexBufferIDs.end(), id));
}

VertexBuffer* GLGeometry::GetVertexBuffer(flIN int64_t index)
{
  return flIMPL->m_vertexBuffers[index];
}

IndexBuffer* GLGeometry::GetIndexBuffer(flIN int64_t index)
{
  return flIMPL->m_indexBuffers[index];
}
