#include "flThreads.h"
#include "flThreadPool.h"
#include "flIThreadQueue.h"

namespace Fractal
{
  namespace Impl
  {
    class ThreadQueue : public IThreadQueue
    {
      FRACTAL_DEFAULT_INTERFACE;

    public:
      ThreadQueue();

      virtual bool Add(flIN ITask* pTask) override;
      virtual void Flush()override;
      virtual void Pause()override;
      virtual void Resume()override;
      virtual bool IsPaused() const override;
      virtual int64_t GetCount() const override;

    private:
      ThreadPool m_pool;
    };
  }
}
