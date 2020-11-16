#ifndef fl_Threads_ThreadPool_h__
#define fl_Threads_ThreadPool_h__

#include "../util/flTaskQueue.h"

namespace flEngine
{
  namespace Threads
  {
    class flPIMPL_CLASS(ThreadPool);

    /**
    * @brief A thread pool for executing generic tasks.
    *
    * This class is similar to an EventQueue, however tasks added to the thread pool
    * may not be executed in the same order they were added. 
    */
    class flEXPORT ThreadPool
    {
      flPIMPL_DEF(ThreadPool);

    public:
      ThreadPool(int64_t threadCount);

      /**
      * Add a task to the queue.
      *
      * @param [in] pTask
      *
      * @return Returns true if the task was successfully added to the queue.
      */
      bool Add(flIN Util::Task *pTask);

      /**
      * Add a task to the queue.
      *
      * @param [in] taskFunc  A pointer to a callback to add to the queue.
      * @param [in] pUserData User data pointer passed to the callback
      *
      * @return Returns true if the task was successfully added to the queue.
      */
      bool Add(flIN Util::TaskFunc taskFunc, flIN void *pUserData = nullptr);

      /**
      * Wait for all the tasks the queue to complete.
      */
      void Flush();

      /**
      * Suspend the execution of tasks.
      *
      * @return Returns true if the
      */
      void Pause();

      /**
      * Resume the execution of tasks.
      */
      void Resume();

      /**
      * Check if execution of tasks is paused.
      *
      * @return Returns true if the thread is paused.
      */
      bool IsPaused() const;

      /**
      * Get the number of tasks in the queue.
      *
      * @return The number of tasks in the queue.
      */
      int64_t GetCount() const;
    };
  }
}

#endif // fl_Threads_ThreadPool_h__
