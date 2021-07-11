#include "flWidgets.h"
#include "flColour.h"
#include "imgui/imgui.h"

namespace Fractal
{
  namespace Widgets
  {
    void Separator()
    {
      ImGui::Separator();
    }

    void PushID(flIN int64_t id)
    {
      ImGui::PushID((int)id);
    }

    void PushID(flIN char const* name)
    {
      ImGui::PushID(name);
    }

    void PopID()
    {
      ImGui::PopID();
    }

    bool Button(flIN char const* name)
    {
      return ImGui::Button(name);
    }

    void Label(flIN char const* text)
    {
      ImGui::Text(text);
    }

    bool Selectable(flIN char const * name, flIN bool selected)
    {
      return ImGui::Selectable(name, selected);
    }

    bool Checkbox(flIN char const* name, flIN bool* pValue, flIN int64_t count)
    {
      return ImGui::Checkbox(name, pValue);
    }

    bool Input(flIN char const* name, flIN float* pValue, flIN int64_t count)
    {
      return ImGui::InputScalarN(name, ImGuiDataType_Float, pValue, (int)count);
    }

    bool Input(flIN char const* name, flIN double* pValue, flIN int64_t count)
    {
      return ImGui::InputScalarN(name, ImGuiDataType_Double, pValue, (int)count);
    }

    bool Input(flIN char const* name, flIN int32_t* pValue, flIN int64_t count)
    {
      return ImGui::InputScalarN(name, ImGuiDataType_S32, pValue, (int)count);
    }

    bool Input(flIN char const* name, flIN uint32_t* pValue, flIN int64_t count)
    {
      return ImGui::InputScalarN(name, ImGuiDataType_U32, pValue, (int)count);
    }

    bool Input(flIN char const* name, flIN int64_t* pValue, flIN int64_t count)
    {
      return ImGui::InputScalarN(name, ImGuiDataType_S64, pValue, (int)count);
    }

    bool Input(flIN char const* name, flIN uint64_t* pValue, flIN int64_t count)
    {
      return ImGui::InputScalarN(name, ImGuiDataType_U64, pValue, (int)count);
    }

    bool Input(flIN char const* name, flIN char* text, flIN int64_t bufferSize)
    {
      return ImGui::InputText(name, text, (size_t)bufferSize);
    }

    bool Input(flIN char const *name, flOUT Colour *pColour)
    {
      return ImGui::ColorEdit4(name, pColour->channel);
    }

    void Image(flIN Texture2D* pTexture, flIN float width, flIN float height)
    {
      ImGui::Image(ImTextureID(pTexture), ImVec2((float)width, (float)height), ImVec2(0, 1), ImVec2(1, 0));
    }

    bool CollapsingHeader(flIN char const * name)
    {
      return ImGui::CollapsingHeader(name);
    }

    bool BeginMenu(flIN char const * name)
    {
      return ImGui::BeginMenu(name);
    }

    void EndMenu()
    {
      return ImGui::EndMenu();
    }

    bool BeginDropdownBox(flIN char const *name, flIN char const *displayItem)
    {
      return ImGui::BeginCombo(name, displayItem);
    }
    
    void EndDropdownBox()
    {
      return ImGui::EndCombo();
    }

    bool BeginTreeNode(flIN char const* name, flIN bool isSelected, flIN bool isLeaf)
    {
      return ImGui::TreeNodeEx(name, (ImGuiTreeNodeFlags_Selected * isSelected) | (isLeaf ? ImGuiTreeNodeFlags_Leaf : ImGuiTreeNodeFlags_OpenOnArrow));
    }

    void EndTreeNode()
    {
      ImGui::TreePop();
    }

    bool IsItemClicked()
    {
      return ImGui::IsItemClicked();
    }

    void SameLine()
    {
      return ImGui::SameLine();
    }
  }
}
