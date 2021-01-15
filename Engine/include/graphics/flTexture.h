#ifndef flTexture_h__
#define flTexture_h__

#include "../flInterface.h"

namespace flEngine
{
  namespace Graphics
  {
    class flEXPORT Texture : public Interface
    {
    public:
      virtual bool HasMipmaps() const = 0;

      virtual int64_t GetNumMimMaps() = 0;

      virtual int64_t GetDepth() const = 0;
      virtual int64_t GetWidth() const = 0;
      virtual int64_t GetHeight() const = 0;
    };
  }
}

#endif // flTexture_h__
