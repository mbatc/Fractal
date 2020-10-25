#ifndef flGraphics_h__
#define flGraphics_h__

#include "../utility/flConfig.h"
#include "../utility/flMath.h"

namespace flEngine
{
  namespace Graphics
  {
    class API;

    class flEXPORT Buffer
    {
    public:
      /**
       * Resize the buffer.
       */
      virtual void Resize(const int64_t &size) = 0;

      /**
       * Map the buffer to client memory. This function will return a pointer to the mapped memory.
       */
      virtual void *Map() = 0;

      /**
       * Release the mapped buffer pointer.
       */
      virtual void Unmap() = 0;
    };
  };
};

#endif // flGraphics_h__
