#pragma once

#include "flEngine.h"
#include "EditorModule.h"
#include "ctString.h"

class PropertiesPanel : public flEngine::GUI::Panel
{
public:
  PropertiesPanel(flEngine::GUI::GUIModule* pGUI);

  virtual void OnGUI() override;
  void DrawComponent(flEngine::Scene::Component* pComponent);
};
