#pragma once

#include "flIThreadPool.h"
#include "flThreads.h"
#include "flRef.h"
#include "ctVector.h"

namespace Fractal
{
  class ITaskQueue;

  namespace Impl
  {
    class ThreadPool : public IThreadPool
    {
      FRACTAL_DEFAULT_INTERFACE;

    public:
      ThreadPool(const int64_t& threadCount);
      ~ThreadPool();

      virtual bool Add(flIN ITask* pTask) override;
      virtual void Flush() override;
      virtual void Pause() override;
      virtual void Resume() override;
      virtual bool IsPaused() const override;
      virtual int64_t GetCount() const override;

    private:
      void Run();

      volatile bool m_paused = false;
      volatile bool m_running = false;
      volatile bool m_isPaused = false;

      Ref<ITaskQueue>   m_pQueue;
      ctVector<Thread*> m_threads;
    };
  }
}
