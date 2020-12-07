#ifndef fl_Graphics_GLUniformBuffer_h__
#define fl_Graphics_GLUniformBuffer_h__

#include "../flUniformBuffer.h"

namespace flEngine
{
  namespace Graphics
  {
    class GLUniformBuffer : public UniformBuffer
    {
    public:
      static GLUniformBuffer* Create();

    };
  }
}

#endif // fl_Graphics_UniformBuffer_h__
