#include "graphics\OpenGL\flGLWindowRenderTarget.h"
#include "flGLWindowRenderTarget_Impl.h"

using namespace flEngine;
using namespace flEngine::Graphics;

flPIMPL_IMPL(GLWindowRenderTarget)

GLWindowRenderTarget::GLWindowRenderTarget(flIN Platform::Window *pWindow, flIN const RenderTargetOptions *pOptions)
{
  Impl()->Construct(pWindow, pOptions);
}

Platform::Window * flEngine::Graphics::GLWindowRenderTarget::GetWindow() const
{
  return Impl()->GetWindow();
}

bool GLWindowRenderTarget::SetFormat(flIN const RenderTargetOptions *pOptions)
{
  return Impl()->SetFormat(pOptions);
}

void GLWindowRenderTarget::Clear(flIN const Util::Colour &colour, flIN const float &depth, flIN const int32_t &stencil)
{
  return Impl()->Clear(colour, depth, stencil);
}

void GLWindowRenderTarget::ClearDepth(flIN const float &depth)
{
  return Impl()->ClearDepth(depth);
}

void GLWindowRenderTarget::ClearColour(flIN const Util::Colour &colour)
{
  return Impl()->ClearColour(colour);
}

void GLWindowRenderTarget::ClearStencil(flIN const int32_t &colour)
{
  return Impl()->ClearStencil(colour);
}

void GLWindowRenderTarget::Swap()
{
  return Impl()->Swap();
}

void* GLWindowRenderTarget::GetNativeHandle() const
{
  return Impl()->GetNativeHandle();
}

void GLWindowRenderTarget::Bind()
{
  return Impl()->Bind();
}

GLWindowRenderTarget* GLWindowRenderTarget::Create(flIN Platform::Window *pWindow, flIN const RenderTargetOptions *pOptions)
{
  return flNew GLWindowRenderTarget(pWindow, pOptions);
}
