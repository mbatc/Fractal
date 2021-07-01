#pragma once

#include "flTaskQueue.h"

namespace Fractal
{
  class Impl_ThreadPool;

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
     * @brief Add a task to the queue.
     *
     * @param [in] pTask
     *
     * @return Returns true if the task was successfully added to the queue.
     */
    bool Add(flIN Task* pTask);

    /**
     * @brief Add a task to the queue.
     *
     * @param [in]  taskFunc  A pointer to a callback to add to the queue.
     * @param [in]  pUserData User data pointer passed to the callback.
     * @param [out] ppTask    A pointer the the new task added. Can be nullptr.
     *
     * @return Returns true if the task was successfully added to the queue.
     */
    bool Add(flIN TaskFunc taskFunc, flIN void* pUserData = nullptr, flOUT Task** ppTask = nullptr);

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
