#ifndef fl_Graphics_RenderTarget_h__
#define fl_Graphics_RenderTarget_h__

#include "../flInterface.h"
#include "flPixelFormat.h"

namespace flEngine
{
  namespace Graphics
  {
    class PixelBuffer;

    struct RenderTargetOptions
    {
      // Pixel format
      PixelFormat colourFormat;
      DepthFormat depthFormat;
      PixelComponentType pixelComponentType;

      // Multi sampling
      int64_t sampleCount;
      int64_t sampleQuality;
    };

    class flEXPORT RenderTarget : public Interface
    {
    public:
      /**
       * @brief Set the format of the render target.
       */
      virtual bool SetFormat(flIN RenderTargetOptions *pOptions) = 0;
    };
  }
}

#endif // fl_Graphics_RenderTarget_h__
