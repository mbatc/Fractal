#ifndef fl_Graphics_HardwareBuffer_h__
#define fl_Graphics_HardwareBuffer_h__

#include "../flInterface.h"

namespace flEngine
{
  namespace Graphics
  {
    enum AccessFlags
    {
      AF_Read      = 1 << 0,
      AF_Write     = 1 << 1,
      AF_Static    = 1 << 2,
      AF_ReadWrite = (int64_t)AF_Read | AF_Write,
    };

    class HardwareBuffer : public Interface
    {
    public:
      /**
       * @brief Create a hardware buffer.
       */
      HardwareBuffer(AccessFlags flags, int64_t initialSize, void *pInitialData);

      /**
       * @brief Resize the buffer.
       */
      virtual bool Resize(int64_t size) = 0;

      /**
       * @brief Set the buffer the data.
       */
      virtual bool Set(void *pData, int64_t size) = 0;

      /**
       * @brief Read data from the buffer.
       */
      virtual bool Get(void *pBuffer, int64_t length, int64_t offset = 0) = 0;

      /**
       * @brief Apply any changes made to the buffer.
       */
      virtual bool Update() = 0;

      /**
       * @brief Map the buffer to client memory.
       *
       * @return A pointer to the buffer.
       */
      virtual void* Map(flIN AccessFlags flags) = 0;

      /**
       * @brief Unmap the buffer from client memory.
       */
      virtual bool Unmap() = 0;
    };

    flBITWISE_ENUM_OPERATORS(AccessFlags);
  }
}

#endif // fl_Graphics_HardwareBuffer_h__
