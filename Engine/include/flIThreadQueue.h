#pragma once

#include "flTaskQueue.h"

namespace Fractal
{
  /**
   * @brief A threaded task queue.
   *
   * This class is essentially a threaded EventQueue. It spawns a worker thread,
   * which executes tasks added to it sequentially.
   */
  class flEXPORT IThreadQueue : public Interface
  {
  public:
    /**
     * @brief Add a task to the queue.
     *
     * @param [in] pTask
     *
     * @return Returns true if the task was successfully added to the queue.
     */
    virtual bool Add(flIN ITask* pTask) = 0;

    /**
     * @brief Wait for all the tasks the queue to complete.
     */
    virtual void Flush() = 0;

    /**
     * @brief Suspend the execution of tasks.
     *
     * @return Returns true if the
     */
    virtual void Pause() = 0;

    /**
     * @brief Resume the execution of tasks.
     */
    virtual void Resume() = 0;

    /**
     * @brief Check if execution of tasks is paused.
     *
     * @return Returns true if the thread is paused.
     */
    virtual bool IsPaused() const = 0;

    /**
     * @brief Get the number of tasks in the queue.
     *
     * @return The number of tasks in the queue.
     */
    virtual int64_t GetCount() const = 0;
  };
}

extern "C" {
  flEXPORT Fractal::IThreadQueue* Fractal_CreateThreadQueue();
}
