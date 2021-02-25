#ifndef fl_Graphics_OpenGL_h__
#define fl_Graphics_OpenGL_h__

#include "../flAPI.h"

namespace flEngine
{
  namespace Graphics
  {
    class flPIMPL_CLASS(OpenGL);

    class flEXPORT OpenGL : public API
    {
      flPIMPL_DEF(OpenGL);

    protected:
      OpenGL(flIN Platform::Window *pWindow, flIN const RenderTargetOptions *pOptions);

    public:
      /**
       * @brief Create an OpenGL API instance.
       */
      static OpenGL* Create(flIN Platform::Window *pWindow, flIN const RenderTargetOptions *pOptions = nullptr);

      /**
       * @brief Set the active geometry to be rendered.
       */
      virtual void SetGeometry(flIN Geometry *pGeometry) override;

      /**
       * @brief Set the destination for the render.
       */
      virtual void SetRenderTarget(flIN RenderTarget *pRenderTarget) override;

      /**
       * @brief Set the GPU program to render.
       */
      virtual void SetProgram(flIN Program *pProgram) override;

      /**
      * @brief Get a pointer the the GPU's state interface.
      */
      virtual DeviceState* GetState() override;

      /**
       * @brief Execute a render command.
       */
      virtual void Render() override;

      virtual WindowRenderTarget* CreateWindowRenderTarget(flIN Platform::Window *pWindow, flIN RenderTargetOptions *pOptions) override;

      virtual TextureRenderTarget* CreateTextureRenderTarget() override;

      virtual Geometry* CreateGeometry() override;

      virtual HardwareBuffer* CreateBuffer(flIN BufferBinding binding, flIN AccessFlags accessFlags) override;

      virtual Program* CreateProgram() override;

      virtual Texture2D* CreateTexture2D(flIN DepthFormat depthFormat) override;

      virtual Texture2D* CreateTexture2D(flIN PixelFormat pixelFormat, flIN PixelComponentType type) override;
    };
  }
}

#endif // fl_Graphics_API_h__
