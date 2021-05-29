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

      flEXPORT void Label(flIN char const *text)
      {
        ImGui::Text(text);
      }

      flEXPORT bool Checkbox(flIN char const *name, flIN bool *pValue)
      {
        return ImGui::Checkbox(name, pValue);
      }

      flEXPORT bool Input(flIN char const *name, flIN float *pValue)
      {
        return ImGui::InputFloat(name, pValue);
      }
      
      flEXPORT bool Input(flIN char const *name, flIN int *pValue)
      {
        return ImGui::InputInt(name, pValue);
      }

      flEXPORT bool Input(flIN char const *name, flIN char *text, flIN int64_t bufferSize)
      {
        return ImGui::InputText(name, text, (size_t)bufferSize);
      }

      flEXPORT void Image(flIN Graphics::Texture2D *pTexture, flIN float width, flIN float height)
      {
        ImGui::Image(ImTextureID(pTexture), ImVec2((float)width, (float)height), ImVec2(0, 1), ImVec2(1, 0));
      }
    }
  }
}
