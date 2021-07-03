#pragma once

#include "flConfig.h"
#include <mutex>

#ifdef Yield
#undef Yield
#endif

namespace Fractal
{
  /**
  * @brief Alias for std::thread
  */
  typedef std::thread          Thread;

  /**
   * @brief Alias for std::mutex
   */
  typedef std::mutex           Mutex;

  /**
  * @brief Alias for std::recursive_mutex
  */
  typedef std::recursive_mutex RecursiveMutex;

  /**
   * @brief Stop execution of the current thread for a given amount of time.
   *
   * @param [in] milli How long to sleep for in milliseconds
   */
  flEXPORT void Sleep(flIN int64_t milli);

  /**
  * @brief Attempt to reschedule this thread, so that another may be run.
  */
  flEXPORT void Yield();

  /**
   * @brief Get the number of concurrent CPU threads supported.
   */
  flEXPORT int64_t GetCPUThreadCount();

  /**
   * @brief Get the ID of the current thread.
   */
  flEXPORT int64_t GetThreadID();
}
