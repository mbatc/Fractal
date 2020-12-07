#include "flOpenGL_Impl.h"
#include "graphics/OpenGL/flGLGeometry.h"
#include "graphics/OpenGL/flGLIndexBuffer.h"
#include "graphics/OpenGL/flGLVertexBuffer.h"
#include "graphics/OpenGL/flGLPixelBuffer.h"
#include "graphics/OpenGL/flGLProgram.h"
#include "graphics/OpenGL/flGLWindowRenderTarget.h"
#include "graphics/OpenGL/flGLTextureRenderTarget.h"

using namespace flEngine::Graphics;

#define flIMPL flPIMPL(OpenGL)

WindowRenderTarget* OpenGL::CreateWindowRenderTarget()
{
  return GLWindowRenderTarget::Create();
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

OpenGL::OpenGL(Platform::Window *pWindow)
{
  flIMPL->Construct(pWindow);
}

OpenGL* OpenGL::Create(Platform::Window *pWindow)
{
  return flNew OpenGL(pWindow);
}
