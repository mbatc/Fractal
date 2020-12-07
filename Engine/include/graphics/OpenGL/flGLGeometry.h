#ifndef fl_Graphics_GLGeometry_h__
#define fl_Graphics_GLGeometry_h__

#include "../flGeometry.h"

namespace flEngine
{
  namespace Graphics
  {
    class flPIMPL_CLASS(GLGeometry);

    class flEXPORT GLGeometry : public Geometry
    {
      flPIMPL_DEF(GLGeometry);

    public:
      static GLGeometry* Create();

      void SetLayout() override;
      void AddVertexBuffer(VertexBuffer *pBuffer) override;
      void AddIndexBuffer(IndexBuffer *pBuffer) override;

      VertexBuffer* GetVertexBuffer() override;
      IndexBuffer* GetIndexBuffer() override;
    };
  }
}

#endif // flGeometry_h__
