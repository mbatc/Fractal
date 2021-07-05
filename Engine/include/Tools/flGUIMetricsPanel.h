#pragma once

#include "flPanel.h"

namespace Fractal
{
  class flEXPORT GUIMetricsPanel : public Panel
  {
  public:
    GUIMetricsPanel(Fractal::GUIModule* pGUI);

    // Do nothing because it is handled by ShowDemoWindow
    virtual bool Begin() override;
    virtual void End() override;
    virtual void OnGUI() override;
  };
}
