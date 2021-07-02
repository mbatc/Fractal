#pragma once

#include "flApplicationBehaviour.h"
#include "flKeyboard.h"
#include "flMouse.h"

namespace Fractal
{
  class Window;
  class API;
  class Application;

  class Impl_Module;

  class flEXPORT Module : public ApplicationBehaviour
  {
    flPIMPL_DEF(Module);

  public:
    Module();

    Window* GetMainWindow();

    Window const* GetMainWindow() const;

    API* GetGraphicsAPI();

    API* GetGraphicsAPI() const;

    Mouse* GetMouse();

    Mouse const* GetMouse() const;

    Keyboard* GetKeyboard();

    Keyboard const* GetKeyboard() const;

    virtual bool OnKeyState(Event* pEvent);

    virtual bool OnMouseMove(Event* pEvent);

    virtual bool OnMouseState(Event* pEvent);

    virtual bool OnMouseScroll(Event* pEvent);
  };
}
