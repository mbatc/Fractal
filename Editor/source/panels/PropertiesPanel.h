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

    Scene::Node *pNode = pSceneSystem->ActiveScene()->GetNode(pEditor->m_selectedNode);

    if (pNode != nullptr)
    {
      ctString name = pNode->GetName();
      ctVector<char> buffer;
      buffer.insert(0, name.begin(), name.end());
      buffer.resize(name.length() + 64);
      flEngine::GUI::Widgets::Input("Name", buffer.data(), buffer.size());
      pNode->SetName(buffer.data());

      flEngine::GUI::Widgets::Separator();
      for (int64_t i = 0; i < pNode->GetComponentCount(); ++i)
      {
        flEngine::Scene::Component* pComponent = pNode->GetComponentByIndex(i);
        flEngine::GUI::Widgets::Label(pComponent->GetType());
        flEngine::GUI::Widgets::Separator();
        DrawComponent(pComponent);
        flEngine::GUI::Widgets::Separator();
      }
    }
  }

  void DrawComponent(flEngine::Scene::Component * pComponent)
  {
    if (pComponent->Is<flEngine::Scene::Transform>())
    {
      flEngine::Ref<flEngine::Scene::Transform> pTransform = pComponent->As<flEngine::Scene::Transform>();


      static bool localTransform = false;
      if (flEngine::GUI::Widgets::Button(localTransform ? "Local" : "Global"))
        localTransform = !localTransform;

      Vec3D pos = localTransform ? pTransform->GetLocalPosition() : pTransform->GetPosition();
      Vec3D scl = localTransform ? pTransform->GetLocalScale() : pTransform->GetScale();
      Vec3D rot = (localTransform ? pTransform->GetLocalOrientation() : pTransform->GetOrientation()).EulerAngles();

      bool changed = flEngine::GUI::Widgets::Input("Position", &pos.x, 3);
      changed     |= flEngine::GUI::Widgets::Input("Scale   ", &scl.x, 3);
      changed     |= flEngine::GUI::Widgets::Input("Rotation", &rot.x, 3);

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
};

#endif // PropertiesPanel_h__
