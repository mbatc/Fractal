#include "flOpenGL_Impl.h"
#include "graphics\OpenGL\flGLWindowRenderTarget.h"

#if flUSING(flPLATFORM_WINDOWS)

#include <windows.h>
#include "GL/GL.h"
#include "GL/glew.h"
#include "GL/wglew.h"

using namespace flEngine;
using namespace flEngine::Graphics;

void Impl_OpenGL::Construct(Platform::Window *pWindow)
{
  RenderTargetOptions options;
  options.colourFormat =PF_RGBA;
  options.pixelComponentType = PCT_UInt8;
  options.depthFormat = DF_Float24Stencil8;

  GLWindowRenderTarget *pWndRenderTarget = GLWindowRenderTarget::Create(pWindow, &options);

  HWND hWnd = (HWND)pWindow->GetNativeHandle();
  HDC hDC = GetDC(hWnd);
  wglChoosePixelFormatARB();
  wglGetPixelFormatAttribivARB(hDC, );
  HGLRC hTempGLRC = wglCreateContext(hDC);

  int attributes[] = {
    WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
    WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
    WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
    WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
    WGL_COLOR_BITS_ARB, 32,
    WGL_DEPTH_BITS_ARB, 24,
    WGL_STENCIL_BITS_ARB, 8,
    WGL_SAMPLE_BUFFERS_ARB, 1, // Number of buffers (must be 1 at time of writing)
    WGL_SAMPLES_ARB, 4,        // Number of samples
    0
  };

  // wglCreateContextAttribsARB();

  // pWndRenderTarget->DecRef();
}

#endif
