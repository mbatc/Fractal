#ifndef fl_Graphics_Geometry_h__
#define fl_Graphics_Geometry_h__

#include "../flInterface.h"

namespace flEngine
{
  namespace Graphics
  {
    class VertexBuffer;
    class IndexBuffer;

    class flEXPORT Geometry : public Interface
    {
    public:
      /**
       * Add a VertexBuffer to the geometry.
       * 
       * @brief [in] An ID that can be used to access the VertexBuffer
       * @brief [in] pBuffer The VertexBuffer to add
       */
      virtual void AddVertexBuffer(flIN int64_t id, flIN VertexBuffer *pBuffer) = 0;
      virtual void AddIndexBuffer(flIN IndexBuffer *pBuffer) = 0;

      virtual int64_t GetVertexBufferCount() = 0;
      virtual int64_t GetVertexBufferID(flIN int64_t index) = 0;
      virtual int64_t GetIndexBufferCount() = 0;

      virtual IndexBuffer* GetIndexBuffer(flIN int64_t index) = 0;
      virtual VertexBuffer* GetVertexBuffer(flIN int64_t index) = 0;
      virtual VertexBuffer* GetVertexBufferByID(flIN int64_t id) = 0;
    };
  }
}

#endif // flGeometry_h__
