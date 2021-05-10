#ifndef fl_EntryPoint_h__
#define fl_EntryPoint_h__

#include "flApplication.h"

namespace flEngine {
  extern Application* CreateApplication(char** argv, int argc);

  class flEXPORT FractalEntryHandler
  {
  public:
    static int Run(char** argv, int argc);
  };
}

#ifndef flCOMPILESHARED
int main(char** argv, int argc)
{
  flEngine::Application *pApp = flEngine::CreateApplication(argv, argc);
  int result = flEngine::FractalEntryHandler::Run(argv, argc);
  pApp->DecRef();
  return result;
}
#endif

#endif // fl_EntryPoint_h__
