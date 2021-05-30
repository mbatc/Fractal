#ifndef ScenePanel_h__
#define ScenePanel_h__

#include "flEngine.h"

class ScenePanel : public flEngine::GUI::Panel
{
public:
  ScenePanel(flEngine::GUI::GUISystem *pGUI)
    : Panel(pGUI, "Scene")
  {}

  virtual void OnGUI() override
  {

  }
};

#endif // ScenePanel_h__
