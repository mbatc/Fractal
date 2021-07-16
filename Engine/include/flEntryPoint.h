#pragma once

#include "flApplication.h"

namespace Fractal
{
  /**
   * @brief Create the client application. INTERNAL USE ONLY.
   *
   * You need to implement this function to configure the application instance
   * for the engine at startup.
   * 
   * This usually involves setting the root behavior for the Application.
   *
   * Do not call this function yourself if you are using Fractals built in entry point.
   */
  extern bool Fractal_Startup(char** argv, int argc);
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
  Fractal::Application* pApp = Fractal::CreateApplication(argv, argc);

  // Call the startup function to allow the client to configure the application
  Fractal_Startup(argv, argc);

  // Run it and wait for the result
  pApp->Run();

  // Release the application reference
  pApp->DecRef();

  // Return our result
  return result;
}

#endif
#endif
