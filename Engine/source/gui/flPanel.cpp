#include "math/flMath.h"
#include "gui/flPanel.h"
#include "imgui/imgui.h"
#include "ctString.h"

using namespace flEngine::Math;

namespace flEngine
{
  namespace GUI
  {
    static int64_t m_nextID = 0;

    class flPIMPL_CLASS(Panel)
    {
    public:
      ctString m_name;
      int64_t m_id = m_nextID++;
      Vec2F m_pos;
      Vec2F m_size;
      Vec2F m_contentAreaSize;
      GUIModule *m_pGUI = nullptr;
    };

    flPIMPL_IMPL(Panel);

    Panel::Panel(flIN GUIModule *pGUI, flIN char const *name)
    {
      Impl()->m_name = name;
      Impl()->m_pGUI = pGUI;
    }

    void Panel::Update()
    {
      ImGui::Begin((Impl()->m_name + "##" + ctString(Impl()->m_id)).c_str());

      ImVec2 contentAreaMin = ImGui::GetWindowContentRegionMin();
      ImVec2 contentAreaMax = ImGui::GetWindowContentRegionMax();

      Impl()->m_pos  = { ImGui::GetWindowPos().x, ImGui::GetWindowPos().y };
      Impl()->m_size = { ImGui::GetWindowWidth(), ImGui::GetWindowHeight() };
      Impl()->m_contentAreaSize = {
        contentAreaMax.x - contentAreaMin.x,
        contentAreaMax.y - contentAreaMin.y
      };

      OnGUI();

      ImGui::End();
    }

    Math::Vec2F GUI::Panel::Position()
    {
      return Impl()->m_pos;
    }

    Math::Vec2F GUI::Panel::Size()
    {
      return Impl()->m_size;
    }

    Math::Vec2F GUI::Panel::ContentAreaSize()
    {
      return Impl()->m_contentAreaSize;
    }

    void Panel::OnGUI() {}

    GUIModule * Panel::GetGUI()
    {
      return Impl()->m_pGUI;
    }

    GUIModule const * Panel::GetGUI() const
    {
      return Impl()->m_pGUI;
    }
  }
}
