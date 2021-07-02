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
      gui->Open<ScenePanel>();
      gui->Open<SceneViewPanel>();
      gui->Open<ProjectPanel>();
      gui->Open<PropertiesPanel>();
      gui->AddMenuItem("File/Exit", Exit);

      OnEvent(E_Wnd_Close, &FractalEditor::OnCloseEvent);
    }

    bool OnCloseEvent(Event *pEvent)
    {
      Close();
      return true;
    }

    static void Exit()
    {
      Application::Get().Close();
    }
  };

  Application *CreateApplication(char **argv, int argc)
  {
    return flNew FractalEditor;
  }
}