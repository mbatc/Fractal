#ifndef fl_Graphics_OpenGL_h__
#define fl_Graphics_OpenGL_h__

#include "graphics/flAPI.h"
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

      DeviceState* GetState() override;

      void Render(DrawMode drawMode, bool indexed, uint64_t elementOffset, uint64_t elementCount) override;

      WindowRenderTarget* CreateWindowRenderTarget(Platform::Window* pWindow, RenderTargetOptions* pOptions) override;
      TextureRenderTarget* CreateTextureRenderTarget() override;
      VertexArray* CreateVertexArray() override;
      HardwareBuffer* CreateBuffer(BufferBinding binding, BufferUsage bufferUsage) override;
      IndexBuffer* CreateIndexBuffer(int64_t indexCount, uint32_t const* pValues, BufferUsage bufferUsage) override;
      VertexBuffer* CreateVertexBuffer(int64_t size, void const* pInitialData, BufferUsage bufferUsage) override;
      UniformBuffer* CreateUniformBuffer(int64_t size, void const *pInitialData, BufferUsage bufferUsage) override;
      Program* CreateProgram() override;
      ShaderMaterial* CreateMaterial(Program *pProgram, char const *materialBlock = "Material") override;

      Texture2D* CreateTexture2D(DepthFormat depthFormat) override;
      Texture2D* CreateTexture2D(PixelFormat pixelFormat, PixelComponentType type) override;
      Sampler* CreateSampler() override;

      static bool RegisterAPI();

    private:
      GLDeviceState* m_pState = nullptr;

#if flUSING(flPLATFORM_WINDOWS)
      void* m_pGLRC = nullptr;
#endif
    };
  }
}

#endif // fl_Graphics_API_h__
