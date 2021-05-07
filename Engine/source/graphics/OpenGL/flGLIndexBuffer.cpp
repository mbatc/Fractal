#include "graphics/OpenGL/flGLIndexBuffer.h"

namespace flEngine
{
  namespace Graphics
  {
    class flPIMPL_CLASS(GLIndexBuffer)
    {
    public:

    };
  }
}

using namespace flEngine;
using namespace flEngine::Graphics;

flPIMPL_IMPL(GLIndexBuffer);

IndexBuffer* GLIndexBuffer::Create(flIN int64_t indexCount, void* pData)
{
  return nullptr;
}

void GLIndexBuffer::Resize(flIN int64_t indexCount)
{
  // HardwareBuffer::Resize(indexCount * GetElementSize(), true);
}

void GLIndexBuffer::SetIndices(flIN uint32_t *pValues, flIN int64_t count)
{
  GLHardwareBuffer::Set(pValues, count * GetElementSize());
}

int64_t GLIndexBuffer::GetIndexCount() const
{
  return GLHardwareBuffer::GetSize() / GetElementSize();
}

Util::Type GLIndexBuffer::GetIndexType() const
{
  return Util::Type_UInt32;
}

int64_t GLIndexBuffer::GetElementSize() const
{
  return Util::SizeOf(GetIndexType());
}
