#ifndef fl_Graphics_UniformBuffer_h__
#define fl_Graphics_UniformBuffer_h__

#include "flHardwareBuffer.h"
#include "flAPIResource.h"

namespace flEngine
{
  namespace Graphics
  {
    class flEXPORT UniformBuffer : public APIResource
    {
    protected:
      UniformBuffer(API *pAPI);

    public:
      virtual void Bind(flIN int64_t index) = 0;
      virtual void Unbind() = 0;

      virtual HardwareBuffer * GetBuffer() = 0;
      virtual HardwareBuffer const * GetBuffer() const = 0;
    };
  }
}

#endif // fl_Graphics_UniformBuffer_h__
