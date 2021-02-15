#include "flOpenGL_Impl.h"
#include "graphics/OpenGL/flGLGeometry.h"
#include "graphics/OpenGL/flGLIndexBuffer.h"
#include "graphics/OpenGL/flGLVertexBuffer.h"
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

WindowRenderTarget* OpenGL::CreateWindowRenderTarget(flIN Platform::Window *pWindow, flIN RenderTargetOptions *pOptions)
{
  return GLWindowRenderTarget::Create(pWindow, pOptions);
}

TextureRenderTarget* OpenGL::CreateTextureRenderTarget()
{
  return GLTextureRenderTarget::Create();
}

Geometry* OpenGL::CreateGeometry()
{
  return GLGeometry::Create();
}

IndexBuffer* OpenGL::CreateIndexBuffer(flIN AccessFlags accessFlags)
{
  return GLIndexBuffer::Create(accessFlags);
}

VertexBuffer* OpenGL::CreateVertexBuffer(flIN AccessFlags accessFlags)
{
  return GLVertexBuffer::Create(accessFlags);
}

Program* OpenGL::CreateProgram()
{
  return GLProgram::Create();
}

OpenGL::OpenGL(flIN Platform::Window *pWindow, flIN const RenderTargetOptions *pOptions)
{
  flIMPL->Construct(pWindow, pOptions);
}

OpenGL* OpenGL::Create(flIN Platform::Window *pWindow, flIN const RenderTargetOptions *pOptions)
{
  return flNew OpenGL(pWindow, pOptions);
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
