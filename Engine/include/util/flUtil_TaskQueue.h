#ifndef flUtil_TaskQueue_h__
#define flUtil_TaskQueue_h__

#include "flUtil_Task.h"

namespace flEngine
{
  namespace Util
  {
    typedef int64_t(*TaskFunc)(void *);

    class flPIMPL_CLASS(TaskQueue);

    class flEXPORT TaskQueue
    {
      flPIMPL_DEF(TaskQueue);

    public:
      bool Add(Task *pTask);

      bool Add(TaskFunc taskFunc, void *pUserData = nullptr);

      void Flush();

      int64_t RunNext();

      bool HasNext() const;

      int64_t GetCount() const;
    };
  }
}

#endif // flUtil_TaskQueue_h__
