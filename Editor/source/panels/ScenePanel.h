#ifndef ScenePanel_h__
#define ScenePanel_h__

#include "flEngine.h"
#include "EditorSystem.h"
#include "SceneSystem.h"
#include "ctVector.h"

class ScenePanel : public flEngine::GUI::Panel
{
  class GUIVisitor : public flEngine::Scene::Visitor
  {
  public:
    GUIVisitor(int64_t selectedID) : m_selectedID(selectedID) {}

    virtual bool OnEnterNode(flIN flEngine::Scene::Node* pNode) {
      if (pNode == pNode->GetScene()->GetRootNode())
        return true;

      m_idStack.emplace_back(pNode->GetID());

      bool open = flEngine::GUI::Widgets::BeginTreeNode(pNode->GetName(), m_selectedID == pNode->GetID());
      if (flEngine::GUI::Widgets::IsItemClicked()) {
        m_selectedID = m_selectedID == pNode->GetID() ? -1 : pNode->GetID();
      }

      if (!open)
        m_idStack.pop_back();

      return open;
    }

    virtual void OnLeaveNode(flIN flEngine::Scene::Node* pNode) {
      if (pNode != pNode->GetScene()->GetRootNode())
      {
        flEngine::GUI::Widgets::EndTreeNode();
        m_idStack.pop_back();
      }
    }

    int64_t m_selectedID;
    ctVector<flEngine::GUI::ScopeID> m_idStack;
  };

public:
  ScenePanel(flEngine::GUI::GUISystem* pGUI)
    : Panel(pGUI, "Scene")
  {
    m_pSceneSystem = flEngine::Application::Get().GetSubSystem<SceneSystem>();;
  }

  virtual void OnGUI() override
  {
    flEngine::Ref<EditorSystem> pEditor = flEngine::Application::Get().GetSubSystem<EditorSystem>();
    flEngine::Ref<flEngine::Scene::Scene> pScene = m_pSceneSystem->ActiveScene();
    if (flEngine::GUI::Widgets::Button("Add")) {
      flEngine::Scene::Node* pNode = pScene->AddNode("Node Node", pEditor->m_selectedNode);
      pEditor->m_selectedNode = pNode->GetID();
    }

    flEngine::GUI::Widgets::Separator();

    GUIVisitor visitor(pEditor->m_selectedNode);
    visitor.VisitNode(pScene->GetRootNode());
    pEditor->m_selectedNode = visitor.m_selectedID;
  }

private:
  flEngine::Ref<SceneSystem> m_pSceneSystem;
};

#endif // ScenePanel_h__
