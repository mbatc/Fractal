#ifndef fl_Threads_h__
#define fl_Threads_h__

#include "../flConfig.h"
#include <mutex>

namespace flEngine
{
  namespace Threads
  {
    /**
    * Alias for std::thread
    */
    typedef std::thread          Thread;

    /**
     * Alias for std::mutex
     */
    typedef std::mutex           Mutex;

    /**
    * Alias for std::recursive_mutex
    */
    typedef std::recursive_mutex RecursiveMutex;

    /**
     * Stop execution of the current thread for a given amount of time.
     *
     * @param [in] milli How long to sleep for in milliseconds
     */
    void flEXPORT Sleep(flIN int64_t milli);

    /**
    * Attempt to reschedule this thread, so that another may be run.
    */
    void flEXPORT Yield();
  }
}

#endif // fl_Threads_h__
