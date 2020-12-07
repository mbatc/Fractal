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
      static GLIndexBuffer* Create();
    };
  }
}

#endif // fl_Graphics_IndexBuffer_h__
