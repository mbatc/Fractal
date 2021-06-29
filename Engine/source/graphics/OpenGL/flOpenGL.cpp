#include "flLog.h"
#include "flOpenGL.h"
#include "flGLUtil.h"
#include "flGLProgram.h"
#include "flGLVertexArray.h"
#include "flGLTexture2D.h"
#include "flGLHardwareBuffer.h"
#include "flGLVertexBuffer.h"
#include "flGLIndexBuffer.h"
#include "flGLTextureRenderTarget.h"
#include "flGLWindowRenderTarget.h"
#include "flGLDeviceState.h"
#include "flGLSampler.h"
#include "flGLUniformBuffer.h"
#include "flGLShaderMaterial.h"

namespace flEngine
{
  namespace Graphics
  {
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

      if (indexed)
        flVerifyGL(glDrawElements, glDrawMode, (GLsizei)elementCount, GL_UNSIGNED_INT, (void*)(elementOffset * sizeof(uint32_t)));
      else
        flVerifyGL(glDrawArrays, glDrawMode, (GLsizei)elementOffset, (GLsizei)elementCount);
    }

    OpenGL* OpenGL::Create(Platform::Window* pWindow, const RenderTargetOptions* pOptions)
    {
      return flNew OpenGL(pWindow, pOptions);
    }

    WindowRenderTarget* OpenGL::CreateWindowRenderTarget(Platform::Window* pWindow, RenderTargetOptions* pOptions)
    {
      return GLWindowRenderTarget::Create(this, pWindow, pOptions);
    }

    TextureRenderTarget* OpenGL::CreateTextureRenderTarget()
    {
      return GLTextureRenderTarget::Create(this);
    }

    VertexArray* OpenGL::CreateVertexArray()
    {
      return GLVertexArray::Create(this);
    }

    HardwareBuffer* OpenGL::CreateBuffer(BufferBinding binding, BufferUsage bufferUsage)
    {
      return GLHardwareBuffer::Create(this, binding, bufferUsage);
    }

    IndexBuffer* OpenGL::CreateIndexBuffer(int64_t indexCount, uint32_t const* pValues, BufferUsage bufferUsage)
    {
      return GLIndexBuffer::Create(this, indexCount, pValues, bufferUsage);
    }

    VertexBuffer* OpenGL::CreateVertexBuffer(int64_t size, void const* pInitialData, BufferUsage bufferUsage)
    {
      return GLVertexBuffer::Create(this, size, pInitialData, bufferUsage);
    }

    UniformBuffer *OpenGL::CreateUniformBuffer(int64_t size, void const *pInitialData, BufferUsage bufferUsage)
    {
      return GLUniformBuffer::Create(this, size, pInitialData, bufferUsage);
    }

    Program* OpenGL::CreateProgram()
    {
      return GLProgram::Create(this);
    }

    ShaderMaterial *OpenGL::CreateMaterial(flIN Program *pProgram, flIN char const *materialBlockName)
    {
      return GLShaderMaterial::Create(this, pProgram, materialBlockName);
    }

    Texture2D* OpenGL::CreateTexture2D(DepthFormat depthFormat)
    {
      return GLTexture2D::Create(this, depthFormat);
    }

    Texture2D* OpenGL::CreateTexture2D(PixelFormat pixelFormat, PixelComponentType type)
    {
      return GLTexture2D::Create(this, pixelFormat, type);
    }

    Sampler *OpenGL::CreateSampler()
    {
      return GLSampler::Create(this);
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
