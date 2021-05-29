#include "flEngine.h"
#include "flEntryPoint.h"

#include "EditorSystem.h"
#include "EditorGUI.h"
#include "ProjectPanel.h"
#include "ScenePanel.h"
#include "SceneViewPanel.h"
#include "PropertiesPanel.h"

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
  {
    AddSubSystem<EditorGUI>();
    AddSubSystem<EditorSystem>();

    auto gui = GetSubSystem<EditorGUI>();
    gui->Open<ScenePanel>();
    gui->Open<SceneViewPanel>();
    gui->Open<ProjectPanel>();
    gui->Open<PropertiesPanel>();
  }
};

flEngine::Application* flEngine::CreateApplication(char** argv, int argc)
{
  return flNew FractalEditor;
}
