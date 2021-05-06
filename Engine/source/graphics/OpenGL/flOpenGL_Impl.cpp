#include "flOpenGL_Impl.h"
#include "flGLUtil.h"
#include "graphics/OpenGL/flGLProgram.h"
#include "graphics/OpenGL/flGLGeometry.h"
#include "graphics/OpenGL/flGLHardwareBuffer.h"
#include "graphics/OpenGL/flGLTextureRenderTarget.h"
#include "graphics/OpenGL/flGLWindowRenderTarget.h"
#include "graphics/OpenGL/flGLDeviceState.h"

using namespace flEngine;
using namespace flEngine::Graphics;

void Impl_OpenGL::SetGeometry(Geometry *pGeometry, int64_t indexBuffer)
{
  m_pGeometry = pGeometry;
  m_indexBuffer = indexBuffer;
}

void Impl_OpenGL::SetRenderTarget(RenderTarget *pRenderTarget)
{
  m_pRenderTarget = pRenderTarget;
}

void Impl_OpenGL::SetProgram(Program *pProgram)
{
  m_pProgram = pProgram;
}

DeviceState* Impl_OpenGL::GetState() { return m_pState; }

void Impl_OpenGL::Render(DrawMode drawMode, bool indexed, uint64_t elementOffset, uint64_t elementCount)
{
  GLenum glDrawMode = GL_NONE;
  switch (drawMode)
  {
  case DrawMode_Patches:       glDrawMode = GL_PATCHES; break;
  case DrawMode_Points:        glDrawMode = GL_POINTS; break;
  case DrawMode_Lines:         glDrawMode = GL_LINES; break;
  case DrawMode_LineLoop:      glDrawMode = GL_LINE_LOOP; break;
  case DrawMode_Triangles:     glDrawMode = GL_TRIANGLES; break;
  case DrawMode_TriangleFan:   glDrawMode = GL_TRIANGLE_FAN; break;
  case DrawMode_TriangleStrip: glDrawMode = GL_TRIANGLE_STRIP; break;
  default: // TODO: Add some logging
    return;
  }

  IndexBuffer* pIndexBuffer = m_pGeometry->GetIndexBuffer(m_indexBuffer);
  VertexBuffer* pVertexBuffer = m_pGeometry->GetVertexBuffer(0);
  m_pProgram->GetNativeResource();
  if (indexed)
    glDrawElements(glDrawMode, elementCount, )
}
