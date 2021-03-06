#pragma once

#include "flInterface.h"
#include "flColour.h"
#include "flPixelFormat.h"
#include "flAPIResource.h"

namespace Fractal
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

    // Width and height of a texture render target
    int64_t width  = -1;
    int64_t height = -1;
  };

  class flEXPORT RenderTarget : public APIResource
  {
  protected:
    RenderTarget(API* pAPI);

  public:
    /**
     * @brief Set the format of the RenderTarget.
     */
    virtual bool SetFormat(flIN RenderTargetOptions const* pOptions) = 0;

    /**
     * @brief Get the width of the RenderTarget in pixels.
     */
    virtual int64_t GetWidth() const = 0;

    /**
     * @brief Get the height of the RenderTarget in pixels.
     */
    virtual int64_t GetHeight() const = 0;

    /**
     * @brief Clear this RenderTarget.
     */
    virtual void Clear(flIN Colour colour = 0, flIN float depth = 1, flIN int32_t stencil = 0) = 0;

    /**
     * @brief Clear the depth component of this RenderTarget.
     */
    virtual void ClearDepth(flIN float depth = 1.0f) = 0;

    /**
     * @brief Clear the colour component of this RenderTarget.
     */
    virtual void ClearColour(flIN Colour colour = 0) = 0;

    /**
     * @brief Clear the stencil component of this RenderTarget.
     */
    virtual void ClearStencil(flIN int32_t colour = 0) = 0;

    /**
     * @brief Make this the active render target.
     */
    virtual void Bind(flIN bool read = true, flIN bool draw = true) = 0;

    /**
     * @brief Get the native resource for
     */
    virtual void* GetNativeResource() const = 0;
  };
}
