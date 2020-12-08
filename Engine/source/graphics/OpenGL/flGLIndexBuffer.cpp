#include "graphics/OpenGL/flGLIndexBuffer.h"

namespace flEngine
{
  namespace Graphics
  {
    class Impl_GLIndexBuffer
    {
    public:
    };
  }
}


using namespace flEngine;
using namespace flEngine::Graphics;

flPIMPL_IMPL(GLIndexBuffer);

GLIndexBuffer* GLIndexBuffer::Create()
{
  return nullptr;
}

bool GLIndexBuffer::Resize(int64_t size)
{
  size;
  return false;
}

bool GLIndexBuffer::Set(void *pData, int64_t size)
{
  pData, size;
  return false;
}

bool GLIndexBuffer::Get(void *pBuffer, int64_t length, int64_t offset)
{
  pBuffer, length, offset;
  return false;
}

bool GLIndexBuffer::Update()
{
  return false;
}

int64_t GLIndexBuffer::GetSize()
{
  return int64_t();
}

AccessFlags GLIndexBuffer::GetAccessFlags()
{
  return AccessFlags();
}

void* GLIndexBuffer::Map(flIN AccessFlags flags)
{
  return nullptr;
}

bool GLIndexBuffer::Unmap()
{
  return false;
}
