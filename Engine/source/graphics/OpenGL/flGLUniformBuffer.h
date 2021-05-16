#ifndef fl_Graphics_GLUniformBuffer_h__
#define fl_Graphics_GLUniformBuffer_h__

#include "graphics/flUniformBuffer.h"
#include "flRef.h"

namespace flEngine
{
  namespace Graphics
  {
    class GLUniformBuffer : public UniformBuffer
    {
    public:
      GLUniformBuffer(API *pAPI, int64_t size, void const * pData);

      static UniformBuffer * Create(API *pAPI, int64_t size, void const * pData);

      void Bind(flIN int64_t index) override;
      void Unbind() override;

      HardwareBuffer *GetBuffer() override;
      HardwareBuffer const *GetBuffer() const override;

    private:
      int64_t m_boundIndex = 0;
      Ref<HardwareBuffer> m_pBuffer;
    };
  }
}


#endif // flGLUniformBuffer_h__
