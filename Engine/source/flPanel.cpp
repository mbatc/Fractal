#include "flPanel.h"
#include "flGUIStyle.h"
#include "flRef.h"

#include "imgui/imgui.h"

#include "ctString.h"

namespace Fractal
{
  static int64_t m_nextID = 0;

  class Impl_Panel
  {
  public:
    ctString m_name;
    int64_t m_id = m_nextID++;
    Vec2F m_pos;
    Vec2F m_size;
    Vec2F m_contentAreaSize;
    bool  m_isOpen = false;
    GUIModule* m_pGUI = nullptr;
    Ref<GUIStyleSheet> m_pStyleSheet;
  };

  flPIMPL_IMPL(Panel);

  Panel::Panel(flIN GUIModule* pGUI, flIN char const* name)
  {
    Impl()->m_name = name;
    Impl()->m_pGUI = pGUI;
    Impl()->m_pStyleSheet = MakeRef<GUIStyleSheet>();
  }

  bool Panel::Begin()
  {
    if (!Impl()->m_isOpen)
      return false;

    ImGui::Begin((Impl()->m_name + "##" + ctString(Impl()->m_id)).c_str(), &Impl()->m_isOpen);
    return true;
  }

  void Panel::End()
  {
    ImGui::End();
  }

  void Panel::Open()
  {
    Impl()->m_isOpen = true;
  }

  void Panel::Close()
  {
    Impl()->m_isOpen = false;
  }

  bool Panel::IsOpen() const
  {
    return Impl()->m_isOpen;
  }

  void Panel::Update()
  {
    if (Begin())
    {
      ImVec2 contentAreaMin = ImGui::GetWindowContentRegionMin();
      ImVec2 contentAreaMax = ImGui::GetWindowContentRegionMax();

      Impl()->m_pos = {ImGui::GetWindowPos().x, ImGui::GetWindowPos().y};
      Impl()->m_size = {ImGui::GetWindowWidth(), ImGui::GetWindowHeight()};
      Impl()->m_contentAreaSize =
      {
        contentAreaMax.x - contentAreaMin.x,
        contentAreaMax.y - contentAreaMin.y
      };

      OnGUI();
      End();
    }
  }

  void Panel::OnCreate()  {}
  void Panel::OnOpen()    {}
  void Panel::OnClose()   {}
  void Panel::OnDestroy() {}

  Vec2F Panel::Position()
  {
    return Impl()->m_pos;
  }

  Vec2F Panel::Size()
  {
    return Impl()->m_size;
  }

  Vec2F Panel::ContentAreaSize()
  {
    return Impl()->m_contentAreaSize;
  }

  void Panel::OnGUI() {}

  GUIModule* Panel::GetGUI()
  {
    return Impl()->m_pGUI;
  }

  GUIModule const* Panel::GetGUI() const
  {
    return Impl()->m_pGUI;
  }
  GUIStyleSheet* Panel::GetStyle()
  {
    return Impl()->m_pStyleSheet;
  }

  GUIStyleSheet const* Panel::GetStyle() const
  {
    return Impl()->m_pStyleSheet;
  }
}
