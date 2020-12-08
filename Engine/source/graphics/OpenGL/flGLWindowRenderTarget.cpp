#include "graphics\OpenGL\flGLWindowRenderTarget.h"
#include "flGLWindowRenderTarget_Impl.h"

using namespace flEngine;
using namespace flEngine::Graphics;

flPIMPL_IMPL(GLWindowRenderTarget)

#define flIMPL flPIMPL(GLWindowRenderTarget)

GLWindowRenderTarget::GLWindowRenderTarget(flIN Platform::Window * pWindow, flIN RenderTargetOptions *pOptions)
{
  flIMPL->Construct(pWindow, pOptions);
}

Platform::Window * flEngine::Graphics::GLWindowRenderTarget::GetWindow() const
{
  return flIMPL->GetWindow();
}

bool flEngine::Graphics::GLWindowRenderTarget::SetFormat(flIN PixelFormat colourFormat, flIN RenderTargetOptions *pOptions)
{
  return flIMPL->SetFormat(colourFormat, pOptions);
}

GLWindowRenderTarget* GLWindowRenderTarget::Create(flIN Platform::Window *pWindow, flIN RenderTargetOptions *pOptions)
{
  return flNew GLWindowRenderTarget(pWindow, pOptions);
}
