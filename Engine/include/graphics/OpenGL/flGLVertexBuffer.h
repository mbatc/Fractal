#ifndef fl_Graphics_GLVertexBuffer_h__
#define fl_Graphics_GLVertexBuffer_h__

#include "../flVertexBuffer.h"
#include "flGLHardwareBuffer.h"

namespace flEngine
{
  namespace Graphics
  {
    class flPIMPL_CLASS(GLVertexBuffer);

    class flEXPORT GLVertexBuffer
      : public VertexBuffer
      , public GLHardwareBuffer
    {
      flPIMPL_DEF(GLVertexBuffer);

    public:
      static VertexBuffer* Create(flIN Util::Type primitiveType = Util::Type_Unknown, flIN int64_t primitiveWidth = 0, void *pInitialData = nullptr);

      /**
       * @brief Set the format of the vertex buffer data.
       *
       * Use this function to specify the format of the data in the vertex buffer.
       *
       * @param [in] primitiveType  The data type of the primitives in the buffer.
       * @param [in] primitiveWidth The number of primitive items per vertex element.
       */
      virtual void SetFormat(flIN Util::Type primitiveType, flIN int64_t primitiveWidth) override;

      /**
       * @brief Get the number of elements in the vertex buffer.
       *
       * The number of elements is calculated based on the buffers total size on bytes,
       * and the size of the format specified via SetFormat.
       *
       * SetFormat must be called before using this function.
       */
      virtual int64_t GetElementCount() override;

      /**
       * @brief Get vertex buffers elements primitive type.
       */
      virtual Util::Type GetPrimitiveType() override;

      /**
       * @brief Get the number of primitive items per element.
       */
      virtual int64_t GetPrimitiveWidth() override;
    };
  }
}

#endif // fl_Graphics_IndexBuffer_h__
