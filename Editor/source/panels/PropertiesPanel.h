#ifndef PropertiesPanel_h__
#define PropertiesPanel_h__

#include "gui/flPanel.h"
#include "SceneSystem.h"
#include "EditorSystem.h"
#include "ctString.h"

class PropertiesPanel : public flEngine::GUI::Panel
{
public:
  PropertiesPanel(flEngine::GUI::GUISystem *pGUI)
    : Panel(pGUI, "Properties")
  {}

  virtual void OnGUI() override
  {
    Ref<EditorSystem> pEditor = Application::Get().GetSubSystem<EditorSystem>();
    Ref<SceneSystem> pSceneSystem = Application::Get().GetSubSystem<SceneSystem>();

    pEditor->m_selectedNode;
    Scene::Node *pNode = pSceneSystem->ActiveScene()->GetNode(pEditor->m_selectedNode);

    if (pNode != nullptr)
    {
      ctString name = pNode->GetName();
      ctVector<char> buffer;
      buffer.insert(0, name.begin(), name.end());
      buffer.resize(name.length() + 64);
      flEngine::GUI::Widgets::Input("Name", buffer.data(), buffer.size());
      pNode->SetName(buffer.data());
    }
  }
};

#endif // PropertiesPanel_h__
