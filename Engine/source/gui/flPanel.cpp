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
    };

    flPIMPL_IMPL(Panel);

    Panel::Panel(char const *name)
    {
      Impl()->m_name = name;
    }

    void Panel::Update()
    {
      ImGui::Begin((Impl()->m_name + "##" + ctString(Impl()->m_id)).c_str());
      Impl()->m_pos  = { ImGui::GetWindowPos().x, ImGui::GetWindowPos().y };
      Impl()->m_size = { ImGui::GetWindowWidth(), ImGui::GetWindowHeight() };
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

    void Panel::OnGUI() {}
  }
}
