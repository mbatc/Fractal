#ifndef fl_Graphics_VertexBuffer_h__
#define fl_Graphics_VertexBuffer_h__

#include "OpenGL/flGLHardwareBuffer.h"
#include "util/flType.h"
#include "flAPI.h"

namespace flEngine
{
  namespace Graphics
  {
    class flEXPORT VertexBuffer : public HardwareBuffer
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
       */
      virtual int64_t GetElementCount() = 0;

      /**
       * @brief Get vertex buffers elements primitive type.
       */
      virtual Util::Type GetPrimitiveType() = 0;

      /**
       * @brief Get the number of primitive items per element.
       */
      virtual int64_t GetPrimitiveWidth() = 0;

      /**
       * @brief Get the hardware buffer that contains the data for this vertex buffer.
       */
      virtual HardwareBuffer* GetBuffer() const = 0;
    };
  }
}

#endif // fl_Graphics_VertexBuffer_h__
