#ifndef fl_Graphics_GLIndexBuffer_h__
#define fl_Graphics_GLIndexBuffer_h__

#include "../flIndexBuffer.h"
#include "flGLHardwareBuffer.h"

namespace flEngine
{
  namespace Graphics
  {
    class flPIMPL_CLASS(GLIndexBuffer);

    class flEXPORT GLIndexBuffer
      : public IndexBuffer
      , public GLHardwareBuffer
    {
      flPIMPL_DEF(GLIndexBuffer);
    public:
      static IndexBuffer* Create(flIN int64_t indexCount, void *pData = nullptr);

      void Resize(flIN int64_t indexCount) override;
      void SetIndices(flIN uint32_t* pValues, flIN int64_t count) override;
      int64_t GetIndexCount() const override;
      Util::Type GetIndexType() const override;
      int64_t GetElementSize() const override;
    };
  }
}

#endif // fl_Graphics_IndexBuffer_h__
