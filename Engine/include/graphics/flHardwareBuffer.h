#ifndef fl_Graphics_HardwareBuffer_h__
#define fl_Graphics_HardwareBuffer_h__

#include "../flInterface.h"
#include "flBufferDetails.h"

namespace flEngine
{
  namespace Graphics
  {
    class flEXPORT HardwareBuffer : public Interface
    {
    public:
      /**
       * @brief Resize the buffer.
       */
      virtual bool Resize(flIN int64_t size, flIN bool discardData) = 0;

      /**
       * @brief Set the buffer the data.
       */
      virtual bool Set(flIN void *pData, flIN int64_t size) = 0;

      /**
       * @brief Read data from the buffer.
       */
      virtual bool Get(flOUT void *pBuffer, flIN int64_t length = -1, flIN int64_t offset = 0) = 0;

      /**
       * @brief Get the size of the buffer.
       */
      virtual int64_t GetSize() const = 0;

      /**
       * @brief Get the access flags for this buffer.
       */
      virtual AccessFlags GetAccessFlags() const = 0;

      /**
       * @brief Get the binding for this HardwareBuffer.
       */
      virtual BufferBinding GetBinding() const = 0;

      /**
       * @brief Map the buffer to client memory.
       *
       * @return A pointer to the buffer.
       */
      virtual void* Map(flIN AccessFlags flags, flIN int64_t length = -1, flIN int64_t offset = 0) = 0;

      /**
       * @brief Unmap the buffer from client memory.
       */
      virtual bool Unmap() = 0;

      /**
       * @brief Get the native resource used by the underlying graphics API
       */
      virtual void* GetNativeResource() const = 0;
    };

    flBITWISE_ENUM_OPERATORS(AccessFlags);
  }
}

#endif // fl_Graphics_HardwareBuffer_h__
