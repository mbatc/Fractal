#ifndef fl_Graphics_GLProgram_h__
#define fl_Graphics_GLProgram_h__

#include "../flProgram.h"

namespace flEngine
{
  namespace Graphics
  {
    class GLProgram : public Program
    {
    public:
      static GLProgram* Create();
    };
  }
}

#endif // fl_Graphics_Program_h__
