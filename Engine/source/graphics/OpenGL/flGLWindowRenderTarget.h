#ifndef fl_Graphics_GLWindowRenderTarget_h__
#define fl_Graphics_GLWindowRenderTarget_h__

#include "graphics/flWindowRenderTarget.h"
#include "platform/flWindow.h"

namespace flEngine
{
  namespace Graphics
  {
    class PixelBuffer;

    class flPIMPL_CLASS(GLWindowRenderTarget);
    
    class flEXPORT GLWindowRenderTarget : public WindowRenderTarget
    {
      flPIMPL_DEF(GLWindowRenderTarget);

    protected:
      GLWindowRenderTarget(flIN Platform::Window *pWindow, flIN const RenderTargetOptions *pOptions);

    public:
      static GLWindowRenderTarget* Create(flIN Platform::Window *pWindow, flIN const RenderTargetOptions *pOptions);

      /**
       * @brief Get the window associated with this render target.
       */
      virtual Platform::Window* GetWindow() const override;

      /**
      * @brief Set the format of the render target.
      */
      virtual bool SetFormat(flIN const RenderTargetOptions *pOptions) override;

      /**
      * @brief Clear this RenderTarget
      */
      virtual void Clear(flIN const Util::Colour &colour = 0, flIN const float &depth = 1, flIN const int32_t &stencil = 0) override;

      /**
      * @brief Clear the depth component of this RenderTarget
      */
      virtual void ClearDepth(flIN const float &depth = 1.0f) override;

      /**
      * @brief Clear the colour component of this RenderTarget
      */
      virtual void ClearColour(flIN const Util::Colour &colour = 0) override;

      /**
      * @brief Clear the stencil component of this RenderTarget
      */
      virtual void ClearStencil(flIN const int32_t &colour = 0) override;

      /**
      * @brief Present the back buffer to the window.
      */
      virtual void Swap() override;

      /**
       * @brief Get the native handle to the Device Context
       */
      virtual void* GetNativeHandle() const override;

      /**
       * @brief Make this the active render target.
       */
      virtual void Bind() override;
    };
  }
}

#endif // fl_Graphics_RenderTarget_h__
