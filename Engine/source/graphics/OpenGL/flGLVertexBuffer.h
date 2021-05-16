#ifndef fl_Graphics_GLVertexBuffer_h__
#define fl_Graphics_GLVertexBuffer_h__

#include "graphics/flVertexBuffer.h"
#include "ctString.h"
#include "flRef.h"

namespace flEngine
{
  namespace Graphics
  {
    class HardwareBuffer;

    class GLVertexBuffer : public VertexBuffer
    {
      friend class OpenGL;

      GLVertexBuffer(API *pAPI, int64_t size, void const* pInitialData);

      static VertexBuffer* Create(API *pAPI, int64_t size, void const * pInitialData);
    public:
      virtual void Bind() override;
      virtual void Unbind() override;
      virtual void SetLayout(VertexElement const* pElements, int64_t elementCount) override;
      virtual int64_t GetVertexCount() const override;
      virtual int64_t GetVertexStride() const override;
      virtual int64_t GetLayoutElementCount() const override;
      virtual void GetLayoutElement(int64_t index, VertexElement* pElement) const override;

      virtual HardwareBuffer* GetBuffer() override;
      virtual HardwareBuffer const* GetBuffer() const override;

    private:
      struct Element
      {
        ctString name;
        Util::Type type;
        int64_t width = 0;
        int64_t offset = 0;
      };

      ctVector<Element> m_layout;
      int64_t m_stride = 0;

      Ref<HardwareBuffer> m_pBuffer;
    };
  }
}

#endif // fl_Graphics_IndexBuffer_h__
