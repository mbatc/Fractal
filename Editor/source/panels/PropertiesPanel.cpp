#include "PropertiesPanel.h"

using namespace flEngine;
using namespace flEngine::Scene;
using namespace flEngine::GUI;
using namespace flEngine::Math;

PropertiesPanel::PropertiesPanel(GUISystem* pGUI)
  : Panel(pGUI, "Properties")
{}

void PropertiesPanel::OnGUI()
{
  EditorSystem* pEditor = Application::Get().GetSubSystem<EditorSystem>();
  SceneSystem* pSceneSystem = Application::Get().GetSubSystem<SceneSystem>();

  Node* pNode = pSceneSystem->ActiveScene()->GetNode(pEditor->m_selectedNode);

  if (pNode != nullptr)
  {
    ctString name = pNode->GetName();
    ctVector<char> buffer;
    buffer.insert(0, name.begin(), name.end());
    buffer.resize(name.length() + 64);
    Widgets::Input("Name", buffer.data(), buffer.size());
    pNode->SetName(buffer.data());

    Widgets::Separator();
    for (int64_t i = 0; i < pNode->GetComponentCount(); ++i)
    {
      Component* pComponent = pNode->GetComponent(i);
      Widgets::Label(pComponent->GetType());
      Widgets::Separator();
      DrawComponent(pComponent);
      Widgets::Separator();
    }
  }
}

void PropertiesPanel::DrawComponent(flEngine::Scene::Component* pComponent)
{
  if (pComponent->Is<Transform>())
  {
    Ref<Transform> pTransform = MakeRef(pComponent->As<Transform>(), true);

    static bool localTransform = false;
    if (Widgets::Button(localTransform ? "Local" : "Global"))
      localTransform = !localTransform;

    Vec3D pos = localTransform ? pTransform->GetLocalPosition() : pTransform->GetPosition();
    Vec3D scl = localTransform ? pTransform->GetLocalScale() : pTransform->GetScale();
    Vec3D rot = (localTransform ? pTransform->GetLocalOrientation() : pTransform->GetOrientation()).EulerAngles();

    rot = ctRads2Degs(rot);

    bool changed = Widgets::Input("Position", &pos.x, 3);
    changed |= Widgets::Input("Scale   ", &scl.x, 3);
    changed |= Widgets::Input("Rotation", &rot.x, 3);

    rot = ctDegs2Rads(rot);

    if (changed)
    {
      if (localTransform)
      {
        pTransform->SetLocalScale(scl);
        pTransform->SetLocalPosition(pos);
        pTransform->SetLocalOrientation(QuatD(rot.x, rot.y, rot.z));
      }
      else
      {
        pTransform->SetScale(scl);
        pTransform->SetPosition(pos);
        pTransform->SetOrientation(QuatD(rot.x, rot.y, rot.z));
      }
    }
  }
}
