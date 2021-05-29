#pragma once

#include "flConfig.h"

namespace flEngine
{
  namespace Graphics { class Texture2D; }

  namespace GUI
  {
    namespace Widgets
    {
      flEXPORT void Separator();
      flEXPORT void Label(flIN char const * text);
      flEXPORT bool Checkbox(flIN char const * name, flIN bool * pValue);
      flEXPORT bool Input(flIN char const * name, flIN float * pValue);
      flEXPORT bool Input(flIN char const * name, flIN int * pValue);
      flEXPORT bool Input(flIN char const * name, flIN char * text, flIN int64_t bufferSize);
      flEXPORT void Image(flIN Graphics::Texture2D *pTexture, flIN float width, flIN float height);
    }
  }
}