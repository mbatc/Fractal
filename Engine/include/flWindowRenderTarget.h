#pragma once

#include "flRenderTarget.h"

namespace Fractal
{
  class Window;

  class PixelBuffer;


  class flEXPORT WindowRenderTarget : public RenderTarget
  {
  protected:
    WindowRenderTarget(API* pAPI);

  public:
    /**
    * @brief Get the window associated with this render target.
    */
    virtual Window* GetWindow() const = 0;

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
