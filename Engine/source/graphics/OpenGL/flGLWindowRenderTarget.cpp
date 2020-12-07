#include "graphics\OpenGL\flGLWindowRenderTarget.h"
#include "flGLWindowRenderTarget_Impl.h"

using namespace flEngine::Graphics;

#define flIMPL flPIMPL(GLWindowRenderTarget)

flEngine::Graphics::GLWindowRenderTarget::GLWindowRenderTarget(flIN Platform::Window * pWindow, flIN PixelFormat colourFormat, flIN PixelComponentType pixelComponentType, flIN DepthFormat depthFormat)
{
  flIMPL->Construct(pWindow, colourFormat, pixelComponentType, depthFormat);
}

GLWindowRenderTarget* GLWindowRenderTarget::Create(flIN Platform::Window *pWindow, flIN PixelFormat colourFormat, flIN PixelComponentType pixelComponentType, flIN DepthFormat depthFormat)
{
  return flNew GLWindowRenderTarget(pWindow, colourFormat, pixelComponentType, depthFormat);
}
