#pragma once

#include "flRenderTarget.h"

namespace Fractal
{
  class Texture2D;
  class PixelBuffer;

  class flEXPORT TextureRenderTarget : public RenderTarget
  {
  protected:
    TextureRenderTarget(API* pAPI);

  public:
    /**
     * @brief Get a pointer to the colour target texture.
     */
    virtual Texture2D* GetColourTarget() = 0;

    /**
     * @brief Get a pointer to the depth target texture.
     */
    virtual Texture2D* GetDepthTarget() = 0;
  };
}
