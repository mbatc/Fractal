#ifndef fl_Threads_ThreadQueue_h__
#define fl_Threads_ThreadQueue_h__

#include "../util/flTaskQueue.h"

namespace flEngine
{
  namespace Threads
  {
    class flPIMPL_CLASS(ThreadQueue);

    /**
     * @brief A threaded task queue.
     *
     * This class is essentially a threaded EventQueue. It spawns a worker thread,
     * which executes tasks added to it sequentially.
     */
    class flEXPORT ThreadQueue
    {
      flPIMPL_DEF(ThreadQueue);

    public:
      /**
       * @brief Add a task to the queue.
       *
       * @param [in] pTask
       *
       * @return Returns true if the task was successfully added to the queue.
       */
      bool Add(flIN Util::Task *pTask);

      /**
       * @brief Add a task to the queue.
       *
       * @param [in]  taskFunc  A pointer to a callback to add to the queue.
       * @param [in]  pUserData User data pointer passed to the callback
       * @param [out] ppTask    A pointer the the new task added. Can be nullptr.
       *
       * @return Returns true if the task was successfully added to the queue.
       */
      bool Add(flIN Util::TaskFunc taskFunc, flIN void *pUserData = nullptr, flOUT Util::Task **ppTask = nullptr);

      /**
       * @brief Wait for all the tasks the queue to complete.
       */
      void Flush();

      /**
       * @brief Suspend the execution of tasks.
       *
       * @return Returns true if the 
       */
      void Pause();

      /**
       * @brief Resume the execution of tasks.
       */
      void Resume();

      /**
       * @brief Check if execution of tasks is paused.
       *
       * @return Returns true if the thread is paused.
       */
      bool IsPaused() const;

      /**
       * @brief Get the number of tasks in the queue.
       *
       * @return The number of tasks in the queue.
       */
      int64_t GetCount() const;
    };
  }
}

#endif // flThreadQueue_h__
