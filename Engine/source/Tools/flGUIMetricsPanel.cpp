#include "tools/flGUIMetricsPanel.h"
#include "imgui/imgui.h"

namespace Fractal
{
  GUIMetricsPanel::GUIMetricsPanel(GUIModule* pGUI) : Panel(pGUI, "Metrics") {}

  bool GUIMetricsPanel::Begin() { return IsOpen(); }
  void GUIMetricsPanel::End()   {}

  void GUIMetricsPanel::OnGUI()
  {
    bool open = true;
    ImGui::ShowMetricsWindow(&open);

    if (!open)
      Close();
  }
}