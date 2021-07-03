#pragma once

#include "flTask.h"

namespace Fractal
{
  typedef int64_t(*TaskFunc)(void*);

  class Impl_TaskQueue;

  class flEXPORT TaskQueue : public Interface
  {
    flPIMPL_DEF(TaskQueue);

  public:
    static TaskQueue* Create();

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
     * @param [in] args Arguments to forward to the tasks types Create(...) function
     *
     * @return Returns true if the task was successfully added to the queue.
     */
    template<typename T, typename... Args> bool Add(flIN Args&& ... args);

    /**
     * @brief Add a task to the queue.
     *
     * @param [in]  taskFunc  A pointer to a callback to add to the queue.
     * @param [in]  pUserData User data pointer passed to the callback. Can be nullptr.
     * @param [out] ppTask    A pointer the the new task added. Can be nullptr.
     *
     * @return Returns true if the task was successfully added to the queue.
     */
    bool Add(flIN TaskFunc taskFunc, flIN void* pUserData = nullptr, flOUT Task** ppTask = nullptr);

    /**
     * @brief Run all the tasks currently in the queue.
     *
     * If a task is added during a call to Flush, it will not be executed.
     * Only the tasks in the queue at the time of calling Flush() will be
     * run.
     */
    void Flush();

    /**
     * @brief Run the next task in the queue.
     *
     * @return The value returned by the task.
     */
    int64_t RunNext();

    /**
     * @brief Check if there is a task in the queue.
     *
     * @return Returns true if there is one or more tasks in the queue.
     */
    bool HasNext() const;

    /**
     * @brief Get the number of tasks in the queue.
     *
     * @return The number of tasks in the queue.
     */
    int64_t GetCount() const;
  };
}

#include "flTaskQueue.inl"
