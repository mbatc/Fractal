#ifndef fl_Graphics_GLGeometry_h__
#define fl_Graphics_GLGeometry_h__

#include "graphics/flGeometry.h"

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

      void AddVertexBuffer(flIN int64_t id, flIN VertexBuffer *pBuffer) override;
      void AddIndexBuffer(flIN IndexBuffer *pBuffer) override;

      void RemoveVertexBuffer(flIN int64_t index) override;
      void RemoveIndexBuffer(flIN int64_t index) override;

      int64_t GetVertexBufferCount() override;
      int64_t GetVertexBufferID(flIN int64_t index) override;
      int64_t GetIndexBufferCount() override;

      VertexBuffer* GetVertexBufferByID(flIN int64_t id) override;
      VertexBuffer* GetVertexBuffer(flIN int64_t index) override;
      IndexBuffer*  GetIndexBuffer(flIN int64_t index) override;

      void Bind(flIN int64_t indexBuffer) override;

      void* GetNativeResource() override;
    };
  }
}

#endif // flGeometry_h__
