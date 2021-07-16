#pragma once

#include "flThreadQueue.h"
#include "flMath.h"
#include "flType.h"
#include "flPixelFormat.h"
#include "flBufferDetails.h"
#include "flProgramDetails.h"

namespace Fractal
{
  class IMesh;
  class IWindow;

  class DeviceState;
  class HardwareBuffer;
  class VertexBuffer;
  class IndexBuffer;
  class UniformBuffer;
  class Texture;
  class Texture2D;
  class VertexArray;
  class RenderTarget;
  class WindowRenderTarget;
  class TextureRenderTarget;
  class Program;
  class Sampler;
  class ShaderMaterial;
  class IRenderMesh;
  class APIResource;

  struct PixelBufferDesc;
  struct RenderTargetOptions;

  class API;

  class flEXPORT APIFactory : public Interface
  {
  public:
    virtual char const* GetIdentifier() const = 0;

    virtual API* Create(IWindow* pWindow, RenderTargetOptions* pOptions) = 0;
  };

  class flEXPORT API : public Interface
  {
  public:
    /**
    * @brief Get a pointer the the GPU's state interface.
    */
    virtual DeviceState* GetState() = 0;

    /**
     * @brief Execute a render command.
     */
    virtual void Render(flIN DrawMode drawMode, bool indexed, uint64_t elementOffset = 0, uint64_t elementCount = INT64_MAX) = 0;

    /**
     * @brief Create a graphics render target for a window.
     *
     * @param [in] pWindow  A pointer to the Window to associate the render target with.
     * @param [in] pOptions The properties of the WindowRenderTarget to create.
     *
     * @return A pointer to a WindowRenderTarget instance.
     */
    virtual WindowRenderTarget* CreateWindowRenderTarget(flIN IWindow* pWindow, flIN RenderTargetOptions* pOptions) = 0;

    /**
     * @brief
     */
    virtual TextureRenderTarget* CreateTextureRenderTarget() = 0;

    /**
     * @brief
     */
    virtual VertexArray* CreateVertexArray() = 0;

    /**
     * @brief
     */
    virtual HardwareBuffer* CreateBuffer(flIN BufferBinding type, flIN BufferUsage bufferUsage) = 0;

    /**
     * @brief
     */
    virtual VertexBuffer* CreateVertexBuffer(flIN int64_t size, flIN void const* pInitialData = nullptr, flIN BufferUsage bufferUsage = BufferUsage_Default) = 0;

    /**
     * @brief
     */
    virtual IndexBuffer* CreateIndexBuffer(flIN int64_t indexCount = 0, uint32_t const* pValues = nullptr, flIN BufferUsage bufferUsage = BufferUsage_Default) = 0;

    /**
     * @brief
     */
    virtual UniformBuffer* CreateUniformBuffer(flIN int64_t size, flIN void const* pInitialData = nullptr, flIN BufferUsage bufferUsage = BufferUsage_Default) = 0;

    /**
     * @brief
     */
    virtual Program* CreateProgram() = 0;

    /**
     * @brief
     */
    virtual ShaderMaterial* CreateMaterial(flIN Program* pProgram, flIN char const* materialBlock = "Material") = 0;

    /**
     * @brief
     */
    virtual Texture2D* CreateTexture2D(flIN DepthFormat depthFormat) = 0;

    /**
     * @brief
     */
    virtual Texture2D* CreateTexture2D(flIN PixelFormat pixelFormat = PixelFormat_RGBA, flIN PixelComponentType type = PixelComponentType_UNorm8) = 0;

    /**
     * @brief
     */
    virtual Sampler* CreateSampler() = 0;

    /**
     * @brief
     */
    virtual IRenderMesh* CreateRenderMesh(flIN IMesh* pMesh) = 0;
  };
}

extern "C" {
  /**
   * @brief Register a Graphics API implementation with the engine.
   *
   * @param [in] pFactory A factory object that will create instances of the implementation.
   */
  flEXPORT bool Fractal_RegisterAPI(flIN Fractal::APIFactory* pFactory);

  /**
   * @brief Get the number of APIs registered.
   */
  flEXPORT int64_t Fractal_GetAPICount();

  /**
   * @brief Get the string identifier for a graphics API.
   */
  flEXPORT char const* Fractal_GetAPIIdentifier(flIN int64_t index);

  /**
   * @brief Create a graphics API using it's string identifier
   */
  flEXPORT Fractal::API* Fractal_CreateAPI(char const* apiIdentifier, Fractal::IWindow* pWindow, Fractal::RenderTargetOptions* pOptions = nullptr);
}
