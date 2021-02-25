#ifndef fl_Graphics_API_h__
#define fl_Graphics_API_h__

#include "../threads/flThreadQueue.h"
#include "../math/flMath.h"

#include "flPixelFormat.h"
#include "flBufferDetails.h"

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
       */
      virtual void SetGeometry(Geometry *pGeometry) = 0;

      /**
       * @brief Set the destination for the render.
       */
      virtual void SetRenderTarget(RenderTarget *pRenderTarget) = 0;

      /**
       * @brief Set the GPU program to render.
       */
      virtual void SetProgram(Program *pProgram) = 0;

      /**
      * @brief Get a pointer the the GPU's state interface.
      */
      virtual DeviceState* GetState() = 0;

      /**
       * @brief Execute a render command.
       */
      virtual void Render() = 0;

      /**
       * @brief Create a graphics render target for a window.
       *
       * @param [in] pWindow  A pointer to the Window to associate the render target with.
       * @param [in] pOptions The properties of the WindowRenderTarget to create.
       *
       * @return A pointer to a WindowRenderTarget instance.
       */
      virtual WindowRenderTarget* CreateWindowRenderTarget(flIN Platform::Window *pWindow, flIN RenderTargetOptions *pOptions) = 0;

      virtual TextureRenderTarget* CreateTextureRenderTarget() = 0;
      
      virtual Geometry* CreateGeometry() = 0;
      
      virtual HardwareBuffer* CreateBuffer(flIN BufferBinding type, flIN AccessFlags accessFlags) = 0;

      virtual Program* CreateProgram() = 0;

      virtual Texture2D* CreateTexture2D(flIN DepthFormat depthFormat) = 0;

      virtual Texture2D* CreateTexture2D(flIN PixelFormat pixelFormat, flIN PixelComponentType type) = 0;
    };
  }
}

#endif // fl_Graphics_API_h__
