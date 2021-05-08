#ifndef fl_Graphics_RenderTarget_h__
#define fl_Graphics_RenderTarget_h__

#include "../flInterface.h"
#include "../util/flColour.h"
#include "flPixelFormat.h"

namespace flEngine
{
  namespace Graphics
  {
    class PixelBuffer;

    struct RenderTargetOptions
    {
      // Colour format
      PixelComponentType pixelComponentType = PixelComponentType_UInt8;
      PixelFormat colourFormat = PixelFormat_RGBA;

      // Depth Format
      DepthFormat depthFormat = DepthFormat_Float24Stencil8;

      // Multi sampling
      int64_t sampleCount = 1;

      // Stereo 3D
      bool stereoBuffer = false;
    };

    class flEXPORT RenderTarget : public Interface
    {
    public:
      /**
       * @brief Set the format of the render target.
       */
      virtual bool SetFormat(flIN RenderTargetOptions const * pOptions) = 0;

      /**
       * @brief Clear this RenderTarget.
       */
      virtual void Clear(flIN Util::Colour colour = 0, flIN float depth = 1, flIN int32_t stencil = 0) = 0;

      /**
       * @brief Clear the depth component of this RenderTarget.
       */
      virtual void ClearDepth(flIN float depth = 1.0f) = 0;

      /**
       * @brief Clear the colour component of this RenderTarget.
       */
      virtual void ClearColour(flIN Util::Colour colour = 0) = 0;

      /**
       * @brief Clear the stencil component of this RenderTarget.
       */
      virtual void ClearStencil(flIN int32_t colour = 0) = 0;

      /**
       * @brief Make this the active render target.
       */
      virtual void Bind() = 0;
    };
  }
}

#endif // fl_Graphics_RenderTarget_h__
