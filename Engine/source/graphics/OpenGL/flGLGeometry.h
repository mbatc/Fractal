#ifndef fl_Graphics_GLGeometry_h__
#define fl_Graphics_GLGeometry_h__

#include "graphics/flGeometry.h"
#include "ctString.h"
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

      void AddVertexBuffer(flIN char const *, flIN VertexBuffer *pBuffer) override;
      void AddIndexBuffer(flIN IndexBuffer *pBuffer) override;

      void RemoveVertexBuffer(flIN int64_t index) override;
      void RemoveIndexBuffer(flIN int64_t index) override;

      int64_t GetVertexBufferCount() override;
      char const * GetVertexBufferName(flIN int64_t index) override;
      int64_t GetIndexBufferCount() override;

      VertexBuffer* GetVertexBuffer(flIN char const * name) override;
      VertexBuffer* GetVertexBuffer(flIN int64_t index) override;
      IndexBuffer* GetIndexBuffer(flIN int64_t index) override;

      int64_t GetVertexCount() const override;
      int64_t GetIndexCount(flIN int64_t indexBuffer) const override;

      bool Update() override;

      void* GetNativeResource() override;

    private:
      ctVector<uint32_t> m_vaos = 0;
      bool m_rebindVBOs = true;
      int64_t m_numVBOsBounds = 0;
      int64_t m_attributeRound = 0;

      ctVector<ctString>          m_vertexBufferNames;
      ctVector<Ref<VertexBuffer>> m_vertexBuffers;
      ctVector<Ref<IndexBuffer>>  m_indexBuffers;
    };
  }
}

#endif // flGeometry_h__
