#ifndef fl_Graphics_GLWindowRenderTarget_h__
#define fl_Graphics_GLWindowRenderTarget_h__

#include "graphics/flWindowRenderTarget.h"
#include "platform/flWindow.h"

namespace flEngine
{
  namespace Graphics
  {
    class PixelBuffer;

    class GLWindowRenderTarget : public WindowRenderTarget
    {
    protected:
      GLWindowRenderTarget(flIN Platform::Window *pWindow, flIN const RenderTargetOptions *pOptions);

    public:
      ~GLWindowRenderTarget();

      static WindowRenderTarget* Create(flIN Platform::Window *pWindow, flIN const RenderTargetOptions *pOptions);

      /**
       * @brief Get the window associated with this render target.
       */
      Platform::Window* GetWindow() const override;

      /**
      * @brief Set the format of the render target.
      */
      bool SetFormat(flIN RenderTargetOptions const * pOptions) override;

      /**
      * @brief Clear this RenderTarget
      */
      void Clear(flIN Util::Colour colour = 0, flIN float depth = 1, flIN int32_t stencil = 0) override;

      /**
      * @brief Clear the depth component of this RenderTarget
      */
      void ClearDepth(flIN float depth = 1.0f) override;

      /**
      * @brief Clear the colour component of this RenderTarget
      */
      void ClearColour(flIN Util::Colour colour = 0) override;

      /**
      * @brief Clear the stencil component of this RenderTarget
      */
      void ClearStencil(flIN int32_t colour = 0) override;

      /**
      * @brief Present the back buffer to the window.
      */
      void Swap() override;

      /**
       * @brief Get the native handle to the Device Context
       */
      void* GetNativeHandle() const override;

      /**
       * @brief Make this the active render target.
       */
      void Bind() override;

    private:
      void MakeCurrent();

      Platform::Window *m_pWindow = nullptr;

#if flUSING(flPLATFORM_WINDOWS)
      void *m_hDC = nullptr;
      bool m_pixelFormatSet = false;
      RenderTargetOptions m_currentOptions;
#endif
    };
  }
}

#endif // fl_Graphics_RenderTarget_h__
