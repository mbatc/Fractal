#pragma once

#pragma comment(lib, "Shcore.lib")

#include "flInterface.h"
#include "flMath.h"

namespace Fractal
{
  class DisplayList;
  class Impl_Display;

  class flEXPORT Display : public Interface
  {
    flPIMPL_DEF(Display);
  public:
    static DisplayList* EnumerateDisplays();

    Vec2I GetPosition() const;
    Vec2I GetSize() const;

    Vec2I GetWorkAreaSize() const;
    Vec2I GetWorkAreaPosition() const;

    bool IsPrimaryMonitor() const;

    double GetDPIScale() const;
  };

  class Impl_DisplayList;

  class flEXPORT DisplayList : public Interface
  {
    flPIMPL_DEF(DisplayList);
  public:
    int64_t GetDisplayCount() const;

    Display const* GetDisplay(flIN int64_t index) const;
  };
}
