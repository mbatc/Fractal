#include "flThreads.h"
#include "flTask.h"

extern "C" {
  Fractal::ITask* Fractal_CreateTask(Fractal::TaskFunc func, Fractal::Interface* pUserData)
  {
    return flNew Fractal::Impl::Task;
  }
}

namespace Fractal
{
  namespace Impl
  {
    Task::Task(TaskFunc func, Interface* pTaskData)
      : m_func(func)
      , m_pTaskData(MakeRef(pTaskData, true))
    {}

    int64_t Task::Run()
    {
      int64_t result = -1;

      Lock();
      // Return result if the task has already been complete
      if (m_status == TaskStatus_Complete)
      {
        result = m_result;
      }
      else if (m_status == TaskStatus_Running)
      {
        Unlock();
        result = Await();

        return result;
      }
      else
      {
        m_status = TaskStatus_Running;
        Unlock();

        // Run the task
        int64_t result = DoTask();

        // Update the status and the result
        Lock();
        m_status = TaskStatus_Complete;
        m_result = result;
      }

      Unlock();
      return result;
    }

    TaskStatus Task::GetStatus() const
    {
      Lock();
      TaskStatus status = m_status;
      Unlock();
      return status;
    }

    int64_t Task::GetResult() const
    {
      Lock();
      int64_t res = m_result;
      Unlock();
      return res;
    }

    int64_t Task::Await()
    {
      while (GetStatus() != TaskStatus_Complete)
        Sleep(1ll);
      return GetResult();
    }

    void Task::Reset()
    {
      Lock();
      m_result = -1;
      m_status = TaskStatus_Waiting;
      Unlock();
    }

    int64_t Task::DoTask()
    {
      return m_func(m_pTaskData.Get());
    }

    bool Task::Cancel()
    {
      Lock();
      if (m_status != TaskStatus_Waiting)
      {
        Unlock();
        return false;
      }

      m_status = TaskStatus_Cancelled;
      Unlock();
      return true;
    }

    void Task::SetStatus(TaskStatus status)
    {
      Lock();
      m_status = status;
      Unlock();
    }

    void Task::Lock() const
    {
      m_lock->lock();
    }

    void Task::Unlock() const
    {
      m_lock->unlock();
    }
  }
}
