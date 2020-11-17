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
  Window window("Title", Window::Flag_Visible, Window::DM_Windowed);

  while (!window.ReceivedEvent(E_Wnd_Close))
    Threads::Sleep(1);

  return 0;
}
