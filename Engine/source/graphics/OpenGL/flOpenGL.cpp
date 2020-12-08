#include "flOpenGL_Impl.h"
#include "graphics/OpenGL/flGLGeometry.h"
#include "graphics/OpenGL/flGLIndexBuffer.h"
#include "graphics/OpenGL/flGLVertexBuffer.h"
#include "graphics/OpenGL/flGLPixelBuffer.h"
#include "graphics/OpenGL/flGLProgram.h"
#include "graphics/OpenGL/flGLWindowRenderTarget.h"
#include "graphics/OpenGL/flGLTextureRenderTarget.h"

using namespace flEngine;
using namespace flEngine::Graphics;

flPIMPL_IMPL(OpenGL)

#define flIMPL flPIMPL(OpenGL)

void OpenGL::Render()
{
  flIMPL->Render();
}

WindowRenderTarget* OpenGL::CreateWindowRenderTarget(flIN Platform::Window *pWindow, flIN PixelFormat colourFormat, flIN PixelComponentType pixelComponentType, flIN DepthFormat depthFormat)
{
  return GLWindowRenderTarget::Create(pWindow, colourFormat, pixelComponentType, depthFormat);
}

TextureRenderTarget* OpenGL::CreateTextureRenderTarget()
{
  return GLTextureRenderTarget::Create();
}

Geometry* OpenGL::CreateGeometry()
{
  return GLGeometry::Create();
}

IndexBuffer* OpenGL::CreateIndexBuffer()
{
  return GLIndexBuffer::Create();
}

VertexBuffer* OpenGL::CreateVertexBuffer()
{
  return GLVertexBuffer::Create();
}

PixelBuffer* OpenGL::CreatePixelBuffer()
{
  return GLPixelBuffer::Create();
}

Program* OpenGL::CreateProgram()
{
  return GLProgram::Create();
}

OpenGL::OpenGL(flIN Platform::Window *pWindow)
{
  flIMPL->Construct(pWindow);
}

OpenGL* OpenGL::Create(flIN Platform::Window *pWindow)
{
  return flNew OpenGL(pWindow);
}

void OpenGL::SetGeometry(flIN Geometry *pGeometry)
{
  return flIMPL->SetGeometry(pGeometry);
}

void OpenGL::SetRenderTarget(flIN RenderTarget *pRenderTarget)
{
  return flIMPL->SetRenderTarget(pRenderTarget);
}

void OpenGL::SetProgram(flIN Program *pProgram)
{
  return flIMPL->SetProgram(pProgram);
}

DeviceState* OpenGL::GetState()
{
  return flIMPL->GetState();
}
