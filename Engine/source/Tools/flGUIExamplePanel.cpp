#include "tools/flGUIExamplePanel.h"
#include "imgui/imgui.h"

namespace Fractal
{
  GUIExamplePanel::GUIExamplePanel(GUIModule *pModule)
    : Panel(pModule, "Example Panel")
  {}

  GUIExamplePanel::~GUIExamplePanel()
  {

  }

  void GUIExamplePanel::OnGUI()
  {
    ImGui::ShowDemoWindow();
  }
}
