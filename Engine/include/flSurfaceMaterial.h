#pragma once

#include "flInterface.h"
#include "math/flMath.h"
#include "util/flColour.h"

namespace flEngine
{
  class Impl_SurfaceMaterial;

  class flEXPORT SurfaceMaterial : public Interface
  {
    flPIMPL_DEF(SurfaceMaterial);
  public:
    static SurfaceMaterial * Create();

    char const * GetName() const;

    void SetName(flIN char const* name);

    float GetValue(flIN char const* name) const;

    Util::Colour GetColour(flIN char const * name) const;

    char const* GetTexture(flIN char const * name) const;

    void SetValue(flIN char const * name, flIN float value);

    void SetColour(flIN char const * name, flIN Util::Colour colour);

    void SetTexture(flIN char const *name, flIN char const *path);

    int64_t GetValueCount() const;
    
    int64_t GetColourCount() const;

    int64_t GetTextureCount() const;
  };
}
