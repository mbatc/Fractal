#ifndef fl_Graphics_GLVertexBuffer_h__
#define fl_Graphics_GLVertexBuffer_h__

#include "graphics/flVertexBuffer.h"
#include "flRef.h"

namespace flEngine
{
  namespace Graphics
  {
    class HardwareBuffer;

    class flEXPORT GLVertexBuffer : public VertexBuffer
    {
      friend class OpenGL;

      GLVertexBuffer(HardwareBuffer* pBuffer, Util::Type primitiveType, int64_t primitiveWidth, int64_t elementCount, void const* pInitialData);

      static VertexBuffer* Create(HardwareBuffer *pBuffer, Util::Type primitiveType = Util::Type_Unknown, int64_t primitiveWidth = 0, int64_t elementCount = 0, void const * pInitialData = nullptr);
    public:
      virtual void SetFormat(Util::Type primitiveType, int64_t primitiveWidth) override;
      virtual Util::Type GetPrimitiveType() const override;
      virtual int64_t GetPrimitiveWidth() const override;
      virtual int64_t GetElementCount() const override;
      virtual HardwareBuffer * GetBuffer() override;
      virtual HardwareBuffer const* GetBuffer() const override;

    private:
      Type    m_primitiveType = Type_Unknown;
      int64_t m_primitiveWidth = 0;
      int64_t m_elementSize = 0;
      Ref<HardwareBuffer> m_pBuffer = nullptr;
    };
  }
}

#endif // fl_Graphics_IndexBuffer_h__
