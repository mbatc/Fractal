#include "flDisplay.h"
#include "flDisplay_Impl.h"

namespace Fractal
{
  flPIMPL_IMPL(Display);

  Vec2I Display::GetPosition() const
  {
    return Impl()->position;
  }

  Vec2I Display::GetSize() const
  {
    return Impl()->size;
  }

  Vec2I Display::GetWorkAreaSize() const
  {
    return Impl()->workAreaSize;
  }

  Vec2I Display::GetWorkAreaPosition() const
  {
    return Impl()->workAreaPosition;
  }

  bool Display::IsPrimaryMonitor() const
  {
    return Impl()->primary;
  }

  double Display::GetDPIScale() const
  {
    return Impl()->dpiScale;
  }

  flPIMPL_IMPL(DisplayList);

  int64_t DisplayList::GetDisplayCount() const
  {
    return Impl()->displays.size();
  }

  Display const* DisplayList::GetDisplay(flIN int64_t index) const
  {
    return index < 0 || index >= GetDisplayCount() ? nullptr : Impl()->displays[index];
  }
}
