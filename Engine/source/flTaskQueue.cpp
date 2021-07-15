#include "flTaskQueue.h"
#include "flITask.h"
#include <type_traits>

extern "C" {
  flEXPORT Fractal::ITaskQueue* Fractal_CreateTaskQueue()
  {
    return flNew Fractal::Impl::TaskQueue;
  }
}

namespace Fractal
{
  namespace Impl
  {
    TaskQueue::TaskQueue()
      : m_lock(std::make_unique<Mutex>())
    {}

    bool TaskQueue::Add(flIN ITask* pTask)
    {
      if (!pTask)
        return false;
      m_lock->lock();
      m_tasks.push_back(MakeRef(pTask, true));
      m_lock->unlock();
      return true;
    }

    void TaskQueue::Flush()
    {
      int64_t currentCount = GetCount();
      while (currentCount-- > 0)
        RunNext();
    }

    int64_t TaskQueue::RunNext()
    {
      m_lock->lock();
      Ref<ITask> pNextTask;
      if (m_tasks.size() > 0)
      {
        pNextTask = m_tasks.front();
        m_tasks.pop_front();
      }
      m_lock->unlock();

      int64_t result = -1;
      if (pNextTask != nullptr)
        result = pNextTask->Run();

      return result;
    }

    bool TaskQueue::HasNext() const
    {
      return GetCount() > 0;
    }

    int64_t TaskQueue::GetCount() const
    {
      m_lock->lock();
      int64_t count = m_tasks.size();
      m_lock->unlock();
      return count;
    }
  }
}
