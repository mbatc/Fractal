#pragma once

#include "flEngine.h"
#include "EditorSystem.h"
#include "ctString.h"

class PropertiesPanel : public flEngine::GUI::Panel
{
public:
  PropertiesPanel(flEngine::GUI::GUISystem* pGUI);

  virtual void OnGUI() override;
  void DrawComponent(flEngine::Scene::Component* pComponent);
};
