#include "flInit.h"
#include "flAPI.h"
#include "OpenGL/flOpenGL.h"

namespace Fractal
{
  bool flEXPORT Initialize()
  {
    return OpenGL::RegisterAPI();
  }
}
