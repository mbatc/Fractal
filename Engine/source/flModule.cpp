#include "flModule.h"
#include "flApplication.h"
#include "flRef.h"

namespace flEngine
{
  class Impl_Module
  {
  public:
    Input::Keyboard m_keyboard;
    Input::Mouse    m_mouse;
  };

  flPIMPL_IMPL(Module)

  Module::Module()
  {
    OnEvent(Platform::E_Kbd_KeyState, &Module::OnKeyState);
    OnEvent(Platform::E_Mse_Move,     &Module::OnMouseMove);
    OnEvent(Platform::E_Mse_State,    &Module::OnMouseState);
    OnEvent(Platform::E_Mse_Scroll,   &Module::OnMouseScroll);
  }

  bool Module::OnKeyState(Platform::Event* pEvent)
  {
    Impl()->m_keyboard.GetServer()->SendEvent(pEvent->kbdState.keyCode, pEvent->kbdState.isDown);
    return true;
  }

  bool Module::OnMouseMove(Platform::Event* pEvent)
  {
    Impl()->m_mouse.GetServer()->SendEvent(Input::MA_XPos, (float)pEvent->mseMove.wndX);
    Impl()->m_mouse.GetServer()->SendEvent(Input::MA_YPos, (float)pEvent->mseMove.wndY);
    return true;
  }

  bool Module::OnMouseState(Platform::Event* pEvent)
  {
    Impl()->m_mouse.GetServer()->SendEvent(pEvent->mseState.button, pEvent->mseState.isDown);
    return true;
  }

  bool Module::OnMouseScroll(Platform::Event* pEvent)
  {
    if (pEvent->mseScroll.isHorizontal)
      Impl()->m_mouse.GetServer()->SendEvent(Input::MA_HScroll, (float)pEvent->mseScroll.amount, true);
    else
      Impl()->m_mouse.GetServer()->SendEvent(Input::MA_VScroll, (float)pEvent->mseScroll.amount, true);
    return true;
  }

  flEngine::Platform::Window* Module::GetMainWindow()
  {
    return Application::Get().GetMainWindow();
  }

  flEngine::Platform::Window const* Module::GetMainWindow() const
  {
    return Application::Get().GetMainWindow();
  }

  flEngine::Graphics::API* Module::GetGraphicsAPI()
  {
    return Application::Get().GetGraphicsAPI();
  }

  flEngine::Graphics::API* Module::GetGraphicsAPI() const
  {
    return Application::Get().GetGraphicsAPI();
  }

  Input::Mouse* Module::GetMouse()
  {
    return &Impl()->m_mouse;
  }

  Input::Keyboard* Module::GetKeyboard()
  {
    return &Impl()->m_keyboard;
  }

  Input::Keyboard const * Module::GetKeyboard() const
  {
    return &Impl()->m_keyboard;
  }

  Input::Mouse const * Module::GetMouse() const
  {
    return &Impl()->m_mouse;
  }
}