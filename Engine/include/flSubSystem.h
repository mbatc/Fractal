#ifndef flSubSystem_h__
#define flSubSystem_h__

#include "flApplicationBehaviour.h"
#include "input/flKeyboard.h"
#include "input/flMouse.h"

namespace flEngine
{
  namespace Platform {
    class Window;
  }

  namespace Graphics {
    class API;
  }

  class Application;

  class Impl_SubSystem;

  class flEXPORT SubSystem : public ApplicationBehaviour
  {
    flPIMPL_DEF(SubSystem);

  public:
    SubSystem();

    Platform::Window * GetMainWindow();
    
    Platform::Window const* GetMainWindow() const;

    Graphics::API * GetGraphicsAPI();

    Graphics::API * GetGraphicsAPI() const;

    Input::Mouse * GetMouse();
    
    Input::Mouse const * GetMouse() const;

    Input::Keyboard * GetKeyboard();
    
    Input::Keyboard const * GetKeyboard() const;

    virtual bool OnKeyState(Platform::Event* pEvent);
    
    virtual bool OnMouseMove(Platform::Event* pEvent);
    
    virtual bool OnMouseState(Platform::Event *pEvent);

    virtual bool OnMouseScroll(Platform::Event *pEvent);
  };
}


#endif // flSubSystem_h__
