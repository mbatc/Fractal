#include "scene/flComponent.h"

namespace flEngine
{
  namespace Scene
  {
    int64_t Component::GetNextTypeID()
    {
      static int64_t typeID = 0;
      return typeID++;
    }
  }
}

