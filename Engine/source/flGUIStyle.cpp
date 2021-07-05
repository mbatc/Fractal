#include "flGUIStyle.h"
#include "imgui/imgui.h"

#include "ctVector.h"

namespace Fractal
{
  static int64_t PushColour(int64_t const& colourID, Vec4F const& col);
  template<typename T>
  static int64_t PushStyle(int64_t const& styleID, T const& col);

  GUIStyleElement::GUIStyleElement(flIN GUIColour colourID, flIN Colour colour)
  {
    numPushed = 0;
    elementID = colourID;
    values[0] = colour.r; values[1] = colour.g; values[2] = colour.b; values[3] = colour.a;
    type = Type_Colour;
  }

  GUIStyleElement::GUIStyleElement(flIN GUIStyle styleID, flIN float value)
  {
    numPushed = 0;
    elementID = styleID;
    values[0] = value;
    type = Type_F32;
  }

  GUIStyleElement::GUIStyleElement(flIN GUIStyle styleID, flIN Vec2F value)
  {
    numPushed = 0;
    elementID = styleID;
    values[0] = value.x;
    values[1] = value.y;
    type = Type_Vec2;
  }

  class Impl_GUIStyleSheet
  {
  public:
    ctVector<GUIStyleElement> elements;
  };

  flPIMPL_IMPL(GUIStyleSheet);

  GUIStyleSheet* GUIStyleSheet::Create()
  {
    return flNew GUIStyleSheet;
  }

  void GUIStyleSheet::Set(GUIStyleElement const* pElements, int64_t count)
  {
    Impl()->elements = ctVector(pElements, count);
  }

  class Impl_GUIStyleScope
  {
  public:
    void Construct(GUIStyleSheet* pStyleSheet)
    {
      for (GUIStyleElement& element : pStyleSheet->Impl()->elements)
      {
        float const* f = element.values;
        switch (element.type)
        {
        case GUIStyleElement::Type_Colour: coloursPushed += PushColour(element.elementID, Vec4F(f[0], f[1], f[2], f[3]));   break;
        case GUIStyleElement::Type_F32:    stylesPushed  += PushStyle(element.elementID, f[0]);    break;
        case GUIStyleElement::Type_Vec2:   stylesPushed  += PushStyle(element.elementID,  ImVec2(f[0], f[1])); break;
        }
      }
    }

    ~Impl_GUIStyleScope()
    {
      if (coloursPushed > 0)
        ImGui::PopStyleColor((int)coloursPushed);
      if (stylesPushed > 0)
        ImGui::PopStyleVar((int)stylesPushed);
    }

    int64_t coloursPushed = 0;
    int64_t stylesPushed = 0;
  };

  flPIMPL_IMPL(GUIStyleScope);

  GUIStyleScope::GUIStyleScope(GUIStyleSheet* pStyleSheet)
  {
    Impl()->Construct(pStyleSheet);
  }

  static ctVector<ImGuiCol> _GetStyleColours(int64_t const& colourID)
  {
    switch (colourID)
    {
    case GUIColour_Text:
      return
      {
        ImGuiCol_Text
      };

    case GUIColour_TextDisabled:
      return
      {
        ImGuiCol_TextDisabled
      };

    case GUIColour_MenuBar:
      return
      {
        ImGuiCol_MenuBarBg
      };

    case GUIColour_WindowTitle:
      return
      {
        ImGuiCol_TitleBg
      };

    case GUIColour_WindowTitleActive:
      return
      {
        ImGuiCol_TitleBgActive
      };

    case GUIColour_WindowBackground:
      return
      {
        ImGuiCol_WindowBg,
        ImGuiCol_ChildBg
      };

    case GUIColour_Item:
      return
      {
        ImGuiCol_Button,
        ImGuiCol_Header,
        ImGuiCol_Separator,
        ImGuiCol_SliderGrab,
        ImGuiCol_ResizeGrip
      };

    case GUIColour_ItemActive:
      return
      {
        ImGuiCol_ButtonActive,
        ImGuiCol_HeaderActive,
        ImGuiCol_ResizeGripActive,
        ImGuiCol_SliderGrabActive,
        ImGuiCol_SeparatorActive,
        ImGuiCol_CheckMark
      };

    case GUIColour_ItemHovered:
      return
      {
        ImGuiCol_ButtonHovered,
        ImGuiCol_HeaderHovered,
        ImGuiCol_SeparatorHovered,
        ImGuiCol_ResizeGripHovered
      };

    case GUIColour_Input:
      return
      {
        ImGuiCol_FrameBg
      };

    case GUIColour_InputActive:
      return
      {
        ImGuiCol_FrameBgActive
      };

    case GUIColour_InputHovered:
      return
      {
        ImGuiCol_FrameBgHovered
      };

    case GUIColour_Border:
      return
      {
        ImGuiCol_Border
      };

    case GUIColour_BorderShadow:
      return
      {
        ImGuiCol_BorderShadow
      };
    }

    return {};
  }

  int64_t PushColour(int64_t const& colourID, Vec4F const& col)
  {
    ImVec4 imCol(col.x, col.y, col.z, col.w);
    ctVector<ImGuiCol> imColours = _GetStyleColours(colourID);
    for (ImGuiCol const& colID : imColours)
      ImGui::PushStyleColor(colID, imCol);
    return imColours.size();
  }

  template<typename T>
  int64_t PushStyle(int64_t const& styleID, T const& col)
  {
    switch (styleID)
    {
    case GUIStyle_Alpha:               ImGui::PushStyleVar(ImGuiStyleVar_Alpha, col); break; // float     Alpha
    case GUIStyle_WindowPadding:       ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, col); break; // ImVec2    WindowPadding
    case GUIStyle_WindowRounding:      ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, col); break; // float     WindowRounding
    case GUIStyle_WindowBorderSize:    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, col); break; // float     WindowBorderSize
    case GUIStyle_WindowMinSize:       ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, col); break; // ImVec2    WindowMinSize
    case GUIStyle_WindowTitleAlign:    ImGui::PushStyleVar(ImGuiStyleVar_WindowTitleAlign, col); break; // ImVec2    WindowTitleAlign
    case GUIStyle_ChildRounding:       ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, col); break; // float     ChildRounding
    case GUIStyle_ChildBorderSize:     ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, col); break; // float     ChildBorderSize
    case GUIStyle_PopupRounding:       ImGui::PushStyleVar(ImGuiStyleVar_PopupRounding, col); break; // float     PopupRounding
    case GUIStyle_PopupBorderSize:     ImGui::PushStyleVar(ImGuiStyleVar_PopupBorderSize, col); break; // float     PopupBorderSize
    case GUIStyle_FramePadding:        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, col); break; // ImVec2    FramePadding
    case GUIStyle_FrameRounding:       ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, col); break; // float     FrameRounding
    case GUIStyle_FrameBorderSize:     ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, col); break; // float     FrameBorderSize
    case GUIStyle_ItemSpacing:         ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, col); break; // ImVec2    ItemSpacing
    case GUIStyle_ItemInnerSpacing:    ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, col); break; // ImVec2    ItemInnerSpacing
    case GUIStyle_IndentSpacing:       ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, col); break; // float     IndentSpacing
    case GUIStyle_ScrollbarSize:       ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarSize, col); break; // float     ScrollbarSize
    case GUIStyle_ScrollbarRounding:   ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarRounding, col); break; // float     ScrollbarRounding
    case GUIStyle_GrabMinSize:         ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, col); break; // float     GrabMinSize
    case GUIStyle_GrabRounding:        ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding, col); break; // float     GrabRounding
    case GUIStyle_TabRounding:         ImGui::PushStyleVar(ImGuiStyleVar_TabRounding, col); break; // float     TabRounding
    case GUIStyle_ButtonTextAlign:     ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, col); break; // ImVec2    ButtonTextAlign
    case GUIStyle_SelectableTextAlign: ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, col); break; // ImVec2    SelectableTextAlign
    default: return 0;
    }

    return 1;
  }
}
