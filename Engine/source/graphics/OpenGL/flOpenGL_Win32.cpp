#include "flOpenGL_Impl.h"
#include "graphics\OpenGL\flGLWindowRenderTarget.h"

#if flUSING(flPLATFORM_WINDOWS)

#include <windows.h>

using namespace flEngine;
using namespace flEngine::Graphics;

void Impl_OpenGL::Construct(Platform::Window *pWindow)
{
  GLWindowRenderTarget *pWndRenderTarget = GLWindowRenderTarget::Create(pWindow, PF_RGBA, PCT_UInt8, DF_Float24Stencil8);

  HWND hWnd = (HWND)pWindow->GetNativeHandle();
  HDC hDC = GetDC(hWnd);

  HGLRC hTempGLRC = wglCreateContext(hDC);

  // wglCreateContextAttribsARB();

  pWndRenderTarget->DecRef();
}

#endif
