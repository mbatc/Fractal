#include "flThreads.h"
#include "flTaskQueue.h"
#include "flRef.h"
#include "ctVector.h"
#include <type_traits>

namespace Fractal
{
  class Impl_TaskQueue
  {
  public:
    bool Add(Ref<Task> const &pTask)
    {
      if (!pTask)
        return false;
      m_lock->lock();
      m_tasks.push_back(pTask);
      m_lock->unlock();
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

      m_lock->lock();
      Ref<Task> pNextTask = m_tasks.front();
      m_tasks.pop_front();
      m_lock->unlock();

      int64_t result = -1;
      if (pNextTask)
        result = pNextTask->Run();

      return result;
    }

    bool HasNext() const
    {
      return GetCount() > 0;
    }

    int64_t GetCount() const
    {
      m_lock->lock();
      int64_t count = m_tasks.size();
      m_lock->unlock();
      return count;
    }

  protected:
    ctVector<Ref<Task>>    m_tasks;
    std::unique_ptr<Mutex> m_lock = std::make_unique<Mutex>();
  };

  flPIMPL_IMPL(TaskQueue);

    class _flGenericTask : public Task
  {
    _flGenericTask(flIN TaskFunc taskFunc, flIN void *pUserData)
      : m_callback(taskFunc)
      , m_pUserData(pUserData)
    {}

  public:
    static _flGenericTask *Create(flIN TaskFunc taskFunc, flIN void *pUserData)
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
    return Impl()->Add(MakeRef(pTask, true));
  }

  bool TaskQueue::Add(flIN TaskFunc taskFunc, flIN void *pUserData, flOUT Task **ppTask)
  {
    Ref<Task> pNewTask = MakeRef(_flGenericTask::Create(taskFunc, pUserData), false).StaticCast<Task>();
    if (ppTask)
    {
      pNewTask->IncRef();
      *ppTask = pNewTask;
    }

    return Impl()->Add(pNewTask);
  }

  void TaskQueue::Flush()
  {
    Impl()->Flush();
  }

  int64_t TaskQueue::RunNext()
  {
    return Impl()->RunNext();
  }

  bool TaskQueue::HasNext() const
  {
    return Impl()->HasNext();
  }

  int64_t TaskQueue::GetCount() const
  {
    return Impl()->GetCount();
  }
}
