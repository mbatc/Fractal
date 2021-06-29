#pragma once

#include "../flPImpl.h"

namespace flEngine
{
  class Impl_OBJImporter;

  class Mesh;

  class flEXPORT OBJImporter
  {
    flPIMPL_DEF(OBJImporter);

  public:
    bool Import(flIN char const * filename);

    Mesh * GetResult();
  };
}
