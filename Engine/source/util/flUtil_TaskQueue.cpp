#include "util/flUtil_TaskQueue.h"
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

        TaskData nextTask = m_tasks.front();
        m_tasks.pop_front();

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

      bool HasNext() const
      {
        return m_tasks.size() > 0;
      }

      int64_t GetCount() const
      {
        return m_tasks.size();
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

        m_tasks.push_back(newTask);
      }

      atVector<TaskData> m_tasks;
    };
  }
}

flPIMPL_IMPL(TaskQueue)

#define flIMPL flPIMPL(TaskQueue)

bool TaskQueue::Add(Task *pTask)
{
  return flIMPL->Add(pTask);
}

bool TaskQueue::Add(TaskFunc taskFunc, void *pUserData)
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
