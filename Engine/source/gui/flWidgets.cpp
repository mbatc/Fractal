#include "gui/flWidgets.h"
#include "imgui/imgui.h"

namespace flEngine
{
  namespace GUI
  {
    namespace Widgets
    {
      flEXPORT void Separator()
      {
        ImGui::Separator();
      }

      flEXPORT void Label(char const *text)
      {
        ImGui::Text(text);
      }

      flEXPORT bool Checkbox(char const *name, bool *pValue)
      {
        return ImGui::Checkbox(name, pValue);
      }

      flEXPORT bool Input(char const *name, float *pValue)
      {
        return ImGui::InputFloat(name, pValue);
      }
      
      flEXPORT bool Input(char const *name, int *pValue)
      {
        return ImGui::InputInt(name, pValue);
      }

      flEXPORT bool Input(char const *name, char *text, int64_t bufferSize)
      {
        return ImGui::InputText(name, text, (size_t)bufferSize);
      }
    }
  }
}
