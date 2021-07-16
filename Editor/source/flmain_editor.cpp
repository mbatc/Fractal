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
  class FractalEditor : public IApplicationBehaviour
  {
  public:
    virtual bool OnStartup() override
    {
      // Add modules to the editor
    }

    virtual void OnShutdown() override {}
    virtual void OnUpdate() override {}
    virtual void OnRender() override {}
    virtual void OnPreUpdate() override {}
    virtual void OnPreRender() override {}
    virtual void OnPostUpdate() override {}
    virtual void OnPostRender() override {}

    bool OnCloseEvent(Event* pEvent)
    {
      Close();
      return true;
    }

    static int64_t Exit(void*)
    {
      Fractal_GetApplication()->Close();
      return 0;
    }

    static int64_t ShowDemoWindow(void*)
    {
      Fractal_GetApplication()->GetModule<EditorGUIModule>()->OpenPanel<GUIExamplePanel>();
      return 0;
    }

    static int64_t ShowMetricsWindow(void*)
    {
      Fractal_GetApplication()->GetModule<EditorGUIModule>()->OpenPanel<GUIMetricsPanel>();
      return 0;
    }

    template<typename T>
    static int64_t ShowPanel()
    {
      Fractal_GetApplication()->GetModule<EditorGUIModule>()->OpenPanel<T>();
      return 0;
    }
  };
}

bool Fractal_Startup(char **argv, int argc)
{
  IApplication* pApplication = Fractal_GetApplication();

  pApplication->SetRootBehaviour(flNew FractalEditor);
}
