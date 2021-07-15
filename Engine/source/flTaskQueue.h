#pragma once

#include "flITaskQueue.h"
#include "flThreads.h"
#include "flRef.h"
#include "ctVector.h"

namespace Fractal
{
  class ITask;

  namespace Impl
  {
    class TaskQueue : public ITaskQueue
    {
      FRACTAL_DEFAULT_INTERFACE;

    public:
      TaskQueue();

      virtual bool TaskQueue::Add(flIN ITask* pTask) override;
      virtual void Flush() override;
      virtual int64_t RunNext() override;
      virtual bool HasNext() const override;
      virtual int64_t GetCount() const override;

    private:
      ctVector<Ref<ITask>>   m_tasks;
      std::unique_ptr<Mutex> m_lock;
    };
  }
}
