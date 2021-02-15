#include "threads/flThreads.h"
#include "util/flTaskQueue.h"
#include "ctVector.h"
#include <type_traits>

using namespace flEngine;
using namespace flEngine::Util;

namespace flEngine
{
  namespace Util
  {
    class flPIMPL_CLASS(TaskQueue)
    {
    public:
      bool Add(Task *pTask)
      {
        if (!pTask)
          return false;

        pTask->IncRef();
        m_lock.lock();
        m_tasks.push_back(pTask);
        m_lock.unlock();
        return true;
      }

      void Flush()
      {
        int64_t currentCount = GetCount();
        while (currentCount-- > 0)
          RunNext();
      }

      int64_t RunNext()
      {
        if (!HasNext())
          return -1;

        m_lock.lock();
        Task *pNextTask = m_tasks.front();
        m_tasks.pop_front();
        m_lock.unlock();

        int64_t result = -1;
        if (pNextTask)
        {
          result = pNextTask->Run();
          pNextTask->DecRef();
        }

        return result;
      }

      bool HasNext()
      {
        return GetCount() > 0;
      }

      int64_t GetCount()
      {
        m_lock.lock();
        int64_t count = m_tasks.size();
        m_lock.unlock();
        return count;
      }

    protected:
      Threads::Mutex     m_lock;
      ctVector<Task*> m_tasks;
    };
  }
}

flPIMPL_IMPL(TaskQueue)

#define flIMPL flPIMPL(TaskQueue)

class _flGenericTask : public Task
{
  _flGenericTask(flIN TaskFunc taskFunc, flIN void *pUserData)
    : m_callback(taskFunc)
    , m_pUserData(pUserData)
  {}

public:
  static _flGenericTask* Create(flIN TaskFunc taskFunc, flIN void *pUserData)
  {
    return flNew _flGenericTask(taskFunc, pUserData);
  }

  virtual void Destroy() override
  {
    flDelete this;
  }

  int64_t DoTask() override
  {
    return m_callback(m_pUserData);
  }

protected:
  TaskFunc m_callback = nullptr;
  void *m_pUserData = nullptr;
};

bool TaskQueue::Add(flIN Task *pTask)
{
  return flIMPL->Add(pTask);
}

bool TaskQueue::Add(flIN TaskFunc taskFunc, flIN void *pUserData, flOUT Task **ppTask)
{
  Task *pNewTask = _flGenericTask::Create(taskFunc, pUserData);
  if (ppTask)
  {
    pNewTask->IncRef();
    *ppTask = pNewTask;
  }

  bool result = flIMPL->Add(pNewTask);
  pNewTask->DecRef();

  return result;
}

void TaskQueue::Flush()
{
  flIMPL->Flush();
}

int64_t TaskQueue::RunNext()
{
  return flIMPL->RunNext();
}

bool TaskQueue::HasNext() const
{
  return flIMPL->HasNext();
}

int64_t TaskQueue::GetCount() const
{
  return flIMPL->GetCount();
}
