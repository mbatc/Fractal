#include "threads/flThreads.h"
#include "util/flTask.h"

using namespace flEngine;
using namespace flEngine::Util;

namespace flEngine
{
  namespace Util
  {
    class flPIMPL_CLASS(Task)
    {
    public:
      Task::Status GetStatus()
      {
        Lock();
        Task::Status status = m_status;
        Unlock();
        return status;
      }

      void SetStatus(const Task::Status &status)
      {
        Lock();
        m_status = status;
        Unlock();
      }

      int64_t GetResult()
      {
        Lock();
        int64_t res = m_result;
        Unlock();
        return res;
      }

      void SetResult(int64_t result)
      {
        Lock();
        m_result = result;
        Unlock();
      }

      void Lock()
      {
        m_lock.lock();
      }

      void Unlock()
      {
        m_lock.unlock();
      }

      int64_t Wait()
      {
        while (GetStatus() != Task::Status_Complete)
          Threads::Sleep(1ll);
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

      Threads::Mutex m_lock;
    };
  }
}

flPIMPL_IMPL(Task)

#define flIMPL flPIMPL(Task)

int64_t Task::Run()
{
  int64_t result = -1;

  flIMPL->Lock();
  // Return result if the task has already been complete
  if (flIMPL->m_status == Status_Complete)
  {
    result = flIMPL->GetResult();
  }
  else if (flIMPL->m_status == Status_Running)
  {
    result = flIMPL->Wait();
  }
  else
  {
    flIMPL->m_status = Status_Running;
    flIMPL->Unlock();

    // Run the task
    int64_t result = DoTask();

    // Update the status and the result
    flIMPL->Lock();
    flIMPL->m_status = Status_Complete;
    flIMPL->m_result = result;
  }

  flIMPL->Unlock();
  return result;
}

int64_t Task::Wait()
{
  return flIMPL->Wait();
}

bool Task::Reset()
{
  if (!OnReset())
    return false;
  flIMPL->Reset();
  return true;
}

bool flEngine::Util::Task::Cancel()
{
  return false;
}

bool Task::OnReset()
{
  return false;
}

Task::Status Task::GetStatus() const
{
  return flIMPL->GetStatus();
}

int64_t Task::GetResult() const
{
  return flIMPL->GetResult();
}
