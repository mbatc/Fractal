#include "input\flMouse.h"
#include "platform\flEventQueue.h"

using namespace flEngine;
using namespace flEngine::Math;
using namespace flEngine::Input;

class _GlobalMouseServer : public InputDeviceServer
{
public:
  _GlobalMouseServer()
  {
    m_events.SetFilter(Platform::E_Type_Mouse);
    m_events.SetEventCallback(&Mouse::EventHandler, this);
  }

  static _GlobalMouseServer* Create()
  {
    return flNew _GlobalMouseServer;
  }

protected:
  Platform::EventQueue m_events;
};

Mouse::Mouse()
  : InputDevice(MB_Count + MB_ExtendedCount, MA_Count, _GlobalMouseServer::Create())
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

void Mouse::EventHandler(flIN Platform::Event *pEvent, flIN void *pUserData)
{
  InputDeviceServer *pServer = (InputDeviceServer*)pUserData;

  switch (pEvent->id)
  {
  case Platform::E_Mse_State:
    pServer->SendEvent(pEvent->mseState.button, pEvent->mseState.isDown);
    break;

  case Platform::E_Mse_Scroll:
    if (pEvent->mseScroll.isHorizontal)
      pServer->SendEvent(Input::MA_HScroll, (float)pEvent->mseScroll.amount, true);
    else
      pServer->SendEvent(Input::MA_VScroll, (float)pEvent->mseScroll.amount, true);
    break;

  case Platform::E_Mse_Move:
    pServer->SendEvent(Input::MA_XPos, (float)pEvent->mseMove.x);
    pServer->SendEvent(Input::MA_YPos, (float)pEvent->mseMove.y);
    break;
  }
}

void Mouse::OnPostUpdate()
{
  // Clear the scroll amount before receiving more scroll events.
  GetServer()->SendEvent(Input::MA_HScroll, 0.0f);
  GetServer()->SendEvent(Input::MA_VScroll, 0.0f);
}
