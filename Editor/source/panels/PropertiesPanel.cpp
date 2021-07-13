#include "PropertiesPanel.h"

using namespace Fractal;

PropertiesPanel::PropertiesPanel(GUIModule* pGUI)
  : Panel(pGUI, "Properties")
{}

void PropertiesPanel::OnGUI()
{
  EditorModule* pEditor = GetApplication()->GetModule<EditorModule>();
  SceneManager* pSceneSystem = GetApplication()->GetModule<SceneManager>();

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

void PropertiesPanel::DrawComponent(Component* pComponent)
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

    rot = Vec3D(Rads2Degs(rot.x), Rads2Degs(rot.y), Rads2Degs(rot.z));

    bool changed = Widgets::Input("Position", &pos.x, 3);
    changed |= Widgets::Input("Scale   ", &scl.x, 3);
    changed |= Widgets::Input("Rotation", &rot.x, 3);

    rot = Vec3D(Degs2Rads(rot.x), Degs2Rads(rot.y), Degs2Rads(rot.z));

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
