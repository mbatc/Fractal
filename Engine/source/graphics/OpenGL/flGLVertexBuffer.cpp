#include "graphics/OpenGL/flGLVertexBuffer.h"

using namespace flEngine::Util;

namespace flEngine
{
  namespace Graphics
  {
    class flPIMPL_CLASS(GLVertexBuffer)
    {
    public:
      Type    primitiveType  = Type_Unknown;
      int64_t primitiveWidth = 0;
      int64_t elementSize    = 0;
    };
  }
}

using namespace flEngine;
using namespace flEngine::Graphics;

flPIMPL_IMPL(GLVertexBuffer)

VertexBuffer* GLVertexBuffer::Create(flIN Util::Type primitiveType, flIN int64_t primitiveWidth, void* pInitialData)
{
  return flNew GLVertexBuffer;
}

void GLVertexBuffer::SetFormat(flIN Util::Type primitiveType, flIN int64_t primitiveWidth)
{
  Impl()->elementSize    = Util::SizeOf(primitiveType) * primitiveWidth;
  Impl()->primitiveType  = primitiveType;
  Impl()->primitiveWidth = primitiveWidth;
}

int64_t GLVertexBuffer::GetElementCount()
{
  return Impl()->elementSize == 0 ? GLHardwareBuffer::GetSize() / Impl()->elementSize : 0;
}

Util::Type GLVertexBuffer::GetPrimitiveType()
{
  return Impl()->primitiveType;
}

int64_t GLVertexBuffer::GetPrimitiveWidth()
{
  return Impl()->primitiveWidth;
}
