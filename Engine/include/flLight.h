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

    void SetColour(flIN Colour colour);

    void SetStrength(flIN double strength);

    void SetFalloff(flIN double falloff);

    LightType GetLightType() const;

    Colour GetColour() const;

    double GetStrength() const;

    double GetFalloff() const;
  };
}