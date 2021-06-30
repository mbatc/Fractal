#ifndef fl_Graphics_VertexBuffer_h__
#define fl_Graphics_VertexBuffer_h__

#include "util/flType.h"
#include "flInterface.h"
#include "flAPIResource.h"
#include <initializer_list>

namespace flEngine
{
  namespace Graphics
  {
    class HardwareBuffer;
    class API;

    struct flEXPORT VertexElement
    {
      VertexElement();

      VertexElement(uint32_t location, Util::Type type, int64_t width, bool normalize = false);

      uint32_t   location;
      Util::Type type;
      int64_t    width;
      bool       normalize;
      int64_t    offset;
    };

    class flEXPORT VertexBuffer : public APIResource
    {
    protected:
      VertexBuffer(API *pAPI);

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
       * @brief Set the format of the vertex buffer data.
       *
       * Use this function to specify the format of the data in the vertex buffer.
       *
       * @param [in] primitiveType  The data type of the primitives in the buffer.
       * @param [in] primitiveWidth The number of primitive items per vertex element.
       */
      virtual void SetLayout(flIN VertexElement const* pElements, int64_t elementCount) = 0;

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
      virtual int64_t GetVertexCount() const = 0;

      /**
       * @brief Get the number of bytes per vertex.
       */
      virtual int64_t GetVertexStride() const = 0;

      /**
       * @brief Get the number of elements in the vertex layout.
       */
      virtual int64_t GetLayoutElementCount() const = 0;

      /**
       * @brief Get the description of an element in the vertex buffer.
       */
      virtual void GetLayoutElement(flIN int64_t index, flOUT VertexElement* pElement) const = 0;

      /**
       * @brief Get the hardware buffer that contains the data for this vertex buffer.
       * 
       * @return A pointer to the underlying HardwareBuffer.
       */
      virtual HardwareBuffer* GetBuffer() = 0;
      virtual HardwareBuffer const* GetBuffer() const = 0;

      /**
       * @brief Set the vertex layout from an initializer list of VertexElement's.
       */
      inline void SetLayout(std::initializer_list<VertexElement> const &elements) {
        SetLayout(elements.begin(), elements.size());
      }
    };
  }
}

#endif // fl_Graphics_VertexBuffer_h__
