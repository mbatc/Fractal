#pragma once

#include "flVertexBuffer.h"
#include "ctString.h"
#include "flRef.h"

namespace Fractal
{
  class HardwareBuffer;

  namespace Impl
  {
    class GLVertexBuffer : public VertexBuffer
    {
      friend class OpenGL;

      FRACTAL_DEFAULT_INTERFACE;

    public:
      GLVertexBuffer(API* pAPI, int64_t size, void const* pInitialData, BufferUsage bufferUsage);

      virtual void Bind() override;
      virtual void Unbind() override;
      virtual void SetLayout(VertexElement const* pElements, int64_t elementCount) override;
      virtual int64_t GetVertexCount() const override;
      virtual int64_t GetVertexStride() const override;
      virtual int64_t GetLayoutElementCount() const override;
      virtual void GetLayoutElement(int64_t index, VertexElement* pElement) const override;

      virtual HardwareBuffer* GetBuffer() override;
      virtual HardwareBuffer const* GetBuffer() const override;

      virtual API* GetAPI() const override;

    private:
      struct Element
      {
        uint32_t location = 0;
        Type type;
        int64_t width = 0;
        int64_t offset = 0;
        bool normalize = false;
      };

      ctVector<Element> m_layout;
      int64_t m_stride = 0;

      Ref<HardwareBuffer> m_pBuffer;
    
      API* m_pAPI;
    };
  }
}
