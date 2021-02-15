#include "flOpenGL_Impl.h"
#include "graphics/OpenGL/flGLProgram.h"
#include "graphics/OpenGL/flGLGeometry.h"
#include "graphics/OpenGL/flGLIndexBuffer.h"
#include "graphics/OpenGL/flGLVertexBuffer.h"
#include "graphics/OpenGL/flGLUniformBuffer.h"
#include "graphics/OpenGL/flGLTextureRenderTarget.h"
#include "graphics/OpenGL/flGLWindowRenderTarget.h"
#include "graphics/OpenGL/flGLDeviceState.h"

using namespace flEngine;
using namespace flEngine::Graphics;

void Impl_OpenGL::SetGeometry(Geometry* pGeometry)
{
  m_pGeometry = pGeometry;
}

void Impl_OpenGL::SetRenderTarget(RenderTarget* pRenderTarget)
{
  m_pRenderTarget = pRenderTarget;
}

void Impl_OpenGL::SetProgram(Program* pProgram)
{
  m_pProgram = pProgram;
}

DeviceState* Impl_OpenGL::GetState() { return m_pState; }

void Impl_OpenGL::Render()
{
}
