#pragma once

#include "flConfig.h"

namespace flEngine
{
  namespace Graphics { class Texture2D; }

  namespace GUI
  {
    class flEXPORT ScopeID
    {
    public:
      ScopeID(char const * id);
      ScopeID(int64_t id);
      ~ScopeID();
    };

    namespace Widgets
    {
      /**
       * @brief Draw a separator.
       */
      flEXPORT void Separator();

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
      flEXPORT bool Checkbox(flIN char const* name, flIN bool* pValue);

      /**
       * @brief Draw a float input.
       */
      flEXPORT bool Input(flIN char const* name, flIN float* pValue);

      /**
       * @brief Draw an int input.
       */
      flEXPORT bool Input(flIN char const* name, flIN int* pValue);

      /**
       * @brief Draw a text input.
       */
      flEXPORT bool Input(flIN char const* name, flIN char* text, flIN int64_t bufferSize);

      /**
       * @brief Draw an image.
       */
      flEXPORT void Image(flIN Graphics::Texture2D* pTexture, flIN float width, flIN float height);

      flEXPORT bool BeginTreeNode(flIN char const* name, flIN bool isSelected = false);

      flEXPORT void EndTreeNode();

      flEXPORT bool IsItemClicked();
    }
  }
}