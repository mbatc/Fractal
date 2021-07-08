#include "flWindow_Impl.h"

namespace Fractal
{
  bool Impl_Window::ReceivedEvent(EventID id, bool reset)
  {
    bool received = m_receivedEvents[id];
    m_receivedEvents[id] &= !reset;
    return received;
  }

  flPIMPL_IMPL(Window);

  Window* Window::Create(flIN const char* title, flIN Flags flags, flIN DisplayMode displayMode, flIN Window* pParent)
  {
    return flNew Window(title, flags, displayMode, pParent);
  }

  Window::Window(flIN const char* title, flIN Flags flags, flIN DisplayMode displayMode, flIN Window* pParent)
  {
    Impl()->Construct(this, title, flags, displayMode, pParent);
  }

  void Window::SetTitle(flIN const char* title)
  {
    return Impl()->SetTitle(title);
  }

  void Window::SetDisplayMode(flIN DisplayMode mode)
  {
    return Impl()->SetDisplayMode(mode);
  }

  void Window::SetFocus(flIN FocusFlags flags, flIN bool focused)
  {
    return Impl()->SetFocus(flags, focused);
  }

  void Window::SetSize(flIN int64_t width, flIN int64_t height)
  {
    return Impl()->SetSize(width, height);
  }

  void Window::SetPosition(flIN int64_t posX, flIN int64_t posY)
  {
    return Impl()->SetPosition(posX, posY);
  }

  void Window::SetRect(flIN int64_t posX, flIN int64_t posY, flIN int64_t width, flIN int64_t height)
  {
    return Impl()->SetRect(posX, posY, width, height);
  }

  void Window::SetParent(flIN Window* pParent)
  {
    return Impl()->SetParent(pParent);
  }

  Window* Window::GetParent() const
  {
    return Impl()->GetParent();
  }

  const char* Window::GetTitle() const
  {
    return Impl()->GetTitle();
  }

  Window::DisplayMode Window::GetDisplayMode() const
  {
    return Impl()->GetDisplayMode();
  }

  Window::FocusFlags Window::GetFocusFlags() const
  {
    return Impl()->GetFocusFlags();
  }

  Window::Flags Window::GetFlags() const
  {
    return Impl()->GetFlags();
  }

  void Window::SetFlags(flIN Flags flags)
  {
    return Impl()->SetFlags(flags);
  }

  void Window::AddFlags(flIN Flags flags)
  {
    return Impl()->AddFlags(flags);
  }

  void Window::RemoveFlags(flIN Flags flags)
  {
    return Impl()->RemoveFlags(flags);
  }

  void Window::GetSize(flOUT int64_t* pWidth, flOUT int64_t* pHeight) const
  {
    Impl()->GetSize(pWidth, pHeight);
  }

  int64_t Window::GetWidth() const
  {
    return Impl()->GetWidth();
  }

  int64_t Window::GetHeight() const
  {
    return Impl()->GetHeight();
  }

  void Window::GetPosition(flOUT int64_t* pPosX, flOUT int64_t* pPosY) const
  {
    Impl()->GetPosition(pPosX, pPosY);
  }

  int64_t Window::GetX() const
  {
    return Impl()->GetX();
  }

  int64_t Window::GetY() const
  {
    return Impl()->GetY();
  }

  void Window::GetRect(flOUT int64_t* pPosX, flOUT int64_t* pPosY, flOUT int64_t* pWidth, flOUT int64_t* pHeight) const
  {
    Impl()->GetRect(pPosX, pPosY, pWidth, pHeight);
  }

  bool Window::ReceivedEvent(flIN EventID id, flIN bool reset)
  {
    return Impl()->ReceivedEvent(id, reset);
  }

  void Window::BringToFocus()
  {
    return Impl()->BringToFocus();
  }

  bool Window::IsEventSource(const Event* pEvent) const
  {
    return Impl()->IsEventSource(pEvent);
  }

  void* Window::GetNativeHandle() const
  {
    return Impl()->GetNativeHandle();
  }

  WindowRenderTarget* Window::GetRenderTarget() const
  {
    return Impl()->GetRenderTarget();
  }

  Window* Window::GetFocusedWindow(flIN FocusFlags focusFlags)
  {
    return Impl_Window::GetFocusedWindow(focusFlags);
  }

  Window* Window::GetForegroundWindow()
  {
    return Impl_Window::GetForegroundWindow();
  }
}