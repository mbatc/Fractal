#include "flEngine.h"
#include "flEntryPoint.h"
#include <stdio.h>

using namespace flEngine;
using namespace flEngine::Platform;
using namespace flEngine::Util;
using namespace flEngine::Threads;
using namespace flEngine::Math;

class FractalEditor : public flEngine::Application
{
public:
  FractalEditor()
    : Application("OpenGL")
  {}
};

flEngine::Application* flEngine::CreateApplication(char** argv, int argc)
{
  return flNew FractalEditor;
}
