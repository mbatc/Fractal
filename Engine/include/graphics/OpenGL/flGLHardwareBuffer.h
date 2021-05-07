#ifndef fl_Graphics_GLHardwareBuffer_h__
#define fl_Graphics_GLHardwareBuffer_h__

#include "../flHardwareBuffer.h"

namespace flEngine
{
  namespace Graphics
  {
    class flPIMPL_CLASS(GLHardwareBuffer);

    class flEXPORT GLHardwareBuffer : public HardwareBuffer
    {
      flPIMPL_DEF(GLHardwareBuffer);

      GLHardwareBuffer(flIN BufferBinding binding, flIN AccessFlags flags);

    public:
      static GLHardwareBuffer* Create(flIN BufferBinding binding, flIN AccessFlags flags);

      virtual bool Resize(flIN int64_t size, flIN bool discardData) override;
      virtual bool Set(flIN void *pData, flIN int64_t size) override;
      virtual bool Get(flOUT void *pBuffer, flIN int64_t length = -1, flIN int64_t offset = 0) override;
      virtual int64_t GetSize() const override;
      virtual AccessFlags GetAccessFlags() const override;
      virtual BufferBinding GetBinding() const override;
      virtual void* Map(flIN AccessFlags flags, flIN int64_t length = -1, flIN int64_t offset = 0) override;
      virtual bool Unmap() override;
      virtual void* GetNativeResource() const override;
    };
  }
}

#endif // fl_Graphics_HardwareBuffer_h__
