#pragma once

#include "flTexture.h"

namespace Fractal
{
  class Image;

    class flEXPORT Texture2D : public Texture
    {
    protected:
      Texture2D(API *pAPI);

    public:
      bool SetFromImage(flIN Image *pImage);
      bool DownloadImage(flOUT Image *pImage);
    };
}
