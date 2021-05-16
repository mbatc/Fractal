#ifndef fl_Graphics_VertexArray_h__
#define fl_Graphics_VertexArray_h__

#include "flAPIResource.h"
#include "../flInterface.h"

namespace flEngine
{
  namespace Graphics
  {
    class VertexBuffer;
    class IndexBuffer;

    class flEXPORT VertexArray : public APIResource
    {
    protected:
      VertexArray(API *pAPI);

    public:
      virtual void Bind() = 0;

      virtual void Unbind() = 0;

      virtual void AddVertexBuffer(flIN VertexBuffer* pBuffer) = 0;

      virtual void SetIndexBuffer(flIN IndexBuffer* pBuffer) = 0;

      virtual void RemoveVertexBuffer(flIN int64_t index) = 0;

      virtual int64_t GetVertexBufferCount() = 0;

      virtual IndexBuffer* GetIndexBuffer() = 0;

      virtual VertexBuffer* GetVertexBuffer(flIN int64_t index) = 0;

      virtual int64_t GetVertexCount() const = 0;

      virtual int64_t GetIndexCount() const = 0;

      virtual void* GetNativeResource() = 0;
    };
  }
}

#endif // flGeometry_h__
