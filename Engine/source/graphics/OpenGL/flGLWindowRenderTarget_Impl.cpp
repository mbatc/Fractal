#include "flGLWindowRenderTarget_Impl.h"

#if flUSING(flPLATFORM_WINDOWS)

#include <windows.h>
#include "ctVector.h"
#include "GL/glew.h"
#include "GL/wglew.h"
#include "GL/GL.h"
#include "../../platform/flWindow_Impl.h"

using namespace flEngine;
using namespace flEngine::Graphics;

// Extern some variables from the OpenGL implementation
extern HDC   flEngine_GL_hCurrentDC;
extern HGLRC flEngine_GL_hCurrentGLRC;

flEngine::Graphics::Impl_GLWindowRenderTarget::~Impl_GLWindowRenderTarget()
{
  ReleaseDC((HWND)m_pWindow->GetNativeHandle(), (HDC)m_hDC);
}

void Impl_GLWindowRenderTarget::Construct(flIN Platform::Window *pWindow, flIN const RenderTargetOptions *pOptions)
{
  m_pWindow = pWindow;
  if (!m_pWindow || m_pWindow->GetRenderTarget() == this)
    return;
  m_pWindow->GetImpl()->BindRenderTarget(this);
  SetFormat(pOptions);
}

void _AddAttribute(ctVector<int> *pAttributes, const int &attrib, const int &val)
{
  pAttributes->push_back(attrib);
  pAttributes->push_back(val);
}

bool Impl_GLWindowRenderTarget::SetFormat(flIN const RenderTargetOptions *pOptions)
{
  HWND hWnd = (HWND)m_pWindow->GetNativeHandle();
  HDC hDC = GetDC(hWnd);

  static const RenderTargetOptions defaultOptions;

  if (!pOptions)
    pOptions = &defaultOptions;

  int componentWidth = 0;
  bool floatPixel = false;

  switch (pOptions->pixelComponentType)
  {
  case Graphics::PixelComponentType::Float16:
    componentWidth = 16;
    floatPixel = true;
    break;
  case Graphics::PixelComponentType::Float32:
    componentWidth = 32;
    floatPixel = true;
    break;
  case Graphics::PixelComponentType::UInt8:   componentWidth = 8;  break;
  case Graphics::PixelComponentType::UInt16:  componentWidth = 16; break;
  case Graphics::PixelComponentType::UInt32:  componentWidth = 32; break;
  case Graphics::PixelComponentType::Int8:    componentWidth = 8;  break;
  case Graphics::PixelComponentType::Int16:   componentWidth = 16; break;
  case Graphics::PixelComponentType::Int32:   componentWidth = 32; break;
  case Graphics::PixelComponentType::UNorm8:  componentWidth = 8;  break;
  case Graphics::PixelComponentType::UNorm16: componentWidth = 16; break;
  default:                    componentWidth = 8; break;
  }

  int64_t numComponents = 0;
  switch (pOptions->colourFormat)
  {
  case PixelFormat::Red:  numComponents = 1; break;
  case PixelFormat::RG:   numComponents = 2; break;
  case PixelFormat::RGB:  numComponents = 3; break;
  case PixelFormat::RGBA: numComponents = 4; break;
  }

  int64_t numDepthBits = 0;
  int64_t numStencilBits = 0;
  switch (pOptions->depthFormat)
  {
    // Depth-only formats
  case Graphics::DepthFormat::Float16: numDepthBits = 16; break;
  case Graphics::DepthFormat::Float24: numDepthBits = 24; break;
  case Graphics::DepthFormat::Float32: numDepthBits = 32; break;

    // Stencil formats
  case Graphics::DepthFormat::Float24Stencil8:
    numDepthBits = 24;
    numStencilBits = 8;
    break;
  case Graphics::DepthFormat::Float32Stencil8:
    numDepthBits = 32;
    numStencilBits = 8;
    break;
  }

  // Get the attribute list
  ctVector<int> attribList;
  _AddAttribute(&attribList, WGL_DRAW_TO_WINDOW_ARB, GL_TRUE);
  _AddAttribute(&attribList, WGL_SUPPORT_OPENGL_ARB, GL_TRUE);
  _AddAttribute(&attribList, WGL_DOUBLE_BUFFER_ARB,  GL_TRUE);

  // Colour Buffer Format
  _AddAttribute(&attribList, WGL_COLOR_BITS_ARB, int(componentWidth * numComponents));
  if (floatPixel) _AddAttribute(&attribList, WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_FLOAT_ARB);
  else            _AddAttribute(&attribList, WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB);

  // Depth Buffer Format
  if (numDepthBits > 0)          _AddAttribute(&attribList, WGL_DEPTH_BITS_ARB,   (int)numDepthBits);
  if (numStencilBits > 0)        _AddAttribute(&attribList, WGL_STENCIL_BITS_ARB, (int)numStencilBits);

  // Other settings
  if (pOptions->sampleCount > 1) _AddAttribute(&attribList, WGL_SAMPLES_ARB, (int)pOptions->sampleCount);
  if (pOptions->stereoBuffer)    _AddAttribute(&attribList, WGL_STEREO_ARB, GL_TRUE);

  attribList.push_back(0);

  extern PFNWGLCHOOSEPIXELFORMATARBPROC flEngine_glChoosePixelFormatARB;

  int  pixelFormat = 0;
  UINT numFormatsFound = 0;

  if (!flEngine_glChoosePixelFormatARB)
    return false;

  if (!flEngine_glChoosePixelFormatARB(hDC, attribList.data(), 0, 1, &pixelFormat, &numFormatsFound))
    return false;

  if (m_pixelFormatSet)
  {
    // Get some properties of the window
    const char *title = m_pWindow->GetTitle();
    Platform::Window::Flags flags = m_pWindow->GetFlags();

    // Recreate the window
    m_pWindow->GetImpl()->Destroy();
    m_pWindow->GetImpl()->Create(m_pWindow, title, flags, GetModuleHandle(NULL));
  }

  PIXELFORMATDESCRIPTOR pfd = { 0 };
  memset(&pfd, 0, sizeof(pfd));
  DescribePixelFormat(hDC, pixelFormat, sizeof(pfd), &pfd);
  if (!SetPixelFormat(hDC, pixelFormat, &pfd))
    return false;

  m_hDC = hDC;
  m_pixelFormatSet = true;
  return true;
}

Platform::Window* Impl_GLWindowRenderTarget::GetWindow() const
{
  return m_pWindow;
}

void Impl_GLWindowRenderTarget::Clear(flIN const Util::Colour &colour, flIN const float &depth, flIN const int32_t &stencil)
{
  ClearColour(colour);
  ClearDepth(depth);
  ClearStencil(stencil);
}

void Impl_GLWindowRenderTarget::ClearDepth(flIN const float &depth)
{
  MakeCurrent();
  glClearDepth(depth);
  glClear(GL_DEPTH_BUFFER_BIT);
}

void Impl_GLWindowRenderTarget::ClearColour(flIN const Util::Colour &colour)
{
  MakeCurrent();
  glClearColor(colour.r, colour.g, colour.b, colour.a);
  glClear(GL_COLOR_BUFFER_BIT);
}

void Impl_GLWindowRenderTarget::ClearStencil(flIN const int32_t &stencil)
{
  MakeCurrent();
  glClearStencil(stencil);
  glClear(GL_STENCIL_BUFFER_BIT);
}

void Impl_GLWindowRenderTarget::Swap()
{
  if (!SwapBuffers((HDC)m_hDC))
    printf("Swap Buffers Failed\n");
}

void* flEngine::Graphics::Impl_GLWindowRenderTarget::GetNativeHandle() const
{
  return m_hDC;
}

void Impl_GLWindowRenderTarget::MakeCurrent()
{
  if (m_hDC != flEngine_GL_hCurrentDC) // Make this the current DC
  {
    wglMakeCurrent((HDC)m_hDC, flEngine_GL_hCurrentGLRC);
    flEngine_GL_hCurrentDC = (HDC)m_hDC;
  }
}

#endif
