#include "flSubSystem.h"
#include "flApplication.h"
#include "flRef.h"

namespace flEngine
{
  class Impl_SubSystem
  {
  public:
    Input::Keyboard m_keyboard;
    Input::Mouse    m_mouse;
  };

  flPIMPL_IMPL(SubSystem)

  SubSystem::SubSystem()
  {
    OnEvent(Platform::E_Kbd_KeyState, &SubSystem::OnKeyState);
    OnEvent(Platform::E_Mse_Move,     &SubSystem::OnMouseMove);
    OnEvent(Platform::E_Mse_State,    &SubSystem::OnMouseState);
    OnEvent(Platform::E_Mse_Scroll,   &SubSystem::OnMouseScroll);
  }

  bool SubSystem::OnKeyState(Platform::Event* pEvent)
  {
    Impl()->m_keyboard.GetServer()->SendEvent(pEvent->kbdState.keyCode, pEvent->kbdState.isDown);
    return true;
  }

  bool SubSystem::OnMouseMove(Platform::Event* pEvent)
  {
    Impl()->m_mouse.GetServer()->SendEvent(Input::MA_XPos, (float)pEvent->mseMove.wndX);
    Impl()->m_mouse.GetServer()->SendEvent(Input::MA_YPos, (float)pEvent->mseMove.wndY);
    return true;
  }

  bool SubSystem::OnMouseState(Platform::Event* pEvent)
  {
    Impl()->m_mouse.GetServer()->SendEvent(pEvent->mseState.button, pEvent->mseState.isDown);
    return true;
  }

  bool SubSystem::OnMouseScroll(Platform::Event* pEvent)
  {
    if (pEvent->mseScroll.isHorizontal)
      Impl()->m_mouse.GetServer()->SendEvent(Input::MA_HScroll, (float)pEvent->mseScroll.amount, true);
    else
      Impl()->m_mouse.GetServer()->SendEvent(Input::MA_VScroll, (float)pEvent->mseScroll.amount, true);
    return true;
  }

  flEngine::Platform::Window* SubSystem::GetMainWindow()
  {
    return Application::Get().GetMainWindow();
  }

  flEngine::Platform::Window const* SubSystem::GetMainWindow() const
  {
    return Application::Get().GetMainWindow();
  }

  flEngine::Graphics::API* SubSystem::GetGraphicsAPI()
  {
    return Application::Get().GetGraphicsAPI();
  }

  flEngine::Graphics::API* SubSystem::GetGraphicsAPI() const
  {
    return Application::Get().GetGraphicsAPI();
  }

  Input::Mouse* SubSystem::GetMouse()
  {
    return &Impl()->m_mouse;
  }

  Input::Keyboard* SubSystem::GetKeyboard()
  {
    return &Impl()->m_keyboard;
  }

  Input::Keyboard const * SubSystem::GetKeyboard() const
  {
    return &Impl()->m_keyboard;
  }

  Input::Mouse const * SubSystem::GetMouse() const
  {
    return &Impl()->m_mouse;
  }
}