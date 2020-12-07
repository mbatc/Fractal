#ifndef fl_Graphics_GLWindowRenderTarget_h__
#define fl_Graphics_GLWindowRenderTarget_h__

#include "../flWindowRenderTarget.h"
#include "../../platform/flWindow.h"

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
      GLWindowRenderTarget(flIN Platform::Window *pWindow, flIN PixelFormat colourFormat, flIN PixelComponentType pixelComponentType, flIN DepthFormat depthFormat);

    public:
      static GLWindowRenderTarget* Create(flIN Platform::Window *pWindow, flIN PixelFormat colourFormat, flIN PixelComponentType pixelComponentType, flIN DepthFormat depthFormat);

      /**
       * @brief Get the window associated with this render target.
       */
      Platform::Window* GetWindow() const;

      /**
      * @brief Set the format of the render target.
      */
      virtual bool SetFormat(flIN PixelFormat colourFormat, flIN PixelComponentType pixelComponentType, flIN DepthFormat depthFormat) override;
    };
  }
}

#endif // fl_Graphics_RenderTarget_h__
