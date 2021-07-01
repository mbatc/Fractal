#include "flTexture2D.h"
#include "flImage.h"

namespace Fractal
{
    Texture2D::Texture2D(API *pAPI)
      : Texture(pAPI)
    {}

    bool Texture2D::SetFromImage(flIN Image *pImage)
    {
      // Create the pixel buffer description for this image
      PixelBufferDesc desc;
      CreatePixelBufferDesc(&desc, PixelFormat_RGBA, PixelComponentType_UNorm8, pImage->GetWidth(), pImage->GetHeight());

      // Set the texture using the image data
      return Set(pImage->GetPixels(), &desc);
    }

    bool Texture2D::DownloadImage(flOUT Image *pImage)
    {
      bool success = false;

      // Set the requested pixel buffer description for the image
      void *pData = nullptr;
      PixelBufferDesc desc;
      CreatePixelBufferDesc(&desc, PixelFormat_RGBA, PixelComponentType_UNorm8, -1, -1, -1);

      // Download the texture data into a buffer.
      if (Download(&pData, &desc, 0))
      { // Set the image data to the download pixels (this takes ownership)
        pImage->SetData((ColourU32 *)pData, desc.width, desc.height);
        success = true;
      }

      return success;
    }
}
