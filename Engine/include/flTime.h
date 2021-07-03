#pragma once

#include "flConfig.h"

namespace Fractal
{
  /*
   * @brief Get nanoseconds since epoch.
   */
  flEXPORT uint64_t flCCONV HighResClock();

  /*
   * @brief Get milliseconds since epoch. 
   */
  flEXPORT uint64_t flCCONV Clock();
}