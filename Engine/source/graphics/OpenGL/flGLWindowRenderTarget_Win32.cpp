#include "graphics\OpenGL\flGLWindowRenderTarget.h"

using namespace flEngine::Graphics;

#if flUSING(flPLATFORM_WINDOWS)

GLWindowRenderTarget* GLWindowRenderTarget::Create(flIN PixelFormat colourFormat, flIN PixelComponentType pixelComponentType, flIN DepthFormat depthFormat)
{
  return flNew GLWindowRenderTarget(colourFormat, pixelComponentType, depthFormat);
}

#endif
