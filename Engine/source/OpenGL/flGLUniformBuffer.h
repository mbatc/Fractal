#pragma once

#include "flUniformBuffer.h"
#include "flRef.h"

namespace Fractal
{
    class GLUniformBuffer : public UniformBuffer
    {
    public:
      GLUniformBuffer(API *pAPI, int64_t size, void const * pData, BufferUsage bufferUsage);

      static UniformBuffer * Create(API *pAPI, int64_t size, void const * pData, BufferUsage bufferUsage);

      void Bind(flIN int64_t index) override;
      void Unbind() override;

      HardwareBuffer *GetBuffer() override;
      HardwareBuffer const *GetBuffer() const override;

    private:
      int64_t m_boundIndex = 0;
      Ref<HardwareBuffer> m_pBuffer;
    };
}
