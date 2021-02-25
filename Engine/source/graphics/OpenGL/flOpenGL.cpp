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

HardwareBuffer* OpenGL::CreateBuffer(flIN BufferBinding binding, flIN AccessFlags accessFlags)
{
  return GLHardwareBuffer::Create(binding, accessFlags);
}

Program* OpenGL::CreateProgram()
{
  return GLProgram::Create();
}

Texture2D* CreateTexture2D(flIN DepthFormat depthFormat)
{
  return GLTexture2D::Create(depthFormat);
}

Texture2D* CreateTexture2D(flIN PixelFormat pixelFormat, flIN PixelComponentType type)
{
  return GLTexture2D::Create(pixelFormat, type);
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
