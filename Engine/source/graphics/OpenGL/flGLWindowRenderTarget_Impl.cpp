#include "flGLWindowRenderTarget_Impl.h"
#include <windows.h>

using namespace flEngine;
using namespace flEngine::Graphics;
using namespace flEngine::Platform;

void Impl_GLWindowRenderTarget::Construct(flIN Platform::Window *pWindow, flIN PixelFormat colourFormat, flIN PixelComponentType pixelComponentType, flIN DepthFormat depthFormat)
{
  m_pWindow = pWindow;
  SetFormat(colourFormat, pixelComponentType, depthFormat);
}

bool Impl_GLWindowRenderTarget::SetFormat(flIN PixelFormat colourFormat, flIN PixelComponentType pixelComponentType, flIN DepthFormat depthFormat)
{
  m_pWindow->SetPixelFormat(colourFormat, pixelComponentType, depthFormat);
  return true;
}
