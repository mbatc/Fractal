#pragma once

#include "flInterface.h"
#include "flRef.h"

namespace Fractal
{
  typedef int64_t (*TaskFunc)(Interface*);

  /**
   * @brief The Status enum describes the Task's current state within a queue.
   */
  enum TaskStatus : int64_t
  {
    TaskStatus_Waiting,   ///< The Task is waiting to be executed.
    TaskStatus_Running,   ///< The Task is being executed.
    TaskStatus_Complete,  ///< The Task has finished executing.
    TaskStatus_Cancelled, ///< The Task has finished executing.
    TaskStatus_Count,     ///< The number of status codes.
  };

  class flEXPORT ITask : public Interface
  {
  public:
    /**
     * @brief Execute the defined task.
     *
     * This function will run the defined task and update the status and return
     * code accordingly. It is not reccomended to call DoTask() directly. Use this
     * function instead.
     *
     * @return The return value of the task.
     */
    virtual int64_t Run() = 0;

    /**
     * @brief Block until the task has complete finished
     *
     * Wait for the task to finish executing.
     *
     * @return The return value of the task.
     */
    virtual int64_t Await() = 0;

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
     * @brief Cancel the execution of the task.
     *
     * This function can be used to stop a task from executing. This must be
     * called while the tasks status is Status_Waiting to have an affect.
     * If the task is already executing, it cannot be interrupted.
     *
     * @return A bool indicating if the task was successfully canceled.
     */
    virtual bool Cancel() = 0;

    /**
     * @brief Reset the task so it can be run again.
     *
     * If the task has been run, this function can be used to reset the task
     * so that it can be run again.
     */
    virtual void Reset() = 0;

    /**
     * @brief Get the current status of the task.
     *
     * @return The current status of the task.
     */
    virtual TaskStatus GetStatus() const = 0;

    /**
     * @brief Get the result of a completed task.
     *
     * @return The result of the task.
     */
    virtual int64_t GetResult() const = 0;
  };
}

extern "C" {
  Fractal::ITask* Fractal_CreateTask(Fractal::TaskFunc func, Fractal::Interface *pUserData);
}

namespace Fractal
{
  /**
   * @brief Create an Task instance from a callable object.
   *
   * The callable object must return an int64_t and take no parameters.
   */
  template <typename Lambda>
  Ref<ITask> MakeTask(Lambda&& lambda)
  {
    class LambdaWrapper : public Interface
    {
      FRACTAL_DEFAULT_INTERFACE;

    public:
      LambdaWrapper(Lambda func) : m_func(func) {}
      Lambda m_func;
    };

    // Create a task that wraps the LambdaWrapper class and calls the function
    ITask* pTask = Fractal_CreateTask([](Interface *pUserData) {
      ((LambdaWrapper*)pUserData)->m_func();
    }, flNew LambdaWrapper(lambda));

    return MakeRef(pTask, false);
  }
}