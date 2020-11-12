#include "flEngine.h"
#include <stdio.h>
#include "flPlatform_Window.h"

using namespace flEngine::Platform;
using namespace flEngine::Util;
using namespace flEngine::Threads;

int main(char **argv, int argc)
{
  ThreadQueue tasks;

  EventQueue queue;

  tasks.Add([](void *) {
    printf("My first task\n");
    return 1ll;
  });

  tasks.Add([](void *) {
    printf("My second task\n");
    return 1ll;
  });

  tasks.Add([](void *pQueuePtr) {
    printf("My third task\n");

    ((ThreadQueue*)pQueuePtr)->Add([](void *) {
      printf("I was added in another task");
      return 0ll;
    });

    return 1ll;
  }, &tasks);

  Event e = { 0 };

  Window window("Title", Window::Flag_Visible, Window::DM_Windowed);

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

  tasks.Flush();

  return (int)e.sysQuit.code;
}
