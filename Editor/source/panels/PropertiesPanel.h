#ifndef PropertiesPanel_h__
#define PropertiesPanel_h__

#include "gui/flPanel.h"

class PropertiesPanel : public flEngine::GUI::Panel
{
public:
  PropertiesPanel(flEngine::GUI::GUISystem *pGUI)
    : Panel(pGUI, "Properties")
  {}

  virtual void OnGUI() override
  {

  }
};

#endif // PropertiesPanel_h__
