#pragma once

#include "flVertexArray.h"
#include "flRef.h"

#include "ctVector.h"

namespace Fractal
{
  class VertexBuffer;
  class IndexBuffer;

  namespace Impl
  {
    class GLVertexArray : public VertexArray
    {
      FRACTAL_DEFAULT_INTERFACE;

    public:
      GLVertexArray(API* pAPI);
      ~GLVertexArray();

      virtual void Bind() override;
      virtual void Unbind() override;

      virtual void AddVertexBuffer(flIN VertexBuffer* pBuffer) override;
      virtual void SetIndexBuffer(flIN IndexBuffer* pBuffer) override;

      virtual void RemoveVertexBuffer(flIN int64_t index) override;
      virtual int64_t GetVertexBufferCount() override;

      virtual VertexBuffer* GetVertexBuffer(flIN int64_t index) override;
      virtual IndexBuffer* GetIndexBuffer() override;

      virtual int64_t GetVertexCount() const override;
      virtual int64_t GetIndexCount() const override;

      virtual void* GetNativeResource() override;

      virtual API* GetAPI() const override;

    private:
      API* m_pAPI = nullptr;

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
