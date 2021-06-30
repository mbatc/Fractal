#pragma once

#include "../flInterface.h"

namespace flEngine
{
  class Impl_OBJImporter;

  class Mesh;

  class flEXPORT OBJImporter : public Interface
  {
    flPIMPL_DEF(OBJImporter);

  public:
    bool Import(flIN char const * filename);

    Mesh * GetResult();
  };
}
