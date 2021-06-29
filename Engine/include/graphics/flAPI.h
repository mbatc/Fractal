#ifndef fl_Graphics_API_h__
#define fl_Graphics_API_h__

#include "../threads/flThreadQueue.h"
#include "../math/flMath.h"
#include "../util/flType.h"
#include "flPixelFormat.h"
#include "flBufferDetails.h"
#include "flProgramDetails.h"

namespace flEngine
{
  namespace Platform { class Window; }

  namespace Graphics
  {
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
    class APIResource;

    struct PixelBufferDesc;
    struct RenderTargetOptions;

    class API;

    class flEXPORT APIFactory : public Interface
    {
    public:
      virtual char const * GetIdentifier() const = 0;
      virtual API * Create(Platform::Window *pWindow, RenderTargetOptions *pOptions) = 0;
    };

    class flEXPORT API : public Interface
    {
    public:
      /**
       * @brief Register a Graphics API implementation with the engine.
       * 
       * @param [in] identifier A unique identifier for the implementation.
       * @param [in] APIFactory A factory object that will create instances of the implementation.
       */
      static bool RegisterAPI(flIN APIFactory * pFactory);

      /**
       * @brief Get the number of APIs registered.
       */
      static int64_t GetAPICount();

      /**
       * @brief Get the string identifier for a graphics API.
       */
      static char const* GetAPIIdentifier(flIN int64_t index);

      /**
       * @brief Create a graphics API using it's string identifier
       */
      static API * Create(char const *apiIdentifier, Platform::Window *pWindow, RenderTargetOptions *pOptions = nullptr);

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
      virtual WindowRenderTarget* CreateWindowRenderTarget(flIN Platform::Window *pWindow, flIN RenderTargetOptions *pOptions) = 0;

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
      virtual VertexBuffer* CreateVertexBuffer(flIN int64_t size, flIN void const *pInitialData = nullptr, flIN BufferUsage bufferUsage = BufferUsage_Default) = 0;

      /**
       * @brief
       */
      virtual IndexBuffer* CreateIndexBuffer(flIN int64_t indexCount = 0, uint32_t const * pValues = nullptr, flIN BufferUsage bufferUsage = BufferUsage_Default) = 0;

      /**
       * @brief
       */
      virtual UniformBuffer * CreateUniformBuffer(flIN int64_t size, flIN void const *pInitialData = nullptr, flIN BufferUsage bufferUsage = BufferUsage_Default) = 0;

      /**
       * @brief
       */
      virtual Program* CreateProgram() = 0;

      /**
       * @brief
       */
      virtual ShaderMaterial * CreateMaterial(flIN Program *pProgram, flIN char const * materialBlock = "Material") = 0;

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
    };
  }
}

#endif // fl_Graphics_API_h__
