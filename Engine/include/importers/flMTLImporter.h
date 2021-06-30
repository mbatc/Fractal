#pragma once

#include "../flInterface.h"

namespace flEngine
{
  class SurfaceMaterial;

  class Impl_MTLImporter;

  class flEXPORT MTLImporter : public Interface
  {
    flPIMPL_DEF(MTLImporter);
  public:
    static MTLImporter * Create();

    bool Import(char const * path);


    int64_t GetMaterialCount();

    SurfaceMaterial * GetMaterial(flIN char const *name);

    SurfaceMaterial * GetMaterial(flIN int64_t index);
  };
}
