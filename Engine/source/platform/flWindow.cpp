#include "platform/flWindow_Impl.h"

using namespace flEngine::Platform;

bool Impl_Window::ReceivedEvent(EventID id, bool reset)
{
  bool received = m_receivedEvents[id];
  m_receivedEvents[id] &= !reset;
  return received;
}

#define flIMPL flPIMPL(Window)

flPIMPL_IMPL(Window);

Window::Window(flIN const char *title, flIN Flags flags, flIN DisplayMode displayMode)
{
  flIMPL->Construct(title, flags, displayMode);
}

void Window::SetTitle(flIN const char *title)
{
  return flIMPL->SetTitle(title);
}

void Window::SetDisplayMode(flIN DisplayMode mode)
{
  return flIMPL->SetDisplayMode(mode);
}

void Window::SetFocus(flIN FocusFlags flags, flIN bool focused)
{
  return flIMPL->SetFocus(flags, focused);
}

void Window::SetSize(flIN int64_t width, flIN int64_t height)
{
  return flIMPL->SetSize(width, height);
}

void Window::SetPosition(flIN int64_t posX, flIN int64_t posY)
{
  return flIMPL->SetPosition(posX, posY);
}

void Window::SetRect(flIN int64_t posX, flIN int64_t posY, flIN int64_t width, flIN int64_t height)
{
  return flIMPL->SetRect(posX, posY, width, height);
}

const char* Window::GetTitle() const
{
  return flIMPL->GetTitle();
}

Window::DisplayMode Window::GetDisplayMode() const
{
  return flIMPL->GetDisplayMode();
}

Window::FocusFlags Window::GetFocusFlags() const
{
  return flIMPL->GetFocusFlags();
}

Window::Flags Window::GetFlags() const
{
  return flIMPL->GetFlags();
}

void Window::GetSize(flOUT int64_t *pWidth, flOUT int64_t *pHeight) const
{
  flIMPL->GetSize(pWidth, pHeight);
}

int64_t Window::GetWidth() const
{
  return flIMPL->GetWidth();
}

int64_t Window::GetHeight() const
{
  return flIMPL->GetHeight();
}

void Window::GetPosition(flOUT int64_t *pPosX, flOUT int64_t *pPosY) const
{
  flIMPL->GetPosition(pPosX, pPosY);
}

int64_t Window::GetX() const
{
  return flIMPL->GetX();
}

int64_t Window::GetY() const
{
  return flIMPL->GetY();
}

void Window::GetRect(int64_t *pPosX, int64_t *pPosY, int64_t *pWidth, int64_t *pHeight) const
{
  flIMPL->GetRect(pPosX, pPosY, pWidth, pHeight);
}

bool Window::ReceivedEvent(EventID id, bool reset)
{
  return flIMPL->ReceivedEvent(id, reset);
}
