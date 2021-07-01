#pragma once

#include "flRef.h"

namespace Fractal
{
    template<typename T, typename... Args>
    class flEXPORT Visitor
      : public Visitor<T>
      , public Visitor<Args...>
    {
    public:
      using Visitor<T>::OnEnter;
      using Visitor<T>::OnLeave;
      using Visitor<Args...>::OnEnter;
      using Visitor<Args...>::OnLeave;
    };

    template<typename T>
    class flEXPORT Visitor<T>
    {
    public:
      virtual bool OnEnter(flIN T *pItem) { return false; }
      virtual void OnLeave(flIN T *pItem) {}
    };
}
