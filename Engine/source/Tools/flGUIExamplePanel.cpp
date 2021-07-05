#include "tools/flGUIExamplePanel.h"
#include "imgui/imgui.h"

namespace Fractal
{
  GUIExamplePanel::GUIExamplePanel(GUIModule* pModule)
    : Panel(pModule, "Example Panel")
  {}

  // Do nothing because it is handled by ShowDemoWindow
  bool GUIExamplePanel::Begin() { return IsOpen(); }
  void GUIExamplePanel::End()   {}

  void GUIExamplePanel::OnGUI()
  {
    bool open = true;
    ImGui::ShowDemoWindow(&open);
    if (!open)
      Close();
  }
}
