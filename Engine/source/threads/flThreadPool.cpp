#include "threads/flThreadPool.h"
#include "threads/flThreads.h"
#include "atVector.h"

using namespace flEngine;
using namespace flEngine::Util;
using namespace flEngine::Threads;

namespace flEngine
{
  namespace Threads
  {
    class flPIMPL_CLASS(ThreadPool)
    {
    public:
      ~flPIMPL_CLASS(ThreadPool)()
      {
        m_running = false;

        for (Thread *pThread : m_threads) pThread->join();
        for (Thread *pThread : m_threads) flDelete pThread;
      }

      void Construct(const int64_t &threadCount)
      {
        m_running = true;

        for (int64_t i = 0; i < threadCount; ++i)
          m_threads.push_back(flNew Thread(&flPIMPL_CLASS(ThreadPool)::Run, this));
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

      volatile bool m_paused   = false;
      volatile bool m_running  = false;
      volatile bool m_isPaused = false;

      TaskQueue         m_queue;
      atVector<Thread*> m_threads;
    };
  }
}

flPIMPL_IMPL(ThreadPool)

#define flIMPL flPIMPL(ThreadPool)

ThreadPool::ThreadPool(int64_t threadCount)
{
  flIMPL->Construct(threadCount);
}

bool ThreadPool::Add(flIN Util::Task *pTask)
{
  return flIMPL->m_queue.Add(pTask);
}

bool ThreadPool::Add(flIN Util::TaskFunc taskFunc, flIN void *pUserData, flOUT Util::Task **ppTask)
{
  return flIMPL->m_queue.Add(taskFunc, pUserData, ppTask);
}

void ThreadPool::Flush()
{
  while (GetCount() > 0)
    Threads::Sleep(1);
}

void ThreadPool::Pause()
{
  flIMPL->m_paused = true;
}

void ThreadPool::Resume()
{
  flIMPL->m_paused = false;
}

bool ThreadPool::IsPaused() const
{
  return flIMPL->m_isPaused;
}

int64_t ThreadPool::GetCount() const
{
  return flIMPL->m_queue.GetCount();
}
