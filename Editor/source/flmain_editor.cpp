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
      OnEvent(E_Kbd_KeyState, &FractalEditor::OnKey);
    }

    void OnUpdate()
    {
      if (m_reloadShaders)
      {
        SceneGraph *pScene = GetModule<SceneManager>()->ActiveScene();
        for (int64_t id : pScene->GetNodeIDs())
        {
          Node *pNode = pScene->GetNode(id);
          MeshRenderer *pMesh = pNode->GetComponent<MeshRenderer>();
          if (pMesh != nullptr)
            for (int64_t i = 0; i < pMesh->GetSubMeshCount(); ++i)
              pMesh->GetShader(i)->Reload();
        }

        for (int64_t id : pScene->GetNodeIDs())
        {
          Node *pNode = pScene->GetNode(id);
          MeshRenderer *pMesh = pNode->GetComponent<MeshRenderer>();
          if (pMesh)
            for (int64_t i = 0; i < pMesh->GetSubMeshCount(); ++i)
              pMesh->GetShader(i)->Compile();
        }

        m_reloadShaders = false;
      }
    }

    bool OnCloseEvent(Event* pEvent)
    {
      Close();
      return true;
    }

    bool OnKey(Event *pEvent)
    {
      static bool allowReload = true;
      if (pEvent->kbdState.keyCode == KC_Apostraphe)
      {
        if (pEvent->kbdState.isDown)
        {
          m_reloadShaders |= allowReload;
          allowReload = false;
        }
        else
          allowReload = true;
      }

      return true;
    }

    static int64_t Exit(void*)
    {
      GetApplication()->Close();
      return 0;
    }

    static int64_t ShowDemoWindow(void*)
    {
      GetApplication()->GetModule<EditorGUIModule>()->OpenPanel<GUIExamplePanel>();
      return 0;
    }

    static int64_t ShowMetricsWindow(void*)
    {
      GetApplication()->GetModule<EditorGUIModule>()->OpenPanel<GUIMetricsPanel>();
      return 0;
    }

    template<typename T>
    static int64_t ShowPanel()
    {
      GetApplication()->GetModule<EditorGUIModule>()->OpenPanel<T>();
      return 0;
    }

    bool m_reloadShaders = false;
  };


  Application* CreateApplication(char** argv, int argc)
  {
    return flNew FractalEditor;
  }
}