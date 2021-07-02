#include "flEngine.h"
#include "OpenGL/flOpenGL.h"

namespace Fractal
{
  bool flEXPORT Initialize()
  {
    bool result = true;

    result &=
      MeshRenderer::Register()
      && Transform::Register();

    result &= OpenGL::RegisterAPI();

    return result;
  }
}
