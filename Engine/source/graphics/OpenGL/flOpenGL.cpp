#include "flOpenGL.h"
#include "flGLUtil.h"
#include "flGLProgram.h"
#include "flGLGeometry.h"
#include "flGLTexture2D.h"
#include "flGLHardwareBuffer.h"
#include "flGLVertexBuffer.h"
#include "flGLIndexBuffer.h"
#include "flGLTextureRenderTarget.h"
#include "flGLWindowRenderTarget.h"
#include "flGLDeviceState.h"

namespace flEngine
{
  namespace Graphics
  {
    void OpenGL::SetGeometry(Geometry * pGeometry, int64_t indexBuffer)
    {
      m_pGeometry = pGeometry;
      m_indexBuffer = indexBuffer;
    }

    void OpenGL::SetRenderTarget(RenderTarget * pRenderTarget)
    {
      bool updated = m_pRenderTarget != pRenderTarget;
      m_pRenderTarget = pRenderTarget;

      if (m_pRenderTarget)
        m_pRenderTarget->Bind();
    }

    void OpenGL::SetProgram(Program* pProgram)
    {
      bool updated = m_pProgram != pProgram;
      m_pProgram = pProgram;

      if (m_pProgram && updated)
        glUseProgram(flNativeToGLID(m_pProgram->GetNativeResource()));

      if (!m_pProgram)
        glUseProgram(0);
    }

    DeviceState* OpenGL::GetState() { return m_pState; }

    void OpenGL::Render(DrawMode drawMode, bool indexed, uint64_t elementOffset, uint64_t elementCount)
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

      VertexBuffer* pVertexBuffer = m_pGeometry->GetVertexBuffer(0);
      IndexBuffer* pIndexBuffer = m_pGeometry->GetIndexBuffer(m_indexBuffer);

      GLenum glType = GL_NONE;
      switch (pIndexBuffer->GetIndexType())
      {
      case Util::Type_UInt32: glType = GL_UNSIGNED_INT;   break;
      case Util::Type_UInt16: glType = GL_UNSIGNED_SHORT; break;
      case Util::Type_UInt8:  glType = GL_UNSIGNED_BYTE;  break;
      }

      if (indexed)
        glDrawElements(glDrawMode, (GLsizei)elementCount, glType, (void*)elementOffset);
      else
        glDrawArrays(glDrawMode, (GLsizei)elementOffset, (GLsizei)elementCount);
    }
    OpenGL* OpenGL::Create(Platform::Window* pWindow, const RenderTargetOptions* pOptions)
    {
      return flNew OpenGL(pWindow, pOptions);
    }

    WindowRenderTarget* OpenGL::CreateWindowRenderTarget(Platform::Window* pWindow, RenderTargetOptions* pOptions)
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

    HardwareBuffer* OpenGL::CreateBuffer(BufferBinding binding, AccessFlags accessFlags)
    {
      return GLHardwareBuffer::Create(binding, accessFlags);
    }

    IndexBuffer* OpenGL::CreateIndexBuffer(int64_t indexCount, uint32_t const* pValues)
    {
      return GLIndexBuffer::Create(indexCount, pValues);
    }

    VertexBuffer* OpenGL::CreateVertexBuffer(Util::Type primitiveType, int64_t primitiveWidth, int64_t elementCount, void const* pInitialData)
    {
      HardwareBuffer* pBuffer = CreateBuffer(BufferBinding_Vertices, AccessFlag_Write);
      VertexBuffer* pVertexBuffer = GLVertexBuffer::Create(pBuffer, primitiveType, primitiveWidth, elementCount, pInitialData);
      pBuffer->DecRef();
      return pVertexBuffer;
    }

    Program* OpenGL::CreateProgram()
    {
      return GLProgram::Create();
    }

    Texture2D* OpenGL::CreateTexture2D(DepthFormat depthFormat)
    {
      return GLTexture2D::Create(depthFormat);
    }

    Texture2D* OpenGL::CreateTexture2D(PixelFormat pixelFormat, PixelComponentType type)
    {
      return GLTexture2D::Create(pixelFormat, type);
    }

    Texture2D* CreateTexture2D(DepthFormat depthFormat)
    {
      return GLTexture2D::Create(depthFormat);
    }

    Texture2D* CreateTexture2D(PixelFormat pixelFormat, PixelComponentType type)
    {
      return GLTexture2D::Create(pixelFormat, type);
    }

    class GLAPIFactory : public APIFactory
    {
    public:
      char const * GetIdentifier() const override
      {
        return "OpenGL";
      }

      API *Create(Platform::Window *pWindow, RenderTargetOptions *pOptions) override
      {
        return OpenGL::Create(pWindow, pOptions);
      }
    };

    bool OpenGL::RegisterAPI()
    {
      GLAPIFactory *pFactory = new GLAPIFactory();
      bool success = API::RegisterAPI(pFactory);
      pFactory->DecRef();
      return success;
    }
  }
}
