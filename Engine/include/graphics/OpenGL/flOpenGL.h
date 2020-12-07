#ifndef fl_Graphics_OpenGL_h__
#define fl_Graphics_OpenGL_h__

#include "../flAPI.h"
#include "../../platform/flWindow.h"

namespace flEngine
{
  namespace Graphics
  {
    class flPIMPL_CLASS(OpenGL);

    class flEXPORT OpenGL : public API
    {
      flPIMPL_DEF(OpenGL);

    protected:
      OpenGL(Platform::Window * pWindow);

    public:
      /**
       * @brief Create an OpenGL API instance.
       */
      static OpenGL* Create(Platform::Window *pWindow);

      /**
       * @brief Set the active geometry to be rendered.
       */
      virtual void SetGeometry(Geometry *pGeometry) override;

      /**
       * @brief Set the destination for the render.
       */
      virtual void SetRenderTarget(RenderTarget *pRenderTarget) override;

      /**
       * @brief Set the GPU program to render.
       */
      virtual void SetProgram(Program *pProgram) override;

      /**
      * @brief Get a pointer the the GPU's state interface.
      */
      virtual DeviceState* GetState() override;

      /**
       * @brief Execute a render command.
       */
      virtual void Render() override;

      virtual WindowRenderTarget* CreateWindowRenderTarget() override;

      virtual TextureRenderTarget* CreateTextureRenderTarget() override;

      virtual Geometry* CreateGeometry() override;

      virtual IndexBuffer* CreateIndexBuffer() override;

      virtual VertexBuffer* CreateVertexBuffer() override;

      virtual PixelBuffer* CreatePixelBuffer() override;

      virtual Program* CreateProgram() override;
    };
  }
}

#endif // fl_Graphics_API_h__
