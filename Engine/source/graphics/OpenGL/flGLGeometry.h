#ifndef fl_Graphics_GLGeometry_h__
#define fl_Graphics_GLGeometry_h__

#include "graphics/flGeometry.h"
#include "ctVector.h"
#include "flRef.h"

namespace flEngine
{
  namespace Graphics
  {
    class VertexBuffer;
    class IndexBuffer;

    class GLGeometry : public Geometry
    {
      GLGeometry();
    public:
      ~GLGeometry();

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
      IndexBuffer* GetIndexBuffer(flIN int64_t index) override;

      void Bind(flIN int64_t indexBuffer) override;

      void* GetNativeResource() override;

    private:
      uint32_t m_vao = 0;
      bool m_rebindVBOs = true;
      int64_t m_numVBOsBounds = 0;

      ctVector<int64_t>           m_vertexBufferIDs;
      ctVector<Ref<VertexBuffer>> m_vertexBuffers;
      ctVector<Ref<IndexBuffer>>  m_indexBuffers;
    };
  }
}

#endif // flGeometry_h__
