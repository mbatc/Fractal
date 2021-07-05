#include "flThreads.h"
#include "flTask.h"

namespace Fractal
{
  class Impl_Task
  {
  public:
    Task::Status GetStatus() const
    {
      Lock();
      Task::Status status = m_status;
      Unlock();
      return status;
    }

    void SetStatus(Task::Status const& status)
    {
      Lock();
      m_status = status;
      Unlock();
    }

    int64_t GetResult() const
    {
      Lock();
      int64_t res = m_result;
      Unlock();
      return res;
    }

    void Lock() const
    {
      m_lock->lock();
    }

    void Unlock() const
    {
      m_lock->unlock();
    }

    int64_t Wait()
    {
      while (GetStatus() != Task::Status_Complete)
        Sleep(1ll);
      return GetResult();
    }

    void Reset()
    {
      Lock();
      m_result = -1;
      m_status = Task::Status_Waiting;
      Unlock();
    }

    int64_t m_result = -1;
    Task::Status m_status = Task::Status_Waiting;

    std::unique_ptr<Mutex> m_lock = std::make_unique<Mutex>();
  };

  flPIMPL_IMPL(Task);

  int64_t Task::Run()
  {
    int64_t result = -1;

    Impl()->Lock();
    // Return result if the task has already been complete
    if (Impl()->m_status == Status_Complete)
    {
      result = Impl()->m_result;
    }
    else if (Impl()->m_status == Status_Running)
    {
      Impl()->Unlock();
      result = Impl()->Wait();

      return result;
    }
    else
    {
      Impl()->m_status = Status_Running;
      Impl()->Unlock();

      // Run the task
      int64_t result = DoTask();

      // Update the status and the result
      Impl()->Lock();
      Impl()->m_status = Status_Complete;
      Impl()->m_result = result;
    }

    Impl()->Unlock();
    return result;
  }

  int64_t Task::Await()
  {
    return Impl()->Wait();
  }

  bool Task::Reset()
  {
    if (!OnReset())
      return false;
    Impl()->Reset();
    return true;
  }

  bool Fractal::Task::Cancel()
  {
    return false;
  }

  bool Task::OnReset()
  {
    return true;
  }

  Task::Status Task::GetStatus() const
  {
    return Impl()->GetStatus();
  }

  int64_t Task::GetResult() const
  {
    return Impl()->GetResult();
  }
}
