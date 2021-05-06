#ifndef fl_Graphics_GLIndexBuffer_h__
#define fl_Graphics_GLIndexBuffer_h__

#include "../flIndexBuffer.h"

namespace flEngine
{
  namespace Graphics
  {
    class flPIMPL_CLASS(GLIndexBuffer);

    class flEXPORT GLIndexBuffer : public IndexBuffer
    {
      flPIMPL_DEF(GLIndexBuffer);

    public:
      void Resize(flIN int64_t indexCount) override;
      void SetIndices(flIN uint32_t* pValues, flIN int64_t count) override;
      void GetIndexCount() override;
      void SetIndex(flIN int64_t index, flIN uint32_t value) override;
      uint32_t GetIndex(flIN int64_t index) override;
      Util::Type GetIndexType() override;
    };
  }
}

#endif // fl_Graphics_IndexBuffer_h__
