#include "ScenePanel.h"
#include "ctVector.h"

using namespace flEngine;
using namespace flEngine::Scene;
using namespace flEngine::GUI;

class GUIVisitor : public Visitor<Node>
{
public:
  GUIVisitor(int64_t selectedID) : m_selectedID(selectedID) {}

  virtual bool OnEnter(flIN Node* pNode) {
    if (pNode == pNode->GetScene()->GetRootNode())
      return true;

    Widgets::PushID(pNode->GetID());

    bool open = Widgets::BeginTreeNode(pNode->GetName(), m_selectedID == pNode->GetID());
    if (Widgets::IsItemClicked()) {
      m_selectedID = m_selectedID == pNode->GetID() ? -1 : pNode->GetID();
    }

    if (!open)
      Widgets::PopID();

    return open;
  }

  virtual void OnLeave(flIN Node* pNode) {
    if (pNode != pNode->GetScene()->GetRootNode())
    {
      Widgets::EndTreeNode();
      Widgets::PopID();
    }
  }

  int64_t m_selectedID;
};

ScenePanel::ScenePanel(GUISystem* pGUI)
  : Panel(pGUI, "Scene")
{
  m_pSceneSystem = Application::Get().GetSubSystem<SceneSystem>();
}

void ScenePanel::OnGUI()
{
  EditorSystem *pEditor = Application::Get().GetSubSystem<EditorSystem>();
  SceneGraph *pScene = m_pSceneSystem->ActiveScene();
  if (Widgets::Button("Add")) {
    Node* pNode = pScene->AddNode("New Node", pEditor->m_selectedNode);
    pEditor->m_selectedNode = pNode->GetID();
  }

  Widgets::Separator();

  GUIVisitor visitor(pEditor->m_selectedNode);
  pScene->Traverse(&visitor, nullptr);
  pEditor->m_selectedNode = visitor.m_selectedID;
}
