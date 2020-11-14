#include "threads/flThreads.h"
#include <chrono>
#include <thread>

void flEngine::Threads::Sleep(int64_t milli)
{
  std::this_thread::sleep_for(std::chrono::milliseconds(milli));
}

void flEngine::Threads::Yield(int64_t milli)
{
  std::this_thread::yield();
}
