#include "flLight.h"

namespace Fractal
{
  class Impl_Light
  {
  public:
    LightType type     = LightType_Sun;
    Colour    diffuse  = ColourU32_White;
    Colour    ambient  = ColourU32_White;
    double    strength = 1;
    double    falloff  = 1;
    double    innerConeAngle = ctDegs2Rads(25);
    double    outerConeAngle = ctDegs2Rads(30);
  };

  flPIMPL_IMPL(Light);

  void Light::SetLightType(flIN LightType type)
  {
    Impl()->type = type;
  }

  void Light::SetDiffuse(flIN Colour colour)
  {
    Impl()->diffuse = colour;
  }

  void Light::SetAmbient(flIN Colour colour)
  {
    Impl()->ambient = colour;
  }

  void Light::SetStrength(flIN double strength)
  {
    Impl()->strength = strength;
  }

  void Light::SetFalloff(flIN double falloff)
  {
    Impl()->falloff = falloff;
  }

  void Light::SetInnerConeAngle(flIN double angleRads)
  {
    Impl()->innerConeAngle = angleRads;
  }

  void Light::SetOuterConeAngle(flIN double angleRads)
  {
    Impl()->outerConeAngle = angleRads;
  }

  LightType Light::GetLightType() const
  {
    return Impl()->type;
  }

  Colour Light::GetDiffuse() const
  {
    return Impl()->diffuse;
  }

  Colour Light::GetAmbient() const
  {
    return Impl()->ambient;
  }

  double Light::GetStrength() const
  {
    return Impl()->strength;
  }

  double Light::GetFalloff() const
  {
    return Impl()->falloff;
  }

  double Light::GetInnerConeAngle() const
  {
    return Impl()->innerConeAngle;
  }

  double Light::GetOuterConeAngle() const
  {
    return Impl()->outerConeAngle;
  }
}
