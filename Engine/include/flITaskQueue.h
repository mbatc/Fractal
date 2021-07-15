#pragma once

#include "flInterface.h"

namespace Fractal
{
  class ITask;

  class flEXPORT ITaskQueue : public Interface
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
     * @brief Run all the tasks currently in the queue.
     *
     * If a task is added during a call to Flush, it will not be executed.
     * Only the tasks in the queue at the time of calling Flush() will be
     * run.
     */
    virtual void Flush() = 0;

    /**
     * @brief Run the next task in the queue.
     *
     * @return The value returned by the task.
     */
    virtual int64_t RunNext() = 0;

    /**
     * @brief Check if there is a task in the queue.
     *
     * @return Returns true if there is one or more tasks in the queue.
     */
    virtual bool HasNext() const = 0;

    /**
     * @brief Get the number of tasks in the queue.
     *
     * @return The number of tasks in the queue.
     */
    virtual int64_t GetCount() const = 0;
  };
}

extern "C" {
  flEXPORT Fractal::ITaskQueue* Fractal_CreateTaskQueue();
}
