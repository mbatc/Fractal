#ifndef fl_Graphics_GLHardwareBuffer_h__
#define fl_Graphics_GLHardwareBuffer_h__

#include "graphics/flHardwareBuffer.h"

namespace flEngine
{
  namespace Graphics
  {
    class GLHardwareBuffer : public HardwareBuffer
    {
      GLHardwareBuffer(BufferBinding binding, AccessFlags flags);

    public:
      static GLHardwareBuffer* Create(BufferBinding binding, AccessFlags flags);

      bool Resize(int64_t size, bool discardData) override;
      bool Set(void const * pData, int64_t size) override;
      bool Get(void * pBuffer, int64_t length = -1, int64_t offset = 0) override;
      int64_t GetSize() const override;
      AccessFlags GetAccessFlags() const override;
      BufferBinding GetBinding() const override;
      void* Map(AccessFlags flags, int64_t length = -1, int64_t offset = 0) override;
      bool Unmap() override;
      void* GetNativeResource() const override;

    private:
      int64_t m_size = 0;
      uint32_t m_bufferID = 0;

      uint32_t m_glAccessFlags = 0;
      AccessFlags m_accessFlags = AccessFlag_None;
      BufferBinding m_binding = BufferBinding_Unknown;

      // Description of the mapped client memory
      void* m_pMappedPtr = nullptr;
      int64_t     m_mappedOffset = 0;
      int64_t     m_mappedLength = 0;
      AccessFlags m_mappedFlags = AccessFlag_None;

      // The number of calls to Map() where a valid pointer was returned.
      // Unmap should be called this many times.
      int64_t     m_mappedCount = 0;
    };
  }
}

#endif // fl_Graphics_HardwareBuffer_h__
