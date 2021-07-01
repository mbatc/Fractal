#include "flThreads.h"
#include <chrono>
#include <thread>

namespace Fractal
{
  void Sleep(flIN int64_t milli)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(milli));
  }

  void Yield()
  {
    std::this_thread::yield();
  }
}