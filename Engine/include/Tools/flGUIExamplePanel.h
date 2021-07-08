#pragma once

#include "flPanel.h"

namespace Fractal
{
  class flEXPORT GUIExamplePanel : public Panel
  {
  public:
    GUIExamplePanel(GUIModule* pModule);

    virtual bool Begin() override;
    virtual void End() override;
    virtual void OnGUI() override;
  };
}
