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
    OBJImporter importer;
    importer.Import("C:/Users/mickb/OneDrive/Documents/Assets/Models/OBJ.obj");

    AddSubSystem<SceneSystem>();
    AddSubSystem<EditorGUI>();
    AddSubSystem<EditorSystem>();

    auto gui = GetSubSystem<EditorGUI>();
    gui->Open<ScenePanel>();
    gui->Open<SceneViewPanel>();
    gui->Open<ProjectPanel>();
    gui->Open<PropertiesPanel>();
    gui->AddMenuItem("File/Exit", Exit);

    OnEvent(E_Wnd_Close, &FractalEditor::OnCloseEvent);

    Mesh m;
    m.AddVertex({ -1, 0, -1 }, { 0, 1, 0 }, { 0, 0 }, { 1, 1, 1, 1 });
    m.AddVertex({ -1, 0,  1 }, { 0, 1, 0 }, { 0, 0 }, { 1, 1, 1, 1 });
    m.AddVertex({  1, 0,  1 }, { 0, 1, 0 }, { 0, 0 }, { 1, 1, 1, 1 });
    m.AddVertex({  1, 0, -1 }, { 0, 1, 0 }, { 0, 0 }, { 1, 1, 1, 1 });
    
    m.AddPolygon();
    m.AddPolygon();

    m.SetPolygonMaterial(0, 0);
    m.AddPolygonVertex(0, 0);
    m.AddPolygonVertex(0, 1);
    m.AddPolygonVertex(0, 2);

    m.SetPolygonMaterial(1, 0);
    m.AddPolygonVertex(1, 0);
    m.AddPolygonVertex(1, 2);
    m.AddPolygonVertex(1, 3);
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
