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

      static IndexBuffer* Create(int64_t indexCount, uint32_t const* pValues = nullptr);

    public:
      void Resize(int64_t indexCount, bool discardData) override;
      void SetIndices(uint32_t const * pValues, int64_t count, int64_t offset) override;
      int64_t GetIndexCount() const override;
      Util::Type GetIndexType() const override;
      int64_t GetElementSize() const override;
      HardwareBuffer* GetBuffer() override;
      HardwareBuffer const * GetBuffer() const override;

    private:
      Ref<HardwareBuffer> m_pBuffer = nullptr;
    };
  }
}

#endif // fl_Graphics_IndexBuffer_h__
