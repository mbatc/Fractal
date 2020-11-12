#include "flPlatform_Window.h"
#include "flPlatform_Window_Impl.h"

using namespace flEngine::Platform;

#define flIMPL flPIMPL(Window)

flPIMPL_IMPL(Window);

Window::Window(flIN const char *title, flIN Flags flags, flIN Window::DisplayMode displayMode)
{
  flIMPL->Construct(title, flags, displayMode);
}

void Window::SetTitle(flIN const char *title)
{
  return flIMPL->SetTitle(title);
}

void Window::SetDisplayMode(flIN Window::DisplayMode mode)
{
  return flIMPL->SetDisplayMode(mode);
}

void Window::SetFocus(flIN Window::FocusFlags flags, flIN bool focused)
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
