#include "platform/flWindow_Impl.h"

using namespace flEngine;
using namespace flEngine::Input;
using namespace flEngine::Platform;

class _WindowMouseServer : public InputDeviceServer
{
public:
  static _WindowMouseServer *Create(Window *pWindow)
  {
    return flNew _WindowMouseServer(pWindow);
  }

  _WindowMouseServer(Window *pWindow)
  {
    m_events.SetFilter(Platform::E_Type_Mouse);
    m_events.SetFilter(
      [](Platform::Event *pEvent, void *pUserData)
      {
        return ((Window*)pUserData)->IsEventSource(pEvent);
      },
      pWindow);

    m_events.SetEventCallback(&Mouse::EventHandler, this);
  }

protected:
  EventQueue m_events;
};

class _WindowKeyboardServer : public InputDeviceServer
{
public:
  static _WindowKeyboardServer *Create(Window *pWindow)
  {
    return flNew _WindowKeyboardServer(pWindow);
  }

  _WindowKeyboardServer(Window *pWindow)
  {
    m_events.SetFilter(Platform::E_Type_Keyboard);

    m_events.SetFilter(
      [](Platform::Event *pEvent, void *pUserData)
      {
        return ((Window*)pUserData)->IsEventSource(pEvent);
      },
      pWindow);

    m_events.SetEventCallback(&Keyboard::EventHandler, this);
  }

protected:
  EventQueue m_events;
};

bool Impl_Window::ReceivedEvent(EventID id, bool reset)
{
  bool received = m_receivedEvents[id];
  m_receivedEvents[id] &= !reset;
  return received;
}

Keyboard* Impl_Window::GetKeyboard()
{
  return &m_keyboard;
}

Mouse* Impl_Window::GetMouse()
{
  return &m_mouse;
}

#define flIMPL flPIMPL(Window)

flPIMPL_IMPL(Window);

Window::Window(flIN const char *title, flIN Flags flags, flIN DisplayMode displayMode)
{
  _WindowKeyboardServer *pKeyboardServer = _WindowKeyboardServer::Create(this);
  _WindowMouseServer *pMouseServer = _WindowMouseServer::Create(this);

  flIMPL->Construct(title, flags, displayMode, pKeyboardServer, pMouseServer);

  pKeyboardServer->DecRef();
  pMouseServer->DecRef();
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

void Window::GetRect(flOUT int64_t *pPosX, flOUT int64_t *pPosY, flOUT int64_t *pWidth, flOUT int64_t *pHeight) const
{
  flIMPL->GetRect(pPosX, pPosY, pWidth, pHeight);
}

bool Window::ReceivedEvent(flIN Platform::EventID id, flIN bool reset)
{
  return flIMPL->ReceivedEvent(id, reset);
}

Input::Keyboard* Window::GetKeyboard() const
{
  return flIMPL->GetKeyboard();
}

Input::Mouse* Window::GetMouse() const
{
  return flIMPL->GetMouse();
}

bool Window::IsEventSource(const Event *pEvent) const
{
  return flIMPL->IsEventSource(pEvent);
}
