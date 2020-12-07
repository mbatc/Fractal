#ifndef fl_Graphics_Geometry_h__
#define fl_Graphics_Geometry_h__

#include "../flInterface.h"

namespace flEngine
{
  namespace Graphics
  {
    class VertexBuffer;
    class IndexBuffer;

    class flEXPORT Geometry : public Interface
    {
    public:
      virtual void SetLayout() = 0;
      virtual void AddVertexBuffer(VertexBuffer *pBuffer) = 0;
      virtual void AddIndexBuffer(IndexBuffer *pBuffer) = 0;

      virtual VertexBuffer* GetVertexBuffer() = 0;
      virtual IndexBuffer* GetIndexBuffer() = 0;
    };
  }
}

#endif // flGeometry_h__
