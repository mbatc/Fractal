#include "flThreadPool.h"
#include "flITaskQueue.h"
#include "flThreads.h"

static Fractal::IThreadPool* _pGlobalThreadPool = nullptr;
static int64_t _globalWorkerCount = Fractal_GetCPUThreadCount();

Fractal::IThreadPool* Fractal_CreateThreadPool(flIN int64_t threadCount)
{
  return flNew Fractal::Impl::ThreadPool(threadCount);
}

Fractal::IThreadPool* Fractal_GetGlobalThreadPool()
{
  if (_pGlobalThreadPool == nullptr)
  {
    _pGlobalThreadPool = Fractal_CreateThreadPool(_globalWorkerCount);
  }

  return _pGlobalThreadPool;
}

namespace Fractal
{
  namespace Impl
  {
    ThreadPool::~ThreadPool()
    {
      m_running = false;

      for (Thread* pThread : m_threads)
        pThread->join();
      for (Thread* pThread : m_threads)
        flDelete pThread;
    }

    ThreadPool::ThreadPool(const int64_t& threadCount)
    {
      m_running = true;

      for (int64_t i = 0; i < threadCount; ++i)
        m_threads.push_back(flNew Thread(&ThreadPool::Run, this));
    }

    void ThreadPool::Run()
    {
      while (m_running)
      {
        m_isPaused = m_paused;
        if (!m_pQueue->HasNext() || m_paused)
        {
          Fractal_Sleep(1);
        }
        else
        {
          m_pQueue->RunNext();
        }
      }
    }

    bool ThreadPool::Add(flIN ITask* pTask)
    {
      return m_pQueue->Add(pTask);
    }

    void ThreadPool::Flush()
    {
      while (GetCount() > 0)
        Fractal_Sleep(1);
    }

    void ThreadPool::Pause()
    {
      m_paused = true;
    }

    void ThreadPool::Resume()
    {
      m_paused = false;
    }

    bool ThreadPool::IsPaused() const
    {
      return m_isPaused;
    }

    int64_t ThreadPool::GetCount() const
    {
      return m_pQueue->GetCount();
    }
  }
}
