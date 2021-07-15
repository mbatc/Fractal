#pragma once

#include "flInterface.h"

namespace Fractal
{
  class ITask;

  /**
   * @brief A thread pool for executing generic tasks.
   *
   * This class is similar to an EventQueue, however tasks added to the thread pool
   * may not be executed in the same order they were added.
   */
  class flEXPORT IThreadPool : public Interface
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
  flEXPORT Fractal::IThreadPool * flCCONV Fractal_CreateThreadPool(flIN int64_t threadCount);

  /**
   * @brief A shared thread pool for the engine.
   */
  flEXPORT Fractal::IThreadPool * flCCONV Fractal_GetGlobalThreadPool();
}
