#ifndef fl_Util_TaskQueue_h__
#define fl_Util_TaskQueue_h__

#include "flTask.h"

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
      /**
       * Add a task to the queue.
       *
       * @param [in] pTask
       *
       * @return Returns true if the task was successfully added to the queue.
       */
      bool Add(flIN Task *pTask);

      /**
       * Add a task to the queue.
       *
       * @param [in] taskFunc  A pointer to a callback to add to the queue.
       * @param [in] pUserData User data pointer passed to the callback
       *
       * @return Returns true if the task was successfully added to the queue.
       */
      bool Add(flIN TaskFunc taskFunc, flIN void *pUserData = nullptr);

      /**
      * @brief Run all the tasks currently in the queue.
      *
      * If a task is added during a call to Flush, it will not be executed.
      * Only the tasks in the queue at the time of calling Flush() will be
      * run.
      */
      void Flush();

      /**
       * Run the next task in the queue.
       *
       * @return The value returned by the task.
       */
      int64_t RunNext();

      /**
       * Check if there is a task in the queue.
       *
       * @return Returns true if there is one or more tasks in the queue.
       */
      bool HasNext() const;

      /**
       * Get the number of tasks in the queue.
       *
       * @return The number of tasks in the queue.
       */
      int64_t GetCount() const;
    };
  }
}

#endif // flUtil_TaskQueue_h__
