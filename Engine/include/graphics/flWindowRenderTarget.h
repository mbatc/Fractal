#ifndef fl_Graphics_WindowRenderTarget_h__
#define fl_Graphics_WindowRenderTarget_h__

#include "flRenderTarget.h"

namespace flEngine
{
  namespace Platform { class Window; }

  namespace Graphics
  {
    class PixelBuffer;


    class flEXPORT WindowRenderTarget : public RenderTarget
    {
    protected:
      WindowRenderTarget(API *pAPI);

    public:
      /**
      * @brief Get the window associated with this render target.
      */
      virtual Platform::Window* GetWindow() const = 0;

      /**
       * @brief Present the back buffer to the window.
       */
      virtual void Swap() = 0;

      /**
       * @brief Get the native handle to the Device Context
       */
      virtual void* GetNativeResource() const = 0;
    };
  }
}

#endif // fl_Graphics_RenderTarget_h__
