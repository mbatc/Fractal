#include "graphics/flVertexBuffer.h"

namespace flEngine
{
  namespace Graphics
  {
    VertexElement::VertexElement()
      : VertexElement("", Util::Type_Unknown, 0)
    {}

    VertexElement::VertexElement(char const *_name, Util::Type _type, int64_t _width)
      : name(_name)
      , type(_type)
      , width(_width)
      , offset(0)
    {}

    VertexBuffer::VertexBuffer(API *pAPI)
      : APIResource(pAPI)
    {}
  }
}
