#pragma once

#include "flConfig.h"

namespace flEngine
{
  namespace GUI
  {
    namespace Widgets
    {
      flEXPORT void Separator();
      flEXPORT void Label(char const * text);
      flEXPORT bool Checkbox(char const * name, bool * pValue);
      flEXPORT bool Input(char const * name, float * pValue);
      flEXPORT bool Input(char const * name, int * pValue);
      flEXPORT bool Input(char const * name, char * text, int64_t bufferSize);
    }
  }
}