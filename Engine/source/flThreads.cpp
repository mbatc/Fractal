#include "flThreads.h"
#include "ctUtility.h"
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

  int64_t GetCPUThreadCount()
  {
    return ctMax(std::thread::hardware_concurrency(), 1ll);
  }

  int64_t GetThreadID()
  {
    return std::hash<std::thread::id>()(std::this_thread::get_id());
  }
}