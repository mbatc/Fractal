#pragma once

#include "flComponent.h"
#include "flColour.h"

namespace Fractal
{
  enum LightType
  {
    LightType_Sun,
    LightType_Point,
    LightType_Spot,
    LightType_Count,
  };

  class Impl_Light;

  class flEXPORT Light : public Component
  {
    FL_IMPLEMENT_COMPONENT(Light, "Light", Component);

    flPIMPL_DEF(Light);

  public:
    void SetLightType(flIN LightType type);

    void SetDiffuse(flIN Colour colour);

    void SetAmbient(flIN Colour colour);

    void SetStrength(flIN double strength);

    void SetFalloff(flIN double falloff);

    void SetInnerConeAngle(flIN double angleRads);
    void SetOuterConeAngle(flIN double angleRads);

    LightType GetLightType() const;

    Colour GetDiffuse() const;
    
    Colour GetAmbient() const;

    double GetStrength() const;

    double GetFalloff() const;

    double GetInnerConeAngle() const;

    double GetOuterConeAngle() const;
  };
}