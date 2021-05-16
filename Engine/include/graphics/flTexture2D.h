#ifndef fl_Graphics_Texture2D_h__
#define fl_Graphics_Texture2D_h__

#include "flTexture.h"
#include "../math/flMath.h"

namespace flEngine
{
  namespace Util { class Image; }
  namespace Graphics
  {
    class flEXPORT Texture2D : public Texture
    {
    protected:
      Texture2D(API *pAPI);

    public:
      bool SetFromImage(flIN Util::Image *pImage);
      bool DownloadImage(flOUT Util::Image *pImage);
    };
  }
}

#endif // fl_Graphics_Texture2D_h__
