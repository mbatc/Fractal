#include "flThreads.h"
#include "flThreadPool.h"
#include "flThreadQueue.h"

namespace Fractal
{
  class Impl_ThreadQueue
  {
  public:
    Impl_ThreadQueue()
      : m_pool(1)
    {}

    ThreadPool m_pool;
  };

  flPIMPL_IMPL(ThreadQueue);

  bool ThreadQueue::Add(flIN Task* pTask)
  {
    return Impl()->m_pool.Add(pTask);
  }

  bool ThreadQueue::Add(flIN TaskFunc taskFunc, flIN void* pUserData, flOUT Task** ppTask)
  {
    return Impl()->m_pool.Add(taskFunc, pUserData, ppTask);
  }

  void ThreadQueue::Flush()
  {
    Impl()->m_pool.Flush();
  }

  void ThreadQueue::Pause()
  {
    Impl()->m_pool.Pause();
  }

  void ThreadQueue::Resume()
  {
    Impl()->m_pool.Resume();
  }

  bool ThreadQueue::IsPaused() const
  {
    return Impl()->m_pool.IsPaused();
  }

  int64_t ThreadQueue::GetCount() const
  {
    return Impl()->m_pool.GetCount();
  }
}
