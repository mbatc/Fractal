#ifndef fl_Graphics_API_h__
#define fl_Graphics_API_h__

#include "../threads/flThreadQueue.h"
#include "../math/flMath.h"

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
    class Texture2D;
    class Geometry;
    class RenderTarget;
    class WindowRenderTarget;
    class TextureRenderTarget;
    class Program;

    struct PixelBufferDesc;
    struct RenderTargetOptions;

    class flEXPORT API : public Interface
    {
    public:
      /**
       * @brief Set the active geometry to be rendered.
       *
       * @param [in] pGeometry
       * @param [in] indexBuffer
       */
      virtual void SetGeometry(flIN Geometry *pGeometry, flIN int64_t indexBuffer = 0) = 0;

      /**
       * @brief Set the GPU program to render.
       *
       * @param [in] pProgram
       */
      virtual void SetProgram(flIN Program *pProgram) = 0;

      /**
       * @brief Set the destination for the render.
       * 
       * @param [in] pRenderTarget
       */
      virtual void SetRenderTarget(flIN RenderTarget *pRenderTarget) = 0;

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
      virtual Geometry* CreateGeometry() = 0;

      /**
       * @brief
       */
      virtual HardwareBuffer* CreateBuffer(flIN BufferBinding type, flIN AccessFlags accessFlags) = 0;

      /**
       * @brief
       */
      virtual Program* CreateProgram() = 0;

      /**
       * @brief
       */
      virtual Texture2D* CreateTexture2D(flIN DepthFormat depthFormat) = 0;

      /**
       * @brief
       */
      virtual Texture2D* CreateTexture2D(flIN PixelFormat pixelFormat, flIN PixelComponentType type) = 0;
    };
  }
}

#endif // fl_Graphics_API_h__
