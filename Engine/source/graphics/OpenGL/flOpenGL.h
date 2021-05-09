#ifndef fl_Graphics_OpenGL_h__
#define fl_Graphics_OpenGL_h__

#include "graphics/flAPI.h"
#include "util/flType.h"
#include "flRef.h"

namespace flEngine
{
  namespace Graphics
  {
    class GLDeviceState;

    class OpenGL : public API
    {
      OpenGL(Platform::Window* pWindow, const RenderTargetOptions* pOptions);

    public:
      static OpenGL* Create(Platform::Window* pWindow, const RenderTargetOptions* pOptions = nullptr);

      void SetGeometry(Geometry* pGeometry, int64_t indexBuffer) override;
      void SetRenderTarget(RenderTarget* pRenderTarget) override;
      void SetProgram(Program* pProgram) override;

      DeviceState* GetState() override;
      void Render(DrawMode drawMode, bool indexed, uint64_t elementOffset, uint64_t elementCount) override;
      WindowRenderTarget* CreateWindowRenderTarget(Platform::Window* pWindow, RenderTargetOptions* pOptions) override;
      TextureRenderTarget* CreateTextureRenderTarget() override;
      Geometry* CreateGeometry() override;
      HardwareBuffer* CreateBuffer(BufferBinding binding, AccessFlags accessFlags) override;
      IndexBuffer* CreateIndexBuffer(int64_t indexCount, uint32_t const* pValues) override;
      VertexBuffer* CreateVertexBuffer(Util::Type primitiveType, int64_t primitiveWidth, int64_t elementCount, void const* pInitialData) override;
      Program* CreateProgram() override;
      Texture2D* CreateTexture2D(DepthFormat depthFormat) override;
      Texture2D* CreateTexture2D(PixelFormat pixelFormat, PixelComponentType type) override;

      static bool RegisterAPI();

    private:
      GLDeviceState* m_pState = nullptr;

      // Active bindings
      Ref<Program>      m_pProgram = nullptr;
      Ref<Geometry>     m_pGeometry = nullptr;
      Ref<RenderTarget> m_pRenderTarget = nullptr;

      int64_t       m_indexBuffer = -1;
      Util::Type    m_indexType   = Util::Type_Unknown;
#if flUSING(flPLATFORM_WINDOWS)
      void* m_pGLRC = nullptr;
#endif
    };
  }
}

#endif // fl_Graphics_API_h__
