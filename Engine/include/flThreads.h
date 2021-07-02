#pragma once

#include "flConfig.h"
#include <mutex>

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
  void flEXPORT Sleep(flIN int64_t milli);

  /**
  * @brief Attempt to reschedule this thread, so that another may be run.
  */
  void flEXPORT Yield();
}
