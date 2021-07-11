#pragma once

#include "flConfig.h"

namespace Fractal
{
  class Texture2D;
  class Colour;

  namespace Widgets
  {
    /**
     * @brief Draw a separator.
     */
    flEXPORT void Separator();

    flEXPORT void PushID(flIN int64_t id);
    flEXPORT void PushID(flIN char const* name);
    flEXPORT void PopID();

    /**
     * @brief Draw a button.
     */
    flEXPORT bool Button(flIN char const* name);

    /**
     * @brief Draw a text label.
     */
    flEXPORT void Label(flIN char const* text);

    /**
     * @brief Draw a check box label.
     */
    flEXPORT bool Checkbox(flIN char const* name, flIN bool* pValue, flIN int64_t count = 1);

    /**
     * @brief Draw a selectable button.
     */
    flEXPORT bool Selectable(flIN char const * name, flIN bool selected);

    /**
     * @brief Draw a float input.
     */
    flEXPORT bool Input(flIN char const* name, flIN float* pValue, flIN int64_t count = 1);

    /**
     * @brief Draw a double input.
     */
    flEXPORT bool Input(flIN char const* name, flIN double* pValue, flIN int64_t count = 1);

    /**
     * @brief Draw an int input.
     */
    flEXPORT bool Input(flIN char const* name, flIN int32_t* pValue, flIN int64_t count = 1);

    /**
     * @brief Draw an int input.
     */
    flEXPORT bool Input(flIN char const* name, flIN uint32_t* pValue, flIN int64_t count = 1);

    /**
     * @brief Draw an int input.
     */
    flEXPORT bool Input(flIN char const* name, flIN int64_t* pValue, flIN int64_t count = 1);

    /**
     * @brief Draw an int input.
     */
    flEXPORT bool Input(flIN char const* name, flIN uint64_t* pValue, flIN int64_t count = 1);

    /**
     * @brief Draw a text input.
     */
    flEXPORT bool Input(flIN char const* name, flIN char* text, flIN int64_t bufferSize);

    /**
     * @brief Draw a colour input.
     */
    flEXPORT bool Input(flIN char const *name, flOUT Colour *pColour);

    /**
     * @brief Draw an image.
     */
    flEXPORT void Image(flIN Texture2D* pTexture, flIN float width, flIN float height);

    /**
     * @brief Draw a collapsing header
     */
    flEXPORT bool CollapsingHeader(flIN char const * name);

    flEXPORT bool BeginMenu(flIN char const * name);

    flEXPORT void EndMenu();

    flEXPORT bool BeginDropdownBox(flIN char const *name, flIN char const *displayItem);
    
    flEXPORT void EndDropdownBox();

    /**
     * @brief Begin a tree node
     */
    flEXPORT bool BeginTreeNode(flIN char const* name, flIN bool isSelected = false, flIN bool isLeaf = false);

    /**
     * @brief End a tree node
     */
    flEXPORT void EndTreeNode();

    /**
     * @brief Check if the last item was clicked
     */
    flEXPORT bool IsItemClicked();

    /**
     * @brief Draw the next widget on the same line as the previous
     */
    flEXPORT void SameLine();
  }
}