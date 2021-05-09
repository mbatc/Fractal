#ifndef flGLAttributeCache_h__
#define flGLAttributeCache_h__

#include "ctString.h"

namespace flEngine
{
  namespace Graphics
  {
    /**
     * @brief GLAttributeCache is used to store and distribute attribute locations
     * 
     * This ensures that shaders have common attribute locations for inputs with the
     * same name.
     * 
     * This allows the same geometry to be used by mutliple shaders, without needing
     * to rebind vertex buffers to different locations.
     */
    class GLAttributeCache
    {
    public:
      /**
       * @brief Add a known attribute location to the cache.
       */
      static bool AddLocation(ctString const & name, uint32_t location);

      /**
       * @brief Get the names of all know attributes.
       */
      static ctVector<ctString> GetNames();

      /**
       * @brief Get the location of a known attribute.
       * 
       * If the attribute is not know, -1 is returned.
       */
      static int32_t GetLocation(ctString const & name);

      /**
       * @brief A counter that is incremented when the GLAttributeCache changes.
       */
      static int64_t GetChangeRound();
    };
  }
}

#endif // flGLAttributeCache_h__