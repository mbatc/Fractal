#include "flTime.h"

#include <chrono>

namespace Fractal
{
  uint64_t HighResClock()
  {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
  }

  uint64_t Clock()
  {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
  }
}
