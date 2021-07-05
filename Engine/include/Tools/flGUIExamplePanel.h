#pragma once

#include "flPanel.h"

namespace Fractal
{
  class Impl_GUIExamplePanel;

  class GUIExamplePanel : public Panel
  {
    flPIMPL_DEF(GUIExamplePanel);

  public:
    GUIExamplePanel(GUIModule *pModule);

    ~GUIExamplePanel();

    virtual void OnGUI() override;
  };
}
