#pragma once

#include "flIndexBuffer.h"
#include "flBufferDetails.h"
#include "flRef.h"

namespace Fractal
{
    class HardwareBuffer;

    class GLIndexBuffer : public IndexBuffer
    {
      friend class OpenGL;

      GLIndexBuffer(API *pAPI, int64_t indexCount, uint32_t const* pValues, BufferUsage usage);

    public:
      static IndexBuffer* Create(API *pAPI, int64_t indexCount = 0, uint32_t const* pValues = nullptr, BufferUsage usage = BufferUsage_Default);

      void Bind() override;
      void Unbind() override;

      void Resize(int64_t indexCount, bool discardData) override;
      void SetIndices(uint32_t const * pValues, int64_t count, int64_t offset) override;
      int64_t GetIndexCount() const override;
      Type GetIndexType() const override;
      int64_t GetElementSize() const override;
      HardwareBuffer* GetBuffer() override;
      HardwareBuffer const * GetBuffer() const override;

    private:
      Ref<HardwareBuffer> m_pBuffer;
    };
}
