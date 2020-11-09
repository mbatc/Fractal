#include "flEngine.h"

using namespace flEngine::Platform;

int main(char **argv, int argc)
{
  EventQueue queue;
  Event e = { 0 };

  bool run = true;
  while (run)
  {
    if (queue.NextEvent(&e))
    {
      if (e.id == E_Sys_Quit)
        run = false;
    }

    Event tst = { 0 };
    tst.id = E_Sys_Quit;
    tst.type = E_Type_System;
    tst.sysQuit.code = 1;
    queue.PostEvent(&tst);
  }

  return (int)e.sysQuit.code;
}
