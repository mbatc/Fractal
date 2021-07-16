#include "flEventQueue.h"
#include "flThreadQueue.h"
#include "flThreads.h"
#include "flITask.h"

#if flUSING(flPLATFORM_WINDOWS)

#include <windows.h>

namespace Fractal
{
  static int64_t _ProcessEvents(Interface*)
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
      Sleep(1);

    Fractal_GetEventThread()->Add(Fractal_CreateTask(_ProcessEvents, 0));

    return 0;
  }
}

extern "C" {
  flEXPORT Fractal::IThreadQueue* flCCONV Fractal_GetEventThread()
  {
    static Fractal::IThreadQueue* _pEventThread = Fractal_CreateThreadQueue();
    static bool _initialised = false;

    if (!_initialised)
    {
      _initialised = true;
      _pEventThread->Add(Fractal_CreateTask(Fractal::_ProcessEvents, 0));
    }

    return _pEventThread;
  }
}
#endif
