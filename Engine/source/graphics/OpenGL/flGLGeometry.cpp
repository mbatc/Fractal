#include "graphics/OpenGL/flGLGeometry.h"

namespace flEngine
{
  namespace Graphics
  {
    class Impl_GLGeometry
    {
    };
  }
}

using namespace flEngine;
using namespace flEngine::Graphics;

flPIMPL_IMPL(GLGeometry)

#define flIMPL flPIMPL(GLGeometry)

GLGeometry * GLGeometry::Create()
{
  return nullptr;
}

void GLGeometry::SetLayout()
{
}

void GLGeometry::AddVertexBuffer(VertexBuffer * pBuffer)
{
}

void GLGeometry::AddIndexBuffer(IndexBuffer * pBuffer)
{
}

VertexBuffer * GLGeometry::GetVertexBuffer()
{
  return nullptr;
}

IndexBuffer * GLGeometry::GetIndexBuffer()
{
  return nullptr;
}
