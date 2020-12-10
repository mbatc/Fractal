#include "graphics\OpenGL\flGLWindowRenderTarget.h"
#include "flGLWindowRenderTarget_Impl.h"

using namespace flEngine;
using namespace flEngine::Graphics;

flPIMPL_IMPL(GLWindowRenderTarget)

#define flIMPL flPIMPL(GLWindowRenderTarget)

GLWindowRenderTarget::GLWindowRenderTarget(flIN Platform::Window *pWindow, flIN const RenderTargetOptions *pOptions)
{
  flIMPL->Construct(pWindow, pOptions);
}

Platform::Window * flEngine::Graphics::GLWindowRenderTarget::GetWindow() const
{
  return flIMPL->GetWindow();
}

bool GLWindowRenderTarget::SetFormat(flIN const RenderTargetOptions *pOptions)
{
  return flIMPL->SetFormat(pOptions);
}

void GLWindowRenderTarget::Clear(flIN const Util::Colour &colour, flIN const float &depth, flIN const int32_t &stencil)
{
  return flIMPL->Clear(colour, depth, stencil);
}

void GLWindowRenderTarget::ClearDepth(flIN const float &depth)
{
  return flIMPL->ClearDepth(depth);
}

void GLWindowRenderTarget::ClearColour(flIN const Util::Colour &colour)
{
  return flIMPL->ClearColour(colour);
}

void GLWindowRenderTarget::ClearStencil(flIN const int32_t &colour)
{
  return flIMPL->ClearStencil(colour);
}

void GLWindowRenderTarget::Swap()
{
  return flIMPL->Swap();
}

void* GLWindowRenderTarget::GetNativeHandle() const
{
  return flIMPL->GetNativeHandle();
}

GLWindowRenderTarget* GLWindowRenderTarget::Create(flIN Platform::Window *pWindow, flIN const RenderTargetOptions *pOptions)
{
  return flNew GLWindowRenderTarget(pWindow, pOptions);
}
