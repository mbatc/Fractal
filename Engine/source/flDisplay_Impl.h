#pragma once

#include "flMath.h"
#include "ctVector.h"
#include "flRef.h"

namespace Fractal
{
  class Display;

  class Impl_Display
  {
  public:
    Vec2I position;
    Vec2I size;
    Vec2I workAreaPosition;
    Vec2I workAreaSize;
    bool   primary;
    double dpiScale;
  };

  class Impl_DisplayList
  {
  public:
    ctVector<Ref<Display>> displays;
  };
}