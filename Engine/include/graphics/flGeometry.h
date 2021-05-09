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
      virtual void AddVertexBuffer(flIN char const * name, flIN VertexBuffer *pBuffer) = 0;
      virtual void AddIndexBuffer(flIN IndexBuffer *pBuffer) = 0;

      virtual void RemoveVertexBuffer(flIN int64_t index) = 0;
      virtual void RemoveIndexBuffer(flIN int64_t index) = 0;

      virtual int64_t GetVertexBufferCount() = 0;
      virtual int64_t GetIndexBufferCount() = 0;
      virtual char const * GetVertexBufferName(flIN int64_t index) = 0;

      virtual IndexBuffer* GetIndexBuffer(flIN int64_t index) = 0;
      virtual VertexBuffer* GetVertexBuffer(flIN int64_t index) = 0;
      virtual VertexBuffer* GetVertexBuffer(flIN char const * name) = 0;

      virtual int64_t GetVertexCount() const = 0;
      virtual int64_t GetIndexCount(flIN int64_t indexBuffer) const = 0;

      virtual void* GetNativeResource() = 0;

      virtual bool Update() = 0;
    };
  }
}

#endif // flGeometry_h__
