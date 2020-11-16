#include "threads/flThreads.h"
#include "threads/flThreadPool.h"
#include "threads/flThreadQueue.h"

using namespace flEngine;
using namespace flEngine::Threads;

namespace flEngine
{
  namespace Threads
  {
    class flPIMPL_CLASS(ThreadQueue)
    {
    public:
      flPIMPL_CLASS(ThreadQueue)()
        : m_pool(1)
      {}

      ThreadPool m_pool;
    };
  }
}

flPIMPL_IMPL(ThreadQueue)

#define flIMPL flPIMPL(ThreadQueue)

bool ThreadQueue::Add(flIN Util::Task *pTask)
{
  return flIMPL->m_pool.Add(pTask);
}

bool ThreadQueue::Add(flIN Util::TaskFunc taskFunc, flIN void *pUserData, flOUT Util::Task **ppTask)
{
  return flIMPL->m_pool.Add(taskFunc, pUserData, ppTask);
}

void ThreadQueue::Flush()
{
  flIMPL->m_pool.Flush();
}

void ThreadQueue::Pause()
{
  flIMPL->m_pool.Pause();
}

void ThreadQueue::Resume()
{
  flIMPL->m_pool.Resume();
}

bool ThreadQueue::IsPaused() const
{
  return flIMPL->m_pool.IsPaused();
}

int64_t ThreadQueue::GetCount() const
{
  return flIMPL->m_pool.GetCount();
}
