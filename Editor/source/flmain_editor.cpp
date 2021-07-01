#include "flEngine.h"
#include "flEntryPoint.h"

#include "EditorModule.h"
#include "EditorGUIModule.h"
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
    AddModule<SceneManager>();
    AddModule<EditorGUIModule>();
    AddModule<EditorModule>();

    auto gui = GetModule<EditorGUIModule>();
    gui->Open<ScenePanel>();
    gui->Open<SceneViewPanel>();
    gui->Open<ProjectPanel>();
    gui->Open<PropertiesPanel>();
    gui->AddMenuItem("File/Exit", Exit);

    OnEvent(E_Wnd_Close, &FractalEditor::OnCloseEvent);
  }

  bool OnCloseEvent(Platform::Event* pEvent)
  {
    Close();
    return true;
  }

  static void Exit()
  {
    Application::Get().Close();
  }
};

flEngine::Application* flEngine::CreateApplication(char** argv, int argc)
{
  return flNew FractalEditor;
}
