#pragma once

#include "flEngine.h"
#include "EditorModule.h"
#include "ctString.h"

class PropertiesPanel : public Fractal::Panel
{
public:
  PropertiesPanel(Fractal::GUIModule* pGUI);

  virtual void OnGUI() override;
  void DrawComponent(Fractal::Component* pComponent);
};
