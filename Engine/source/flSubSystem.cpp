#include "flSubSystem.h"
#include "flRef.h"

namespace flEngine
{
  class flPIMPL_CLASS(EventDispatcher)
  {
  public:
    bool Dispatch(flIN Platform::Event *pEvent)
    {
      return m_handlers[pEvent->id] == nullptr || m_handlers[pEvent->id]->OnEvent(pEvent);
    }

    void OnEvent(flIN Platform::EventID type, flIN IEventHandler* pHandler)
    {
      m_handlers[type] = MakeRef(pHandler, true);
    }
    
    Ref<IEventHandler> m_handlers[Platform::Event_Count];
  };

  flPIMPL_IMPL(EventDispatcher)

  bool EventDispatcher::Dispatch(flIN Platform::Event *pEvent)
  {
    return Impl()->Dispatch(pEvent);
  }

  void EventDispatcher::OnEvent(flIN Platform::EventID type, flIN IEventHandler* pHandler)
  {
    Impl()->OnEvent(type, pHandler);
  }
}
