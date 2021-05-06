#ifndef fl_Graphics_IndexBuffer_h__
#define fl_Graphics_IndexBuffer_h__

#include "flHardwareBuffer.h"
#include "../util/flType.h"

namespace flEngine
{
  namespace Graphics
  {
    class flEXPORT IndexBuffer : public HardwareBuffer
    {
    public:
      virtual void Resize(flIN int64_t indexCount) = 0;
      virtual void SetIndices(flIN uint32_t* pValues, flIN int64_t count) = 0;
      virtual void GetIndexCount() = 0;
      virtual void SetIndex(flIN int64_t index, flIN uint32_t value) = 0;
      virtual uint32_t GetIndex(flIN int64_t index) = 0;
      virtual Util::Type GetIndexType() = 0;
    };
  }
}

#endif // fl_Graphics_IndexBuffer_h__
