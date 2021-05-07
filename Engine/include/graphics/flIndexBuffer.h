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
      virtual int64_t GetIndexCount() const = 0;
      virtual Util::Type GetIndexType() const = 0;
      virtual int64_t GetElementSize() const = 0;
    };
  }
}

#endif // fl_Graphics_IndexBuffer_h__
