#pragma once

#include "flITask.h"
#include "flThreads.h"

namespace Fractal
{
  namespace Impl
  {
    class Task : public ITask
    {
      FRACTAL_DEFAULT_INTERFACE;

    public:
      Task(TaskFunc func, Interface *pTaskData)
        : m_func(func)
        , m_pTaskData(MakeRef(pTaskData, true))
      {}

      virtual int64_t Task::Run() override;
      virtual TaskStatus GetStatus() const override;
      virtual int64_t GetResult() const override;
      virtual int64_t Await() override;
      virtual void Reset() override;
      virtual int64_t DoTask() override;
      virtual bool Cancel() override;


    private:
      void SetStatus(TaskStatus status);
      void Lock() const;
      void Unlock() const;


      int64_t    m_result = -1;
      TaskStatus m_status = TaskStatus_Waiting;

      TaskFunc       m_func;
      Ref<Interface> m_pTaskData;
      
      std::unique_ptr<Mutex> m_lock = std::make_unique<Mutex>();
    };
  }
}
