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

      flEXPORT void PushID(flIN int64_t id)
      {
        ImGui::PushID((int)id);
      }

      flEXPORT void PushID(flIN char const* name)
      {
        ImGui::PushID(name);
      }

      flEXPORT void PopID()
      {
        ImGui::PopID();
      }

      flEXPORT bool Button(flIN char const* name)
      {
        return ImGui::Button(name);
      }

      flEXPORT void Label(flIN char const* text)
      {
        ImGui::Text(text);
      }

      flEXPORT bool Checkbox(flIN char const* name, flIN bool* pValue, flIN int64_t count)
      {
        return ImGui::Checkbox(name, pValue);
      }

      flEXPORT bool Input(flIN char const* name, flIN float* pValue, flIN int64_t count)
      {
        return ImGui::InputScalarN(name, ImGuiDataType_Float, pValue, (int)count);
      }

      flEXPORT bool Input(flIN char const* name, flIN double* pValue, flIN int64_t count)
      {
        return ImGui::InputScalarN(name, ImGuiDataType_Double, pValue, (int)count);
      }

      flEXPORT bool Input(flIN char const* name, flIN int32_t* pValue, flIN int64_t count)
      {
        return ImGui::InputScalarN(name, ImGuiDataType_S32, pValue, (int)count);
      }

      flEXPORT bool Input(flIN char const* name, flIN uint32_t* pValue, flIN int64_t count)
      {
        return ImGui::InputScalarN(name, ImGuiDataType_U32, pValue, (int)count);
      }

      flEXPORT bool Input(flIN char const* name, flIN int64_t* pValue, flIN int64_t count)
      {
        return ImGui::InputScalarN(name, ImGuiDataType_S64, pValue, (int)count);
      }

      flEXPORT bool Input(flIN char const* name, flIN uint64_t* pValue, flIN int64_t count)
      {
        return ImGui::InputScalarN(name, ImGuiDataType_U64, pValue, (int)count);
      }

      flEXPORT bool Input(flIN char const* name, flIN char* text, flIN int64_t bufferSize)
      {
        return ImGui::InputText(name, text, (size_t)bufferSize);
      }

      flEXPORT void Image(flIN Graphics::Texture2D* pTexture, flIN float width, flIN float height)
      {
        ImGui::Image(ImTextureID(pTexture), ImVec2((float)width, (float)height), ImVec2(0, 1), ImVec2(1, 0));
      }

      flEXPORT bool BeginTreeNode(flIN char const* name, flIN bool isSelected)
      {
        return ImGui::TreeNodeEx(name, (ImGuiTreeNodeFlags_Selected * isSelected) | ImGuiTreeNodeFlags_OpenOnArrow);
      }

      flEXPORT void EndTreeNode()
      {
        ImGui::TreePop();
      }

      flEXPORT bool IsItemClicked()
      {
        return ImGui::IsItemClicked();
      }
    }
  }
}
