#include "flInit.h"
#include "graphics/flAPI.h"
#include "graphics/OpenGL/flOpenGL.h"

namespace flEngine
{
  namespace Graphics
  {
    bool Init()
    {
      // Add default Graphics API's
      return OpenGL::RegisterAPI();
    }
  }

  bool flEXPORT Initialize()
  {
    return Graphics::Init();
  }
}
