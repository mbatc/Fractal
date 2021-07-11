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
    if (Widgets::BeginMenu("Add Component"))
    {
      for (int64_t i = 0; i < ComponentRegistry::ComponentCount(); ++i)
      {
        if (pNode->GetComponentByType(i) == nullptr)
        {
          char const * componentTypeName = ComponentRegistry::GetComponentName(i);
          if (Widgets::Selectable(componentTypeName, false))
            pNode->AddComponent(componentTypeName);
        }
      }

      Widgets::EndMenu();
    }
    Widgets::Separator();
    for (int64_t i = 0; i < pNode->GetComponentCount(); ++i)
    {
      Component* pComponent = pNode->GetComponent(i);
      if (!Widgets::CollapsingHeader(pComponent->GetType()))
        continue;
      DrawComponent(pComponent);
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

  if (pComponent->Is<MeshRenderer>())
  {
    MeshRenderer *pMesh = pComponent->As<MeshRenderer>();
  }

  if (pComponent->Is<Light>())
  {
    Light *pLight = pComponent->As<Light>();

    static char const * lightTypeName[LightType_Count] = { "Sun", "Point Light", "Spot Light" };

    if (Widgets::BeginDropdownBox("Light Type", lightTypeName[pLight->GetLightType()]))
    {
      for (int64_t i = 0; i < LightType_Count; ++i)
        if (Widgets::Selectable(lightTypeName[i], i == pLight->GetLightType()))
          pLight->SetLightType(LightType(i));
      Widgets::EndDropdownBox();
    }

    // Get the properties
    Colour diffuse   = pLight->GetDiffuse();
    Colour ambient   = pLight->GetAmbient();
    double strength  = pLight->GetStrength();
    double falloff   = pLight->GetFalloff();
    double innerConeAngle = ctRads2Degs(pLight->GetInnerConeAngle());
    double outerConeAngle = ctRads2Degs(pLight->GetOuterConeAngle());

    // Draw inputs for each light type
    switch (pLight->GetLightType())
    {
    case LightType_Sun:
      Widgets::Input("Colour",   &diffuse);
      Widgets::Input("Ambient",  &ambient);
      Widgets::Input("Strength", &strength);
      break;
    case LightType_Point:
      Widgets::Input("Colour",   &diffuse);
      Widgets::Input("Strength", &strength);
      Widgets::Input("Falloff",  &falloff);
      break;
    case LightType_Spot:
      Widgets::Input("Colour",   &diffuse);
      Widgets::Input("Strength", &strength);
      Widgets::Input("Falloff",  &falloff);
      Widgets::Input("Inner Cone Angle", &innerConeAngle);
      Widgets::Input("Outer Cone Angle", &outerConeAngle);
      break;
    }

    // Apply changes
    pLight->SetDiffuse(diffuse);
    pLight->SetAmbient(ambient);
    pLight->SetStrength(strength);
    pLight->SetFalloff(falloff);
    pLight->SetInnerConeAngle(ctDegs2Rads(innerConeAngle));
    pLight->SetOuterConeAngle(ctDegs2Rads(outerConeAngle));
  }

  if (pComponent->Is<Camera>())
  {
    Camera *pCamera = pComponent->As<Camera>();
  }
}
