#include "flLight.h"

namespace Fractal
{
  class Impl_Light
  {
  public:
    LightType type     = LightType_Sun;
    Colour    colour   = ColourU32_White;
    double    strength = 1;
    double    falloff  = 1;
  };

  flPIMPL_IMPL(Light);

  void Light::SetLightType(flIN LightType type)
  {
    Impl()->type = type;
  }

  void Light::SetColour(flIN Colour colour)
  {
    Impl()->colour = colour;
  }

  void Light::SetStrength(flIN double strength)
  {
    Impl()->strength = strength;
  }

  void Light::SetFalloff(flIN double falloff)
  {
    Impl()->falloff = falloff;
  }

  LightType Light::GetLightType() const
  {
    return Impl()->type;
  }

  Colour Light::GetColour() const
  {
    return Impl()->colour;
  }

  double Light::GetStrength() const
  {
    return Impl()->strength;
  }

  double Light::GetFalloff() const
  {
    return Impl()->falloff;
  }
}
