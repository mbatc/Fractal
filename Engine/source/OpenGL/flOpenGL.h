#pragma once

#include "flAPI.h"
#include "flRef.h"

namespace Fractal
{
  namespace Impl
  {
    class GLDeviceState;

    class OpenGL : public API
    {
      FRACTAL_DEFAULT_INTERFACE;

    public:
      OpenGL(IWindow* pWindow, const RenderTargetOptions* pOptions);

      virtual DeviceState* GetState() override;
      virtual void Render(DrawMode drawMode, bool indexed, uint64_t elementOffset, uint64_t elementCount) override;

      virtual WindowRenderTarget* CreateWindowRenderTarget(IWindow* pWindow, RenderTargetOptions* pOptions) override;
      virtual TextureRenderTarget* CreateTextureRenderTarget() override;
      virtual VertexArray* CreateVertexArray() override;
      virtual HardwareBuffer* CreateBuffer(BufferBinding binding, BufferUsage bufferUsage) override;
      virtual IndexBuffer* CreateIndexBuffer(int64_t indexCount, uint32_t const* pValues, BufferUsage bufferUsage) override;
      virtual VertexBuffer* CreateVertexBuffer(int64_t size, void const* pInitialData, BufferUsage bufferUsage) override;
      virtual UniformBuffer* CreateUniformBuffer(int64_t size, void const* pInitialData, BufferUsage bufferUsage) override;
      virtual Program* CreateProgram() override;
      virtual ShaderMaterial* CreateMaterial(Program* pProgram, char const* materialBlock = "Material") override;

      virtual Texture2D* CreateTexture2D(DepthFormat depthFormat) override;
      virtual Texture2D* CreateTexture2D(PixelFormat pixelFormat, PixelComponentType type) override;
      virtual Sampler* CreateSampler() override;

      virtual IRenderMesh* CreateRenderMesh(flIN IMesh* pMesh) override;

      static bool RegisterAPI();

    private:
      GLDeviceState* m_pState = nullptr;

#if flUSING(flPLATFORM_WINDOWS)
      void* m_pGLRC = nullptr;
#endif
    };
  }
}
