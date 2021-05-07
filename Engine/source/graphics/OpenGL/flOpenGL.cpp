#include "flOpenGL_Impl.h"
#include "graphics/OpenGL/flGLTexture2D.h"
#include "graphics/OpenGL/flGLGeometry.h"
#include "graphics/OpenGL/flGLProgram.h"
#include "graphics/OpenGL/flGLHardwareBuffer.h"
#include "graphics/OpenGL/flGLWindowRenderTarget.h"
#include "graphics/OpenGL/flGLTextureRenderTarget.h"

using namespace flEngine;
using namespace flEngine::Graphics;

flPIMPL_IMPL(OpenGL)

#define flIMPL flPIMPL(OpenGL)

void OpenGL::Render(flIN DrawMode drawMode, flIN bool indexed, flIN uint64_t elementOffset, flIN uint64_t elementCount)
{
  flIMPL->Render(drawMode, indexed, elementCount, elementCount);
}

OpenGL::OpenGL(flIN Platform::Window *pWindow, flIN const RenderTargetOptions *pOptions)
{
  flIMPL->Construct(pWindow, pOptions);
}

OpenGL* OpenGL::Create(flIN Platform::Window *pWindow, flIN const RenderTargetOptions *pOptions)
{
  return flNew OpenGL(pWindow, pOptions);
}

void OpenGL::SetGeometry(flIN Geometry *pGeometry, flIN int64_t indexBuffer)
{
  return flIMPL->SetGeometry(pGeometry, indexBuffer);
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

WindowRenderTarget* OpenGL::CreateWindowRenderTarget(flIN Platform::Window* pWindow, flIN RenderTargetOptions* pOptions)
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

HardwareBuffer* OpenGL::CreateBuffer(flIN BufferBinding binding, flIN AccessFlags accessFlags)
{
  return GLHardwareBuffer::Create(binding, accessFlags);
}

IndexBuffer* CreateIndexBuffer(flIN BufferBinding binding, flIN AccessFlags accessFlags)
{
  return GLIndexBuffer::Create(binding, accessFlags);
}

VertexBuffer* CreateVertexBuffer(flIN BufferBinding binding, flIN AccessFlags accessFlags)
{
  return GLVertexBuffer::Create(binding, accessFlags);
}

Program* OpenGL::CreateProgram()
{
  return GLProgram::Create();
}

Texture2D* OpenGL::CreateTexture2D(flIN DepthFormat depthFormat)
{
  return GLTexture2D::Create(depthFormat);
}

Texture2D* OpenGL::CreateTexture2D(flIN PixelFormat pixelFormat, flIN PixelComponentType type)
{
  return GLTexture2D::Create(pixelFormat, type);
}

Texture2D* CreateTexture2D(flIN DepthFormat depthFormat)
{
  return GLTexture2D::Create(depthFormat);
}

Texture2D* CreateTexture2D(flIN PixelFormat pixelFormat, flIN PixelComponentType type)
{
  return GLTexture2D::Create(pixelFormat, type);
}
