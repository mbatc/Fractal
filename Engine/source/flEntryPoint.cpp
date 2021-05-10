#include "flEntryPoint.h"
#include "flApplication.h"

int flEngine::FractalEntryHandler::Run(char** argv, int argc)
{
  Application& app = Application::Get();
  if (!app.OnStartup())
    return 1; // Startup failed

  int result = app.Run();
  app.OnShutdown();
  return result;
}
