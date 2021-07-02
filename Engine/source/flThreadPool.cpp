#include "flThreadPool.h"
#include "flThreads.h"
#include "ctVector.h"

namespace Fractal
{
  class Impl_ThreadPool
  {
  public:
    ~Impl_ThreadPool()
    {
      m_running = false;

      for (Thread* pThread : m_threads)
        pThread->join();
      for (Thread* pThread : m_threads)
        flDelete pThread;
    }

    void Construct(const int64_t& threadCount)
    {
      m_running = true;

      for (int64_t i = 0; i < threadCount; ++i)
        m_threads.push_back(flNew Thread(&Impl_ThreadPool::Run, this));
    }

    void Run()
    {
      while (m_running)
      {
        m_isPaused = m_paused;
        if (!m_queue.HasNext() || m_paused)
        {
          Sleep(1);
        }
        else
        {
          m_queue.RunNext();
        }
      }
    }

    volatile bool m_paused = false;
    volatile bool m_running = false;
    volatile bool m_isPaused = false;

    TaskQueue         m_queue;
    ctVector<Thread*> m_threads;
  };

  flPIMPL_IMPL(ThreadPool);

  ThreadPool::ThreadPool(int64_t threadCount)
  {
    Impl()->Construct(threadCount);
  }

  bool ThreadPool::Add(flIN Task* pTask)
  {
    return Impl()->m_queue.Add(pTask);
  }

  bool ThreadPool::Add(flIN TaskFunc taskFunc, flIN void* pUserData, flOUT Task** ppTask)
  {
    return Impl()->m_queue.Add(taskFunc, pUserData, ppTask);
  }

  void ThreadPool::Flush()
  {
    while (GetCount() > 0)
      Sleep(1);
  }

  void ThreadPool::Pause()
  {
    Impl()->m_paused = true;
  }

  void ThreadPool::Resume()
  {
    Impl()->m_paused = false;
  }

  bool ThreadPool::IsPaused() const
  {
    return Impl()->m_isPaused;
  }

  int64_t ThreadPool::GetCount() const
  {
    return Impl()->m_queue.GetCount();
  }
}
