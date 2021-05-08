#ifndef fl_Graphics_VertexBuffer_h__
#define fl_Graphics_VertexBuffer_h__

#include "util/flType.h"
#include "flInterface.h"

namespace flEngine
{
  namespace Graphics
  {
    class HardwareBuffer;

    class flEXPORT VertexBuffer : public Interface
    {
    public:
      /**
       * @brief Set the format of the vertex buffer data.
       * 
       * Use this function to specify the format of the data in the vertex buffer.
       * 
       * @param [in] primitiveType  The data type of the primitives in the buffer.
       * @param [in] primitiveWidth The number of primitive items per vertex element.
       */
      virtual void SetFormat(flIN Util::Type primitiveType, flIN int64_t primitiveWidth) = 0;

      /**
       * @brief Get the number of elements in the vertex buffer.
       * 
       * The number of elements is calculated based on the buffers total size on bytes, 
       * and the size of the format specified via SetFormat.
       * 
       * SetFormat must be called before using this function.
       * 
       * @return The number of elements in the vertex buffer.
       */
      virtual int64_t GetElementCount() const = 0;

      /**
       * @brief Get vertex buffers elements primitive type.
       * 
       * @return The primitive type of the vertex attribute.
       */
      virtual Util::Type GetPrimitiveType() const = 0;

      /**
       * @brief Get the number of primitive items per element.
       *
       * @return The primitive width of the vertex attribute.
       */
      virtual int64_t GetPrimitiveWidth() const = 0;

      /**
       * @brief Get the hardware buffer that contains the data for this vertex buffer.
       * 
       * @return A pointer to the underlying HardwareBuffer.
       */
      virtual HardwareBuffer* GetBuffer() = 0;
      virtual HardwareBuffer const* GetBuffer() const = 0;
    };
  }
}

#endif // fl_Graphics_VertexBuffer_h__
