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
#include "flGLSampler.h"

namespace flEngine
{
  namespace Graphics
  {
    void OpenGL::SetGeometry(Geometry* pGeometry, int64_t indexBuffer)
    {
      bool updated = m_pGeometry != pGeometry || m_indexBuffer != indexBuffer;
      m_pGeometry = pGeometry;
      m_indexBuffer = indexBuffer;

      if (m_pGeometry && updated)
      {
        uint32_t* pVAOs = (uint32_t*)m_pGeometry->GetNativeResource();
        uint32_t vaoToBind = pVAOs[0];

        if (m_indexBuffer >= 0 && m_indexBuffer < m_pGeometry->GetIndexBufferCount())
        {
          vaoToBind = pVAOs[m_indexBuffer];
          m_indexType = m_pGeometry->GetIndexBuffer(m_indexBuffer)->GetIndexType();
        }
        else
        {
          m_indexBuffer = -1;
        }
        glBindVertexArray(vaoToBind);
      }

      if (!m_pGeometry)
        glBindVertexArray(0);
    }

    void OpenGL::SetRenderTarget(RenderTarget* pRenderTarget)
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
      {
        // Make sure the shader is compiled
        if (!m_pProgram->Compile())
        { // Clear the program if the shader failed to compile
          SetProgram(nullptr);
          return;
        }

        // Bind the shader program
        glUseProgram(flNativeToGLID(m_pProgram->GetNativeResource()));

      }

      if (!m_pProgram)
        glUseProgram(0);
    }

    DeviceState* OpenGL::GetState() { return m_pState; }

    void OpenGL::Render(DrawMode drawMode, bool indexed, uint64_t elementOffset, uint64_t elementCount)
    {
      if (m_pProgram  == nullptr) return; // TODO: Report error
      if (m_pGeometry == nullptr) return; // TODO: Report error
      if (m_pProgram  == nullptr) return; // TODO: Report error

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

      // Update the active geometry
      if (m_pGeometry->Update())
      { // If it was update, we need to rebind the correct VAO
        Geometry* pPrev = m_pGeometry.Get();
        m_pGeometry = nullptr;
        SetGeometry(pPrev, m_indexBuffer);
      }

      m_pProgram->ApplyInputs();

      if (indexed && m_indexBuffer != -1)
      {
        // Render using an index buffer
        GLenum glType = GL_NONE;
        switch (m_indexType)
        {
        case Util::Type_UInt32: glType = GL_UNSIGNED_INT;   break;
        case Util::Type_UInt16: glType = GL_UNSIGNED_SHORT; break;
        case Util::Type_UInt8:  glType = GL_UNSIGNED_BYTE;  break;
        }

        elementCount = ctMin(m_pGeometry->GetIndexCount(m_indexBuffer), elementCount);
        glDrawElements(glDrawMode, (GLsizei)elementCount, glType, (void*)elementOffset);
      }
      else
      {
        // No index buffer, draw arrays directly
        elementCount = ctMin(m_pGeometry->GetVertexCount(), elementCount);
        glDrawArrays(glDrawMode, (GLsizei)elementOffset, (GLsizei)elementCount);
      }
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
      HardwareBuffer* pBuffer = CreateBuffer(BufferBinding_Indices, AccessFlag_Write);
      IndexBuffer* pIndexBuffer = GLIndexBuffer::Create(pBuffer, indexCount, pValues);
      pBuffer->DecRef();
      return pIndexBuffer;
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

    Sampler *OpenGL::CreateSampler()
    {
      return GLSampler::Create();
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
      char const* GetIdentifier() const override
      {
        return "OpenGL";
      }

      API* Create(Platform::Window* pWindow, RenderTargetOptions* pOptions) override
      {
        return OpenGL::Create(pWindow, pOptions);
      }
    };

    bool OpenGL::RegisterAPI()
    {
      GLAPIFactory* pFactory = new GLAPIFactory();
      bool success = API::RegisterAPI(pFactory);
      pFactory->DecRef();
      return success;
    }
  }
}
