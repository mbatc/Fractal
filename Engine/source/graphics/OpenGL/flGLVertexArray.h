#ifndef fl_Graphics_GLGeometry_h__
#define fl_Graphics_GLGeometry_h__

#include "graphics/flVertexArray.h"
#include "ctString.h"
#include "flRef.h"

namespace flEngine
{
  namespace Graphics
  {
    class VertexBuffer;
    class IndexBuffer;

    class GLVertexArray : public VertexArray
    {
      GLVertexArray(API *pAPI);
    public:
      ~GLVertexArray();

      static GLVertexArray* Create(API *pAPI);

      void Bind() override;
      void Unbind() override;

      void AddVertexBuffer(flIN VertexBuffer *pBuffer) override;
      void SetIndexBuffer(flIN IndexBuffer *pBuffer) override;

      void RemoveVertexBuffer(flIN int64_t index) override;
      int64_t GetVertexBufferCount() override;

      VertexBuffer* GetVertexBuffer(flIN int64_t index) override;
      IndexBuffer* GetIndexBuffer() override;

      int64_t GetVertexCount() const override;
      int64_t GetIndexCount() const override;

      void* GetNativeResource() override;

    private:
      uint32_t m_vao = 0;
      int64_t  m_numVBOsBounds = 0;
      int64_t  m_attributeRound = 0;
      bool     m_rebindVBOs = true;

      Ref<IndexBuffer>            m_indexBuffer;
      ctVector<Ref<VertexBuffer>> m_vertexBuffers;
      ctVector<uint32_t>          m_boundLocations;
    };
  }
}

#endif // flGeometry_h__
