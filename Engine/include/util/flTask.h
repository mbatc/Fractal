#ifndef fl_Util_Task_h__
#define fl_Util_Task_h__

#include "../flInterface.h"

namespace flEngine
{
  namespace Util
  {
    class flPIMPL_CLASS(Task);

    class flEXPORT Task : public Interface
    {
      flPIMPL_DEF(Task);

    public:
      /**
       * The Status enum describes the Task's current state within a queue.
       */
      enum Status
      {
        Status_Waiting,   ///> The Task is waiting to be executed.
        Status_Running,   ///> The Task is being executed.
        Status_Complete,  ///> The Task has finised executing.
        Status_Cancelled, ///> The Task has finised executing.
        Status_Count,     ///> The number of status codes.
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
      int64_t Wait();

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
       * @brief Explicitly destroy the Task instance.
       *
       * As this function implements the Interface class, the DecRef() function should
       * be preferred over calling this directly.
       *
       * This needs to be implemented so that tasks passed between module boundaries
       * can be safely destroyed. This is because when adding a task to a queue in the Engine,
       * that queue may take ownership of the Task instance. Therefor, to safely destroy the
       * instance, it MUST be freed in the module in which it was created (i.e. the module that
       * defined the object).
       *
       * Most implementations of this function will be
       *
       *    void MyTaskBase::Destroy() { delete this; }
       *
       * It is recommended that a module that implements may tasks should create a base class that
       * implements this function once.
       *
       * See Interface::Destroy for further information.
       */
      virtual void Destroy() override = 0;

      /**
       * Get the current status of the task.
       *
       * @return The current status of the task.
       */
      Status GetStatus() const;

      /**
       * Get the result of a completed task.
       *
       * @return The result of the task.
       */
      int64_t GetResult() const;
    };
  }
}

#endif // flUtil_Task_h__
