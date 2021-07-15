#include "flThreads.h"
#include "flThreadPool.h"
#include "flThreadQueue.h"

extern "C" {
  flEXPORT Fractal::IThreadQueue* Fractal_CreateThreadQueue()
  {
    return flNew Fractal::Impl::ThreadQueue;
  }
}

namespace Fractal
{
  namespace Impl
  {
    ThreadQueue::ThreadQueue()
      : m_pool(1)
    {}

    bool ThreadQueue::Add(flIN ITask* pTask)
    {
      return m_pool.Add(pTask);
    }

    void ThreadQueue::Flush()
    {
      m_pool.Flush();
    }

    void ThreadQueue::Pause()
    {
      m_pool.Pause();
    }

    void ThreadQueue::Resume()
    {
      m_pool.Resume();
    }

    bool ThreadQueue::IsPaused() const
    {
      return m_pool.IsPaused();
    }

    int64_t ThreadQueue::GetCount() const
    {
      return m_pool.GetCount();
    }
  }
}
