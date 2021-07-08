#include "flEntryPoint.h"
#include "flApplication.h"

int Fractal::FractalEntryHandler::Run(char** argv, int argc)
{
  Application *pApp = GetApplication();
  int result = pApp->Run();
  return result;
}
