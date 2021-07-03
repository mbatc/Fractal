#include "ScenePanel.h"
#include "ctVector.h"

using namespace Fractal;
class GUIVisitor : public Visitor<Node>
{
public:
  GUIVisitor(int64_t selectedID) : m_selectedID(selectedID) {}

  virtual bool OnEnter(flIN Node* pNode)
  {
    if (pNode == pNode->GetScene()->GetRootNode())
      return true;

    Widgets::PushID(pNode->GetID());

    bool open = Widgets::BeginTreeNode(pNode->GetName(), m_selectedID == pNode->GetID());
    if (Widgets::IsItemClicked())
    {
      m_selectedID = m_selectedID == pNode->GetID() ? -1 : pNode->GetID();
    }

    if (!open)
      Widgets::PopID();

    return open;
  }

  virtual void OnLeave(flIN Node* pNode)
  {
    if (pNode != pNode->GetScene()->GetRootNode())
    {
      Widgets::EndTreeNode();
      Widgets::PopID();
    }
  }

  int64_t m_selectedID;
};

ScenePanel::ScenePanel(GUIModule* pGUI)
  : Panel(pGUI, "Scene")
{
  m_pSceneManager = Application::Get().GetModule<SceneManager>();
}

void ScenePanel::OnGUI()
{
  EditorModule* pEditor = Application::Get().GetModule<EditorModule>();
  SceneGraph* pScene = m_pSceneManager->ActiveScene();
  if (Widgets::Button("Add"))
  {
    bool containsNode = pScene->GetNode(pEditor->m_selectedNode) != nullptr;

    Node* pNode = pScene->AddNode("New Node", containsNode ? pEditor->m_selectedNode : pScene->GetRootNode()->GetID());

    m_pSceneManager->Import(pNode, "C:/Users/mickb/OneDrive/Documents/Test Models/Sponza/sponza.obj");

    pEditor->m_selectedNode = pNode->GetID();
  }

  if (Widgets::Button("Import"))
  {
    GetGlobalThreadPool()->Add(
      MakeTask([=]() {
        SystemDialog::OpenFile dialog(false, true);
        if (dialog.Show(0))
        {
          for (int64_t i = 0; i < dialog.GetSelectedCount(); ++i)
          {
            Node* pNode = nullptr;
            // Need to add the node on the main thread
            Application::Await(MakeTask([&]() { pNode = m_pSceneManager->ActiveScene()->AddNode(); return 0; }));

            if (pNode == nullptr)
              return -1;

            m_pSceneManager->Import(pNode, dialog.GetSelected(i));

            Application::Await(MakeTask([&]() { pNode->SetParent(pScene->GetRootNode()); return 0; }));
          }
        }

        return 0;
      })
    );
  }

  Widgets::Separator();

  GUIVisitor visitor(pEditor->m_selectedNode);
  pScene->Traverse(&visitor, nullptr);
  pEditor->m_selectedNode = visitor.m_selectedID;
}
