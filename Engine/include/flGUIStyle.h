#pragma once

#include "flColour.h"
#include "flInterface.h"

namespace Fractal
{
  enum GUIStyle
  {
    GUIStyle_Alpha,               // float     Alpha
    GUIStyle_WindowPadding,       // ImVec2    WindowPadding
    GUIStyle_WindowRounding,      // float     WindowRounding
    GUIStyle_WindowBorderSize,    // float     WindowBorderSize
    GUIStyle_WindowMinSize,       // ImVec2    WindowMinSize
    GUIStyle_WindowTitleAlign,    // ImVec2    WindowTitleAlign
    GUIStyle_ChildRounding,       // float     ChildRounding
    GUIStyle_ChildBorderSize,     // float     ChildBorderSize
    GUIStyle_PopupRounding,       // float     PopupRounding
    GUIStyle_PopupBorderSize,     // float     PopupBorderSize
    GUIStyle_FramePadding,        // ImVec2    FramePadding
    GUIStyle_FrameRounding,       // float     FrameRounding
    GUIStyle_FrameBorderSize,     // float     FrameBorderSize
    GUIStyle_ItemSpacing,         // ImVec2    ItemSpacing
    GUIStyle_ItemInnerSpacing,    // ImVec2    ItemInnerSpacing
    GUIStyle_IndentSpacing,       // float     IndentSpacing
    GUIStyle_ScrollbarSize,       // float     ScrollbarSize
    GUIStyle_ScrollbarRounding,   // float     ScrollbarRounding
    GUIStyle_GrabMinSize,         // float     GrabMinSize
    GUIStyle_GrabRounding,        // float     GrabRounding
    GUIStyle_TabRounding,         // float     TabRounding
    GUIStyle_ButtonTextAlign,     // ImVec2    ButtonTextAlign
    GUIStyle_SelectableTextAlign, // ImVec2    SelectableTextAlign
  };
  
  // ImGuiCol_Text,
  // ImGuiCol_TextDisabled,
  // ImGuiCol_WindowBg,              // Background of normal windows
  // ImGuiCol_ChildBg,               // Background of child windows
  // ImGuiCol_PopupBg,               // Background of popups, menus, tooltips windows
  // ImGuiCol_Border,
  // ImGuiCol_BorderShadow,
  // ImGuiCol_FrameBg,               // Background of checkbox, radio button, plot, slider, text input
  // ImGuiCol_FrameBgHovered,
  // ImGuiCol_FrameBgActive,
  // ImGuiCol_TitleBg,
  // ImGuiCol_TitleBgActive,
  // ImGuiCol_TitleBgCollapsed,
  // ImGuiCol_MenuBarBg,
  // ImGuiCol_ScrollbarBg,
  // ImGuiCol_ScrollbarGrab,
  // ImGuiCol_ScrollbarGrabHovered,
  // ImGuiCol_ScrollbarGrabActive,
  // ImGuiCol_CheckMark,
  // ImGuiCol_SliderGrab,
  // ImGuiCol_SliderGrabActive,
  // ImGuiCol_Button,
  // ImGuiCol_ButtonHovered,
  // ImGuiCol_ButtonActive,
  // ImGuiCol_Header,
  // ImGuiCol_HeaderHovered,
  // ImGuiCol_HeaderActive,
  // ImGuiCol_Separator,
  // ImGuiCol_SeparatorHovered,
  // ImGuiCol_SeparatorActive,
  // ImGuiCol_ResizeGrip,
  // ImGuiCol_ResizeGripHovered,
  // ImGuiCol_ResizeGripActive,
  // ImGuiCol_Tab,
  // ImGuiCol_TabHovered,
  // ImGuiCol_TabActive,
  // ImGuiCol_TabUnfocused,
  // ImGuiCol_TabUnfocusedActive,
  // ImGuiCol_DockingPreview,
  // ImGuiCol_DockingEmptyBg,        // Background color for empty node (e.g. CentralNode with no window docked into it)
  // ImGuiCol_PlotLines,
  // ImGuiCol_PlotLinesHovered,
  // ImGuiCol_PlotHistogram,
  // ImGuiCol_PlotHistogramHovered,
  // ImGuiCol_TextSelectedBg,
  // ImGuiCol_DragDropTarget,
  // ImGuiCol_NavHighlight,          // Gamepad/keyboard: current highlighted item
  // ImGuiCol_NavWindowingHighlight, // Highlight window when using CTRL+TAB
  // ImGuiCol_NavWindowingDimBg,     // Darken/colorize entire screen behind the CTRL+TAB window list, when active
  // ImGuiCol_ModalWindowDimBg,      // Darken/colorize entire screen behind a modal window, when one is active

  enum GUIColour
  {
    GUIColour_Text,
    GUIColour_TextDisabled,
    GUIColour_MenuBar,
    GUIColour_WindowTitle,
    GUIColour_WindowTitleActive,
    GUIColour_WindowBackground,
    GUIColour_Item,
    GUIColour_ItemActive,
    GUIColour_ItemHovered,
    GUIColour_Input,
    GUIColour_InputActive,
    GUIColour_InputHovered,
    GUIColour_Border,
    GUIColour_BorderShadow,
    GUIColour_Count,
  };

  class flEXPORT GUIStyleElement
  {
    friend class Impl_GUIStyleScope;

  public:
    enum Type
    {
      Type_Colour,
      Type_F32,
      Type_Vec2
    };

    GUIStyleElement(flIN GUIColour colourID, flIN Colour colour);
    GUIStyleElement(flIN GUIStyle  styleID,  flIN float value);
    GUIStyleElement(flIN GUIStyle  styleID,  flIN Vec2F value);

  private:
    float values[4];

    Type    type;
    int64_t elementID; // Either a style or colour ID
    int64_t numPushed;
  };

  class Impl_GUIStyleSheet;

  class flEXPORT GUIStyleSheet : public Interface
  {
    flPIMPL_DEF(GUIStyleSheet);

  public:
    static GUIStyleSheet* Create();

    void Set(GUIStyleElement const * pElements, int64_t count);

    inline void Set(std::initializer_list<GUIStyleElement> const& styles) {
      Set(styles.begin(), styles.size());
    }
  };

  class Impl_GUIStyleScope;

  class flEXPORT GUIStyleScope
  {
    flPIMPL_DEF(GUIStyleScope);
  public:
    GUIStyleScope(GUIStyleSheet *pStyleSheet);
  };
}