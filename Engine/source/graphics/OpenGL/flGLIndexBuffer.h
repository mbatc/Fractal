#ifndef fl_Graphics_GLIndexBuffer_h__
#define fl_Graphics_GLIndexBuffer_h__

#include "graphics/flIndexBuffer.h"
#include "flRef.h"

namespace flEngine
{
  namespace Graphics
  {
    class HardwareBuffer;

    class GLIndexBuffer : public IndexBuffer
    {
      friend class OpenGL;

      GLIndexBuffer(HardwareBuffer* pBuffer, int64_t indexCount, uint32_t const* pValues);

    public:
      static IndexBuffer* Create(HardwareBuffer *pBuffer, int64_t indexCount = 0, uint32_t const* pValues = nullptr);

      void Bind() override;
      void Unbind() override;

      void Resize(int64_t indexCount, bool discardData) override;
      void SetIndices(uint32_t const * pValues, int64_t count, int64_t offset) override;
      int64_t GetIndexCount() const override;
      Util::Type GetIndexType() const override;
      int64_t GetElementSize() const override;
      HardwareBuffer* GetBuffer() override;
      HardwareBuffer const * GetBuffer() const override;

    private:
      Ref<HardwareBuffer> m_pBuffer;
    };
  }
}

#endif // fl_Graphics_IndexBuffer_h__
