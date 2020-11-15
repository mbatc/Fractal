#include "threads/flThreads.h"
#include "util/flTaskQueue.h"
#include "atVector.h"
#include <type_traits>

using namespace flEngine;
using namespace flEngine::Util;

namespace flEngine
{
  namespace Util
  {
    class flPIMPL_CLASS(TaskQueue)
    {
    public:
      bool Add(Task *pTask)
      {
        if (!pTask)
          return false;
        TaskData newTask;
        newTask.pTask = pTask;
        AddTask(newTask);
        return true;
      }

      bool Add(TaskFunc taskFunc, void *pUserData)
      {
        if (!taskFunc)
          return false;

        TaskData newTask;
        newTask.TaskCallback = taskFunc;
        newTask.pCallbackUserData = pUserData;
        AddTask(newTask);
        return true;
      }

      void Flush()
      {
        int64_t currentCount = GetCount();
        while (currentCount-- > 0)
          RunNext();
      }

      int64_t RunNext()
      {
        if (!HasNext())
          return -1;

        m_lock.lock();
        TaskData nextTask = m_tasks.front();
        m_tasks.pop_front();
        m_lock.unlock();

        int64_t result = -1;
        if (nextTask.pTask)
        {
          result = nextTask.pTask->Run();
          nextTask.pTask->DecRef();
        }
        else if (nextTask.TaskCallback)
        {
          result = nextTask.TaskCallback(nextTask.pCallbackUserData);
        }

        return result;
      }

      bool HasNext()
      {
        return GetCount() > 0;
      }

      int64_t GetCount()
      {
        m_lock.lock();
        int64_t count = m_tasks.size();
        m_lock.unlock();
        return count;
      }

    protected:
      struct TaskData
      {
        TaskFunc TaskCallback = nullptr;
        void *pCallbackUserData = nullptr;

        Task *pTask = nullptr;
      };

      void AddTask(const TaskData &newTask)
      {
        if (newTask.pTask)
          newTask.pTask->IncRef();

        m_lock.lock();
        m_tasks.push_back(newTask);
        m_lock.unlock();
      }

      Threads::Mutex     m_lock;
      atVector<TaskData> m_tasks;
    };
  }
}

flPIMPL_IMPL(TaskQueue)

#define flIMPL flPIMPL(TaskQueue)

bool TaskQueue::Add(flIN Task *pTask)
{
  return flIMPL->Add(pTask);
}

bool TaskQueue::Add(flIN TaskFunc taskFunc, flIN void *pUserData)
{
  return flIMPL->Add(taskFunc, pUserData);
}

void TaskQueue::Flush()
{
  flIMPL->Flush();
}

int64_t TaskQueue::RunNext()
{
  return flIMPL->RunNext();
}

bool TaskQueue::HasNext() const
{
  return flIMPL->HasNext();
}

int64_t TaskQueue::GetCount() const
{
  return flIMPL->GetCount();
}
