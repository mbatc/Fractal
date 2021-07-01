#include "flMouse.h"
#include "flEventQueue.h"

namespace Fractal
{
static Window* _pActiveWindow = nullptr;

Mouse::Mouse()
  : InputDevice(MB_Count + MB_ExtendedCount, MA_Count)
{}

bool Mouse::GetDown(flIN MouseButton button) const
{
  return GetButton(button)->IsDown();
}

bool Mouse::GetPressed(flIN MouseButton button) const
{
  return GetButton(button)->IsPressed();
}

bool Mouse::GetReleased(flIN MouseButton button) const
{
  return GetButton(button)->IsReleased();
}

float Mouse::GetX() const
{
  return GetAnalog(MA_XPos)->GetValue();
}

float Mouse::GetY() const
{
  return GetAnalog(MA_YPos)->GetValue();
}

float Mouse::GetXDelta() const
{
  return GetAnalog(MA_XPos)->GetDelta();
}

float Mouse::GetYDelta() const
{
  return GetAnalog(MA_YPos)->GetDelta();
}

float Mouse::GetScrollH() const
{
  return GetAnalog(MA_HScroll)->GetValue();
}

float Mouse::GetScrollV() const
{
  return GetAnalog(MA_VScroll)->GetValue();
}

float Mouse::GetScrollHDelta() const
{
  return GetAnalog(MA_HScroll)->GetDelta();
}

float Mouse::GetScrollVDelta() const
{
  return GetAnalog(MA_VScroll)->GetDelta();
}

Vec2F Mouse::GetPosition() const
{
  return Vec2F(GetX(), GetY());
}

Vec2F Mouse::GetPositionDelta() const
{
  return Vec2F(GetXDelta(), GetYDelta());
}

Vec2F Mouse::GetScroll() const
{
  return Vec2F(GetScrollH(), GetScrollV());
}

Vec2F Mouse::GetScrollDelta() const
{
  return Vec2F(GetScrollHDelta(), GetScrollVDelta());
}

void Mouse::OnPostUpdate()
{
  // Clear the scroll amount before receiving more scroll events.
  GetServer()->SendEvent(MA_HScroll, 0.0f);
  GetServer()->SendEvent(MA_VScroll, 0.0f);
}
}