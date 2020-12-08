#include "graphics/OpenGL/flGLVertexBuffer.h"

namespace flEngine
{
  namespace Graphics
  {
    class Impl_GLVertexBuffer
    {
    public:
    };
  }
}


using namespace flEngine;
using namespace flEngine::Graphics;

flPIMPL_IMPL(GLVertexBuffer);

GLVertexBuffer* GLVertexBuffer::Create()
{
  return flNew GLVertexBuffer;
}

bool GLVertexBuffer::Resize(int64_t size)
{
  return false;
}

bool GLVertexBuffer::Set(void* pData, int64_t size)
{
  return false;
}

bool GLVertexBuffer::Get(void* pBuffer, int64_t length, int64_t offset)
{
  return false;
}

bool GLVertexBuffer::Update()
{
  return false;
}

int64_t GLVertexBuffer::GetSize()
{
  return int64_t();
}

AccessFlags GLVertexBuffer::GetAccessFlags()
{
  return AccessFlags();
}

void* GLVertexBuffer::Map(flIN AccessFlags flags)
{
  return nullptr;
}

bool GLVertexBuffer::Unmap()
{
  return false;
}
