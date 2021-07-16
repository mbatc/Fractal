#pragma once

#include "flIApplication.h"
#include "flModule.h"

#include "ctVector.h"
#include "ctString.h"
#include "ctKeyValue.h"

namespace Fractal
{
  class IWindow;
  class ITaskQueue;
  class IEventQueue;
  class Module;

  namespace Impl
  {
    class Application : public IApplication
    {
      FRACTAL_DEFAULT_INTERFACE;

    public:
      Application(char const* graphicsAPIName);

      void HandleEvent(Event* pEvent);
      template<typename ReturnT, typename... Args>
      bool InvokeBehaviour(ReturnT(IApplicationBehaviour::* func)(Args...), Args&& ... args)
      {
        (m_pApp->*func)(args...);
        for (int64_t i = 0; i < m_subSystems.size(); ++i)
          (m_subSystems[i].m_val->*func)(args...);
        return true;
      }

      bool Startup();
      void Shutdown();
      void PreUpdate();
      void Update();
      void PostUpdate();
      void PreRender();
      void Render();
      void PostRender();
      void BeginFrame();
      void EndFrame();
      void ProcessQueuedTasks();

      virtual void AddModule(Module* pSystem, char const* name) override;

      virtual Module* GetModule(char const* name) override;

      virtual int Run() override;

      virtual void Close() override;

      virtual void SetRootBehaviour(IApplicationBehaviour *pBehaviour);

      ITask* EnqueueTask(flIN ITask* pTask);
      int64_t Await(flIN ITask* pTask);
      int64_t MainThreadID();

      API* GetGraphicsAPI() const;
      IWindow* GetMainWindow() const;

    private:
      // Application state
      bool         m_isRunning = true;

      // Core components of an application
      Ref<API>        m_pGraphics = nullptr;
      Ref<IWindow>    m_pMainWindow = nullptr;
      Ref<IEventQueue> m_pSystemEvents = nullptr;

      int64_t m_mainThreadID = 0;
      Ref<ITaskQueue> m_pTaskQueue; // The applications task queue. These are executed on the main thread

      // Custom application sub systems
      ctVector<ctKeyValue<ctString, Ref<Module>>> m_subSystems;

      uint64_t m_frameStartTime;
    };
  }
}
