#include "flGLWindowRenderTarget_Impl.h"
#include <windows.h>

using namespace flEngine;
using namespace flEngine::Graphics;

void Impl_GLWindowRenderTarget::Construct(flIN Platform::Window *pWindow, flIN RenderTargetOptions *pOptions)
{
  m_pWindow = pWindow;
  SetFormat(pOptions);
}

bool Impl_GLWindowRenderTarget::SetFormat(flIN RenderTargetOptions *pOptions)
{
  m_pWindow->SetPixelFormat(pOptions);
  return true;
}

Platform::Window* Impl_GLWindowRenderTarget::GetWindow() const
{
  return m_pWindow;
}
