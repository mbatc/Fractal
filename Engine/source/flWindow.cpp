#include "flWindow.h"

extern "C" {
  flEXPORT Fractal::IWindow* Fractal_CreateWindow(flIN char const* title, flIN Fractal::WindowFlags flags, flIN Fractal::WindowDisplayMode displayMode)
  {
    return flNew Fractal::Impl::Window(title, flags, displayMode);
  }

  flEXPORT Fractal::IWindow* Fractal_GetFocusedWindow(flIN Fractal::WindowFocusFlags focusFlags)
  {
    return Fractal::Impl::Window::GetFocusedWindow(focusFlags);
  }
}
