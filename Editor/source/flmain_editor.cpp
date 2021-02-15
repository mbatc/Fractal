#include "flEngine.h"
#include "graphics/OpenGL/flOpenGL.h"

#include <stdio.h>

using namespace flEngine;
using namespace flEngine::Platform;
using namespace flEngine::Util;
using namespace flEngine::Threads;

int main(char **argv, int argc)
{
  // Create a window
  Window window("Has Inputs", Window::Flag_Visible, Window::DM_Windowed);
  Window window2("Has Inputs", Window::Flag_Visible, Window::DM_Windowed);
  
  Graphics::API *pOpenGL = Graphics::OpenGL::Create(&window);

  Graphics::WindowRenderTarget *pFirstTarget = window.GetRenderTarget();
  Graphics::WindowRenderTarget *pSecondTarget = pOpenGL->CreateWindowRenderTarget(&window2, nullptr);

  // Get window input interfaces
  Input::Mouse    *pMouse    = window.GetMouse();
  Input::Keyboard *pKeyboard = window.GetKeyboard();

  Input::Mouse globalMouse;
  Input::Keyboard globalKbd;

  while (!window.ReceivedEvent(E_Wnd_Close)) // Check if the window has requested a close
  {
    Inputs::Update(); // Push input events

    // Test for inputs
    if (pKeyboard->GetKeyPressed(Input::KC_L))
      printf("Window L pressed\n");
    if (pKeyboard->GetKeyDown(Input::KC_L))
      printf("Window L down\n");
    if (pKeyboard->GetKeyReleased(Input::KC_L))
      printf("Window L released\n");

    if (globalMouse.GetPressed(Input::MB_Left))
    {
      Window *pWindow = Window::GetFocusedWindow(Window::FF_Mouse);
      if (pWindow)
      {
        Input::Mouse *pFocusedMouse = pWindow->GetMouse();
        printf("Window [0x%X]: %f, %f\n", (int64_t)pWindow, pFocusedMouse->GetX(), pFocusedMouse->GetY());
      }

      printf("Screen: %f, %f\n", globalMouse.GetX(), globalMouse.GetY());
    }

    float vScroll = pMouse->GetScrollV();
    float hScroll = pMouse->GetScrollH();

    if (vScroll != 0)
      printf("%f\n", vScroll);

    if (hScroll != 0)
      printf("%f\n", hScroll);

    if (globalKbd.GetKeyPressed(Input::KC_L))
      printf("Global L pressed\n");
    if (globalKbd.GetKeyDown(Input::KC_L))
      printf("Global L down\n");
    if (globalKbd.GetKeyReleased(Input::KC_L))
      printf("Global L released\n");

    pFirstTarget->Clear(0xFF0000FF);
    pFirstTarget->Swap();

    pSecondTarget->Clear(0xFF00FF00);
    pSecondTarget->Swap();
  }

  return 0;
}
