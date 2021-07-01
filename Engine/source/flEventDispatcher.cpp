#include "flEventDispatcher.h"
#include "flRef.h"

namespace Fractal
{
  class Impl_EventDispatcher
  {
  public:
    bool Dispatch(flIN Event* pEvent)
    {
      return m_handlers[pEvent->id] == nullptr || m_handlers[pEvent->id]->OnEvent(pEvent);
    }

    void OnEvent(flIN EventID type, flIN IEventHandler* pHandler)
    {
      m_handlers[type] = MakeRef(pHandler, true);
    }

    Ref<IEventHandler> m_handlers[Event_Count];
  };

  flPIMPL_IMPL(EventDispatcher);

  bool EventDispatcher::Dispatch(flIN Event* pEvent)
  {
    return Impl()->Dispatch(pEvent);
  }

  void EventDispatcher::OnEvent(flIN EventID type, flIN IEventHandler* pHandler)
  {
    Impl()->OnEvent(type, pHandler);
  }
}

