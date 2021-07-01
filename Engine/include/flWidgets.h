#pragma once

#include "flConfig.h"

namespace Fractal
{
  class Texture2D;

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
     * @brief Draw an image.
     */
    flEXPORT void Image(flIN Texture2D* pTexture, flIN float width, flIN float height);

    flEXPORT bool BeginTreeNode(flIN char const* name, flIN bool isSelected = false);

    flEXPORT void EndTreeNode();

    flEXPORT bool IsItemClicked();
  }
}