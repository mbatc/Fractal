#include "platform/flEventQueue.h"
#include "threads/flThreadQueue.h"
#include "threads/flThreads.h"

#if flUSING(flPLATFORM_WINDOWS)

#include <windows.h>

using namespace flEngine;
using namespace flEngine::Platform;

static int64_t _ProcessEvents(void *)
{
  MSG msg = { 0 };
  bool active = false;

  while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
    active = true;
  }

  if (!active)
    Threads::Sleep(1);

  EventQueue::GetEventThread()->Add(_ProcessEvents);

  return 0;
}

Threads::ThreadQueue* Platform::EventQueue::GetEventThread()
{
  static Threads::ThreadQueue _eventThread;
  static bool _initialised = false;

  if (!_initialised)
  {
    _initialised = true;
    _eventThread.Add(_ProcessEvents);
  }

  return &_eventThread;
}

#endif
