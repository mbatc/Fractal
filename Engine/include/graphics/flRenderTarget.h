#ifndef fl_Graphics_RenderTarget_h__
#define fl_Graphics_RenderTarget_h__

#include "../flInterface.h"
#include "flPixelFormat.h"

namespace flEngine
{
  namespace Graphics
  {
    class PixelBuffer;
    
    class flEXPORT RenderTarget : public Interface
    {
    public:
      /**
       * @brief Set the format of the render target.
       */
      virtual bool SetFormat(flIN PixelFormat colourFormat, flIN PixelComponentType pixelComponentType, flIN DepthFormat depthFormat) = 0;
    };
  }
}

#endif // fl_Graphics_RenderTarget_h__
