#include "flThreads.h"
#include "ctUtility.h"
#include <chrono>
#include <thread>

extern "C" {
  void Fractal_Sleep(flIN int64_t milli)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(milli));
  }

  void Fractal_Yield()
  {
    std::this_thread::yield();
  }

  int64_t Fractal_GetCPUThreadCount()
  {
    return ctMax(std::thread::hardware_concurrency(), 1ll);
  }

  int64_t Fractal_GetThreadID()
  {
    return std::hash<std::thread::id>()(std::this_thread::get_id());
  }
}