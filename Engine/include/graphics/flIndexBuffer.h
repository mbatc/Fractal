#ifndef fl_Graphics_IndexBuffer_h__
#define fl_Graphics_IndexBuffer_h__

#include "../util/flType.h"
#include "flInterface.h"

namespace flEngine
{
  namespace Graphics
  {
    class HardwareBuffer;

    class flEXPORT IndexBuffer : public Interface
    {
    public:
      /**
       * @brief Bind the VertexBuffer to the the graphics API context
       */
      virtual void Bind() = 0;

      /**
       * @brief Unbind the VertexBuffer from the graphics API context
       */
      virtual void Unbind() = 0;

      /**
       * @brief Resize the index buffer.
       * 
       * @param [in] indexCount  The number of indices to allocate.
       * @param [in] discardData If true, the old buffers data will be discard.
       *                         The new buffer will be uninitialized.
       */
      virtual void Resize(flIN int64_t indexCount, flIN bool discardData = true) = 0;

      /**
       * @brief Set the buffers index data.
       *
       * The buffer will be resized to fit the new indices.
       * 
       * @param [in] pValues A pointer to an array of indices to copy to the buffer.
       * @param [in] count   The number of indices to copy.
       * @param [in] offset  An optional offset into pValues to use.
       */
      virtual void SetIndices(flIN uint32_t const* pValues, flIN int64_t count, flIN int64_t offset = 0) = 0;

      /**
       * @brief Get the number of indices in the buffer.
       *
       * @return The number of indices.
       */
      virtual int64_t GetIndexCount() const = 0;

      /**
       * @brief Get the primitive type of the indices.
       *
       * @return The Type of each index.
       */
      virtual Util::Type GetIndexType() const = 0;

      /**
       * @brief Get the size of each index in bytes.
       * 
       * @return The size of each index.
       */
      virtual int64_t GetElementSize() const = 0;

      /**
       * @brief Get the hardware buffer that contains the data for this vertex buffer.
       * 
       * @return A pointer to the underlying HardwareBuffer.
       */
      virtual HardwareBuffer* GetBuffer() = 0;
      virtual HardwareBuffer const * GetBuffer() const = 0;
    };
  }
}

#endif // fl_Graphics_IndexBuffer_h__
