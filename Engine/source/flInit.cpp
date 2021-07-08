#include "flEngine.h"
#include "OpenGL/flOpenGL.h"

namespace Fractal
{
  bool Initialize()
  {
    bool result = true;

    result &=
      MeshRenderer::Register()
      && Light::Register()
      && Camera::Register()
      && Transform::Register();

    result &= OpenGL::RegisterAPI();

    return result;
  }
}
