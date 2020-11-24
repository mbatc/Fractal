#include "input\flMouse.h"

using namespace flEngine::Input;
using namespace flEngine::Math;

Mouse::Mouse()
  : InputDevice(MB_Count + MB_ExtendedCount, MA_Count)
{}

bool Mouse::GetDown(MouseButton button) const
{
  return GetButton(button)->IsDown();
}

bool Mouse::GetPressed(MouseButton button) const
{
  return GetButton(button)->IsPressed();
}

bool Mouse::GetReleased(MouseButton button) const
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

flVec2F Mouse::GetPosition() const
{
  return flVec2F(GetX(), GetY());
}

flVec2F Mouse::GetPositionDelta() const
{
  return flVec2F(GetXDelta(), GetYDelta());
}

flVec2F Mouse::GetScroll() const
{
  return flVec2F(GetScrollH(), GetScrollV());
}

flVec2F Mouse::GetScrollDelta() const
{
  return flVec2F(GetScrollHDelta(), GetScrollVDelta());
}

void flEngine::Input::Mouse::OnUpdate()
{
  GetAnalog(MA_HScroll)->;
}
