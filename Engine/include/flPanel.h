#pragma once

#include "flApplicationBehaviour.h"
#include "flMath.h"

namespace Fractal
{
  class GUIModule;
  class GUIStyleSheet;

  class Impl_Panel;

  class flEXPORT Panel : public ApplicationBehaviour
  {
    flPIMPL_DEF(Panel);

  public:
    /**
     * @brief Construct a new GUI Panel.
     *
     * @param [in] pGUI A pointer to the parent GUI.
     * @param [in] name The name of the panel as a c-string.
     */
    Panel(flIN GUIModule* pGUI, flIN char const* name);

    /**
     * @brief Update the Panel.
     *
     * This function is called by the engine. You should not need to call this manually.
     */
    void Update();

    /**
     * @brief Draw the GUI Panel.
     *
     * This is called within a valid GUI window context. Draw any required widgets here.
     */
    virtual void OnGUI() = 0;

    /**
     * @brief Get the position of the window.
     *
     * @return A Vector2 contain the position.
     */
    Vec2F Position();

    /**
     * @brief Get the size of the window.
     *
     * @return A Vector2 contain the dimensions.
     */
    Vec2F Size();

    /**
     * @brief Get the size of the windows drawable area.
     *
     * @return A Vector2 contain the dimensions.
     */
    Vec2F ContentAreaSize();

    /**
     * @brief Get a pointer to the GUI that this Panel belongs to.
     *
     * @return A pointer to the GUI.
     */
    GUIModule* GetGUI();

    /**
     * @brief Get a const pointer to the GUI that this Panel belongs to.
     *
     * @return A const pointer to the GUI.
     */
    GUIModule const* GetGUI() const;

    GUIStyleSheet* GetStyle();

    GUIStyleSheet const* GetStyle() const;
  };
}