#include "ctHashMap.h"
#include "flGLAttributeCache.h"

namespace flEngine
{
  namespace Graphics
  {
    static ctHashMap<ctString, uint32_t> g_layoutLocation;
    static int64_t g_changeRound = 0;

    bool GLAttributeCache::AddLocation(ctString const& name, uint32_t location)
    {
      if (g_layoutLocation.Contains(name))
        return false;

      g_layoutLocation.Add(name, location);
      ++g_changeRound;
      return true;
    }

    ctVector<ctString> GLAttributeCache::GetNames()
    {
      return g_layoutLocation.GetKeys();
    }

    int32_t GLAttributeCache::GetLocation(ctString const& name)
    {
      return g_layoutLocation.GetOr(name, -1);
    }

    int64_t GLAttributeCache::GetChangeRound()
    {
      return g_changeRound;
    }
  }
}
