#include "platform/flWindow.h"
#include "threads/flThreads.h"
#include "flEngine.h"
#include <stdio.h>

using namespace flEngine;
using namespace flEngine::Platform;
using namespace flEngine::Util;
using namespace flEngine::Threads;

int main(char **argv, int argc)
{
  // Create a window
  Window window("Title", Window::Flag_Visible, Window::DM_Windowed);

  // Get window input interfaces
  Inputs *pInputs            = window.GetInputs();
  Input::Mouse *pMouse       = pInputs->GetMouse();
  Input::Keyboard *pKeyboard = pInputs->GetKeyboard();

  while (!window.ReceivedEvent(E_Wnd_Close)) // Check if the window has requested a close
  {
    Inputs::Update(); // Push input events

    // Test for inputs
    if (pKeyboard->GetKeyPressed(Input::KC_L))
      printf("L pressed\n");
    if (pKeyboard->GetKeyDown(Input::KC_L))
      printf("L down\n");
    if (pKeyboard->GetKeyReleased(Input::KC_L))
      printf("L released\n");

    if (pMouse->GetPressed(Input::MB_Left))
      printf("%f, %f\n", pMouse->GetX(), pMouse->GetY());

    float vScroll = pMouse->GetScrollV();
    float hScroll = pMouse->GetScrollH();

    if (vScroll != 0)
      printf("%f\n", vScroll);

    if (hScroll != 0)
      printf("%f\n", hScroll);
  }

  return 0;
}
