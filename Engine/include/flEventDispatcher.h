#pragma once

#include "flInterface.h"
#include "flEvent.h"

namespace Fractal
{
    class Impl_EventDispatcher;

    class flEXPORT IEventHandler : public Interface
    {
    public:
      virtual bool OnEvent(flIN Event *pEvent) = 0;
    };

    class flEXPORT EventDispatcher : public Interface
    {
      flPIMPL_DEF(EventDispatcher);

    public:
      typedef bool(*HandlerFunc)(EventDispatcher *, Event *, void *);

      /**
       * @brief Send an event to the event handler.
       */
      bool Dispatch(flIN Event *pEvent);

      void OnEvent(flIN EventID type, flIN IEventHandler *pHandler);

    protected:
      /**
       * @brief Bind a member function of a derived class
       */
      template<typename DispatcherType>
      void OnEvent(EventID type, bool(DispatcherType:: *handler)(flIN Event *))
      {
        typedef bool(DispatcherType:: *MemFunType)(Event *);

        class HandlerImpl : public IEventHandler
        {
          HandlerImpl(EventDispatcher *pDispatcher, MemFunType memFunc)
            : m_memFunc(memFunc)
            , m_pDispatcher((DispatcherType *)pDispatcher)
          {}

        public:
          static HandlerImpl *Create(EventDispatcher *pDispatcher, MemFunType memFunc) { return flNew(flAlloc(sizeof(HandlerImpl))) HandlerImpl(pDispatcher, memFunc); }

          virtual bool OnEvent(flIN Event *pEvent) override { return (m_pDispatcher->*m_memFunc)(pEvent); }

        private:
          MemFunType m_memFunc = nullptr;
          DispatcherType *m_pDispatcher = nullptr;
        };

        IEventHandler *pHandler = HandlerImpl::Create(this, handler);
        OnEvent(type, pHandler);
        pHandler->DecRef();
      }
    };
}
