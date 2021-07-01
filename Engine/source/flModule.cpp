#include "flModule.h"
#include "flApplication.h"
#include "flRef.h"

namespace Fractal
{
  class Impl_Module
  {
  public:
    Keyboard m_keyboard;
    Mouse    m_mouse;
  };

  flPIMPL_IMPL(Module);

  Module::Module()
  {
    OnEvent(E_Kbd_KeyState, &Module::OnKeyState);
    OnEvent(E_Mse_Move,     &Module::OnMouseMove);
    OnEvent(E_Mse_State,    &Module::OnMouseState);
    OnEvent(E_Mse_Scroll,   &Module::OnMouseScroll);
  }

  bool Module::OnKeyState(Event* pEvent)
  {
    Impl()->m_keyboard.GetServer()->SendEvent(pEvent->kbdState.keyCode, pEvent->kbdState.isDown);
    return true;
  }

  bool Module::OnMouseMove(Event* pEvent)
  {
    Impl()->m_mouse.GetServer()->SendEvent(MA_XPos, (float)pEvent->mseMove.wndX);
    Impl()->m_mouse.GetServer()->SendEvent(MA_YPos, (float)pEvent->mseMove.wndY);
    return true;
  }

  bool Module::OnMouseState(Event* pEvent)
  {
    Impl()->m_mouse.GetServer()->SendEvent(pEvent->mseState.button, pEvent->mseState.isDown);
    return true;
  }

  bool Module::OnMouseScroll(Event* pEvent)
  {
    if (pEvent->mseScroll.isHorizontal)
      Impl()->m_mouse.GetServer()->SendEvent(MA_HScroll, (float)pEvent->mseScroll.amount, true);
    else
      Impl()->m_mouse.GetServer()->SendEvent(MA_VScroll, (float)pEvent->mseScroll.amount, true);
    return true;
  }

  Window* Module::GetMainWindow()
  {
    return Application::Get().GetMainWindow();
  }

  Window const* Module::GetMainWindow() const
  {
    return Application::Get().GetMainWindow();
  }

  API* Module::GetGraphicsAPI()
  {
    return Application::Get().GetGraphicsAPI();
  }

  API* Module::GetGraphicsAPI() const
  {
    return Application::Get().GetGraphicsAPI();
  }

  Mouse* Module::GetMouse()
  {
    return &Impl()->m_mouse;
  }

  Keyboard* Module::GetKeyboard()
  {
    return &Impl()->m_keyboard;
  }

  Keyboard const* Module::GetKeyboard() const
  {
    return &Impl()->m_keyboard;
  }

  Mouse const* Module::GetMouse() const
  {
    return &Impl()->m_mouse;
  }
}