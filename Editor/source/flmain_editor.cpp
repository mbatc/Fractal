#include "flEngine.h"
#include "flEntryPoint.h"

#include "EditorModule.h"
#include "EditorGUIModule.h"
#include "ProjectPanel.h"
#include "ScenePanel.h"
#include "SceneViewPanel.h"
#include "PropertiesPanel.h"

namespace Fractal
{
  class FractalEditor : public Application
  {
  public:
    FractalEditor()
      : Application("OpenGL")
    {
      AddModule<SceneManager>();
      AddModule<EditorGUIModule>();
      AddModule<EditorModule>();

      auto gui = GetModule<EditorGUIModule>();
      gui->AddPanel<ScenePanel>();
      gui->AddPanel<SceneViewPanel>();
      gui->AddPanel<ProjectPanel>();
      gui->AddPanel<PropertiesPanel>();
      gui->AddPanel<GUIExamplePanel>();
      gui->AddPanel<GUIMetricsPanel>();

      gui->OpenPanel<ScenePanel>();
      gui->OpenPanel<SceneViewPanel>();
      gui->OpenPanel<ProjectPanel>();
      gui->OpenPanel<PropertiesPanel>();

      gui->AddMenuItem("File/Exit", MakeTask(Exit));
      gui->AddMenuItem("Window/Demo", MakeTask(ShowDemoWindow));
      gui->AddMenuItem("Window/Metrics", MakeTask(ShowMetricsWindow));

      gui->AddMenuItem("Window/Project",     MakeTask(ShowPanel<ProjectPanel>));
      gui->AddMenuItem("Window/Scene View",  MakeTask(ShowPanel<SceneViewPanel>));
      gui->AddMenuItem("Window/Scene Graph", MakeTask(ShowPanel<ScenePanel>));
      gui->AddMenuItem("Window/Properties",  MakeTask(ShowPanel<PropertiesPanel>));

      OnEvent(E_Wnd_Close, &FractalEditor::OnCloseEvent);
    }

    bool OnCloseEvent(Event* pEvent)
    {
      Close();
      return true;
    }

    static int64_t Exit(void*)
    {
      Application::Get().Close();
      return 0;
    }

    static int64_t ShowDemoWindow(void*)
    {
      Application::Get().GetModule<EditorGUIModule>()->OpenPanel<GUIExamplePanel>();
      return 0;
    }

    static int64_t ShowMetricsWindow(void*)
    {
      Application::Get().GetModule<EditorGUIModule>()->OpenPanel<GUIMetricsPanel>();
      return 0;
    }

    template<typename T>
    static int64_t ShowPanel()
    {
      Application::Get().GetModule<EditorGUIModule>()->OpenPanel<T>();
      return 0;
    }
  };

  Application* CreateApplication(char** argv, int argc)
  {
    return flNew FractalEditor;
  }
}