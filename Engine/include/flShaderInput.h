#pragma once

#include "flConfig.h"
#include <string>

namespace Fractal
{
  class flEXPORT ShaderInput
  {
  public:
    static inline std::string ValueName(flIN char const* name)
    {
      return std::string(name) + "0";
    }

    static inline std::string ColourName(flIN char const* name)
    {
      return std::string(name) + "Colour0";
    }

    static inline std::string TextureName(flIN char const* name)
    {
      return std::string(name) + "Map0";
    }
  };
}
