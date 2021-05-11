#ifndef fl_EntryPoint_h__
#define fl_EntryPoint_h__

#include "flApplication.h"

namespace flEngine {
  /**
   * @brief Create the client application. INTERNAL USE ONLY.
   * 
   * You need to implement this function to return an application instance
   * for the engine.
   * 
   * Do not call this function yourself if you are using Fractals built in entry point.
   */
  extern Application* CreateApplication(char** argv, int argc);

  /**
   * @brief This is a helper class used to.
   */
  class flEXPORT FractalEntryHandler
  {
  public:
    static int Run(char** argv, int argc);
  };
}

#ifndef flCOMPILESHARED
#ifndef flNO_ENTRY_POINT

/**
 * @brief Fractal Engine entry point.
 * 
 * This is the default main function used to create the client application.
 * 
 * You may define your own entry point if you wish, but make sure it performs
 * the same steps used in this function.
 * 
 * Define flNO_ENTRY_POINT before including this file to disable the default entry point.
 */
int main(char** argv, int argc)
{
  // Create the application
  flEngine::Application *pApp = flEngine::CreateApplication(argv, argc);

  // Run it and wait for the result
  int result = flEngine::FractalEntryHandler::Run(argv, argc);

  // Release the application reference
  pApp->DecRef();

  // Return our result
  return result;
}

#endif
#endif

#endif // fl_EntryPoint_h__
