#include "flVertexBuffer.h"

namespace Fractal
{
  VertexElement::VertexElement()
    : VertexElement(0, Type_Unknown, 0)
  {}

  VertexElement::VertexElement(uint32_t _location, Type _type, int64_t _width, bool _normalize)
    : location(_location)
    , type(_type)
    , width(_width)
    , normalize(_normalize)
    , offset(0)
  {}

  VertexBuffer::VertexBuffer(API* pAPI)
    : APIResource(pAPI)
  {}
}

