#pragma once

#include "flIApplicationBehaviour.h"
#include "flKeyboard.h"
#include "flMouse.h"

namespace Fractal
{
  class IWindow;
  class API;
  class IApplication;

  class Impl_Module;

  class flEXPORT Module : public IApplicationBehaviour
  {
    flPIMPL_DEF(Module);

  public:
    Module();

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
