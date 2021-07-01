#include "flEntryPoint.h"
#include "flApplication.h"

int Fractal::FractalEntryHandler::Run(char** argv, int argc)
{
  Application& app = Application::Get();
  int result = app.Run();
  return result;
}
