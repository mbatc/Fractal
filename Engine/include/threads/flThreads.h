#ifndef flUtil_Threads_h__
#define flUtil_Threads_h__

#include <mutex>
#include "../flConfig.h"

namespace flEngine
{
  namespace Threads
  {
    typedef std::mutex           Mutex;
    typedef std::recursive_mutex RecursiveMutex;
    typedef std::thread          Thread;

    void flEXPORT Sleep(int64_t milli);
    void flEXPORT Yield(int64_t milli);
  }
}

#endif // flUtil_Threads_h__
