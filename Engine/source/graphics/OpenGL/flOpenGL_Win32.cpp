#include "flOpenGL.h"

#if flUSING(flPLATFORM_WINDOWS)

#include "graphics\OpenGL\flGLWindowRenderTarget.h"
#include "flGLDeviceState.h"
#include "ctString.h"
#include <windows.h>
#include "GL/glew.h"
#include "GL/wglew.h"
#include "GL/GL.h"

using namespace flEngine;
using namespace flEngine::Graphics;

static PIXELFORMATDESCRIPTOR _defaultPfd = {
  sizeof(PIXELFORMATDESCRIPTOR),
  1,
  PFD_DRAW_TO_WINDOW,
  PFD_TYPE_RGBA,
  32,
  8, 0, 8, 0, 8, 0,
  0, 0, 0, 0, 0,
  24, 8,
  0,
  0,
  0,
  PFD_MAIN_PLANE,
  0,
  0
};

PFNWGLCHOOSEPIXELFORMATARBPROC    flEngine_glChoosePixelFormatARB = nullptr;
PFNWGLCREATECONTEXTATTRIBSARBPROC flEngine_glCreateContextAttribsARB = nullptr;

// The currently bound render context
HDC   flEngine_GL_hCurrentDC   = 0;
HGLRC flEngine_GL_hCurrentGLRC = 0;

static void GLAPIENTRY _ErrorMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
  userParam, length;
  ctString assertion = "OpenGL Error (type: " + ctString((int64_t)type) + ", severity: " + ctString((int64_t)severity) + ", id: " + ctString((int64_t)id) + ")\n\n" + message;
  printf((assertion + "\n").c_str());
  ctRelAssert(type != GL_DEBUG_TYPE_ERROR, assertion);
}

OpenGL::OpenGL(Platform::Window *pWindow, const RenderTargetOptions *pOptions)
  : m_pState(GLDeviceState::Create())
{
  // Create a temporary window to make our fake GL context
  Platform::Window tempWindow("tmp", Platform::Window::Flag_None, Platform::Window::DM_Windowed);

  HWND hTempWnd       = (HWND)tempWindow.GetNativeHandle();
  HDC hTempDC         = GetDC(hTempWnd);
  int tempPixelFormat = ChoosePixelFormat(hTempDC, &_defaultPfd);

  SetPixelFormat(hTempDC, tempPixelFormat, &_defaultPfd);
  HGLRC hTempGLRC = wglCreateContext(hTempDC);
  wglMakeCurrent(hTempDC, hTempGLRC);

  flEngine_glChoosePixelFormatARB    = reinterpret_cast<PFNWGLCHOOSEPIXELFORMATARBPROC>(wglGetProcAddress("wglChoosePixelFormatARB"));
  flEngine_glCreateContextAttribsARB = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(wglGetProcAddress("wglCreateContextAttribsARB"));

  const int major_min = 4;
  const int minor_min = 5;
  int contextAttribs[] = {
    WGL_CONTEXT_MAJOR_VERSION_ARB, major_min,
    WGL_CONTEXT_MINOR_VERSION_ARB, minor_min,
    WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
    0
  };
  
  // Create the render target for the actual window
  WindowRenderTarget *pWndRenderTarget = GLWindowRenderTarget::Create(this, pWindow, pOptions);
  HWND  hWnd  = (HWND)tempWindow.GetNativeHandle();
  HDC   hDC   = (HDC)pWndRenderTarget->GetNativeResource();
  HGLRC hGLRC = flEngine_glCreateContextAttribsARB(hDC, nullptr, contextAttribs);

  // Destroy the temporary context
  wglMakeCurrent(nullptr, nullptr);
  wglDeleteContext(hTempGLRC);
  ReleaseDC(hTempWnd, hTempDC);

  // Make the new context current
  if (hGLRC)
  {
    wglMakeCurrent(hDC, hGLRC);
    wglewInit();
    glewInit();

    flEngine_GL_hCurrentDC   = hDC;
    flEngine_GL_hCurrentGLRC = hGLRC;
  }

#ifdef _DEBUG // Enable error logging in debug
  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(_ErrorMessageCallback, 0);
#endif
}

#endif
