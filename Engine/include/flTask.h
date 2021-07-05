#pragma once

#include "flInterface.h"
#include "flRef.h"

namespace Fractal
{
  typedef int64_t (*TaskFunc)(void*);

  class Impl_Task;

  class flEXPORT Task : public Interface
  {
    flPIMPL_DEF(Task);

  public:
    /**
     * @brief The Status enum describes the Task's current state within a queue.
     */
    enum Status : int64_t
    {
      Status_Waiting,   ///< The Task is waiting to be executed.
      Status_Running,   ///< The Task is being executed.
      Status_Complete,  ///< The Task has finised executing.
      Status_Cancelled, ///< The Task has finised executing.
      Status_Count,     ///< The number of status codes.
    };

    /**
     * @brief Execute the defined task.
     *
     * This function will run the defined task and update the status and return
     * code accordingly. It is not reccomended to call DoTask() directly. Use this
     * function instead.
     *
     * @return The return value of the task.
     */
    int64_t Run();

    /**
     * @brief Block until the task has complete finished
     *
     * Wait for the task to finish executing.
     *
     * @return The return value of the task.
     */
    int64_t Await();

    /**
     * @brief The Task implementation function
     *
     * This function must be overridden to define the work performed by the task. This function
     * should not be called directly. Use Run() instead.
     *
     * @return A int64 indicating the result of the function.
     */
    virtual int64_t DoTask() = 0;

    /**
     * @brief Reset the task so it can be run again.
     *
     * If the task has been run, this function can be used to reset the task
     * so that it can be run again. A task must implement the OnReset()
     * function and return `true` to enable this behavior.
     *
     * @return A bool indicating if the task was reset successfully.
     */
    bool Reset();

    /**
     * @brief Cancel the execution of the task.
     *
     * This function can be used to stop a task from executing. This must be
     * called while the tasks status is Status_Waiting to have an affect.
     * If the task is already executing, it cannot be interrupted.
     *
     * @return A bool indicating if the task was successfully canceled.
     */
    bool Cancel();

    /**
     * @brief The Task implementation function
     *
     * This function must be overridden to define the work performed by the task. This function
     * should not be called directly. Use Run() instead.
     *
     * @return A int64 indicating the result of the function.
     */
    virtual bool OnReset();

    /**
     * @brief Get the current status of the task.
     *
     * @return The current status of the task.
     */
    Status GetStatus() const;

    /**
     * @brief Get the result of a completed task.
     *
     * @return The result of the task.
     */
    int64_t GetResult() const;
  };

  /**
   * @brief Create an Task instance from a callable object.
   *
   * The callable object must return an int64_t and take no parameters.
   */
  template <typename Lambda>
  Ref<Task> MakeTask(Lambda&& lambda)
  {
    class Wrapper : public Task
    {
    public:
      virtual int64_t DoTask() override
      {
        return m_func();
      }

      Wrapper(Lambda func) : m_func(func) {}

      Lambda m_func;
    };

    return MakeRef<Wrapper>(lambda).StaticCast<Task>();
  }

  inline Ref<Task> MakeTask(TaskFunc func, void* pUserData = nullptr)
  {
    class Wrapper : public Task
    {
    public:
      Wrapper(TaskFunc func, void* pUserData)
        : m_pUserData(pUserData), m_func(func)
      {}

      virtual int64_t DoTask() override { return m_func(m_pUserData); }

      void* m_pUserData = 0;
      TaskFunc m_func = 0;
    };

    return MakeRef<Wrapper>(func, pUserData).StaticCast<Task>();
  }
}
