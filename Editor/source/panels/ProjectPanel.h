#ifndef ProjectPanel_h__
#define ProjectPanel_h__

#include "flEngine.h"

class ProjectPanel : public flEngine::GUI::Panel
{
public:
  ProjectPanel(flEngine::GUI::GUISystem *pGUI)
    : Panel(pGUI, "Project")
  {

  }

  virtual void OnGUI() override
  {

  }
};

#endif // ProjectPanel_h__
