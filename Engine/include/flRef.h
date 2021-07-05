#pragma once

#include "flInterface.h"
#include <type_traits>
#include <memory>
#include <utility>

namespace Fractal
{
  template<typename T>
  class Ref
  {
  public:
    Ref() = default;

    Ref(std::nullptr_t const& ptr) : m_pInterface(ptr) {}

    explicit Ref(T* pInterface, bool incRef)
    {
      Set(pInterface, incRef);
    }

    template<typename T2, std::enable_if_t<std::is_convertible_v<T*, T2*>, int> = 0>
    explicit Ref(T2* pInterface, bool incRef)
    {
      Set(pInterface, incRef);
    }

    template<typename T2, std::enable_if_t<std::is_convertible_v<T*, T2*>, int> = 0>
    Ref(Ref<T2> const& ref)
    {
      Set(ref.Get());
    }

    Ref(Ref&& o)
    {
      *this = std::move(o);
    }

    Ref(Ref const& o)
    {
      *this = o;
    }

    ~Ref()
    {
      Set(nullptr);
    }

    T* operator->() const
    {
      return Get();
    }

    T& operator*() const
    {
      return *Get();
    }

    T* Get() const
    {
      return (T*)m_pInterface;
    }

    template<typename T2>
    T2* As() const
    {
      return (T2*)m_pInterface
    };

    operator T* () const
    {
      return Get();
    }

    operator bool() const
    {
      return Get() != nullptr;
    }

    template<typename T2>
    Ref<T2> StaticCast() const
    {
      return Ref<T2>(static_cast<T2*>(Get()), true);
    }

    template<typename T2>
    Ref<T2> DynamicCast() const
    {
      return Ref<T2>(dynamic_cast<T2*>(Get()), true);
    }

    Ref& operator=(Ref const& o)
    {
      Set(o.m_pInterface);
      return *this;
    }

    Ref& operator=(Ref&& o)
    {
      Set(o.m_pInterface);
      o.Set(nullptr);
      return *this;
    }

    void Set(Interface* pNewInterface, bool incRef = true)
    {
      m_pInterface->DecRef();
      m_pInterface = pNewInterface;
      if (incRef)
        m_pInterface->IncRef();
    }

  private:
    Interface* m_pInterface = nullptr;
  };

  template<typename T>
  Ref<T> MakeRef(T* pPtr, bool incRef)
  {
    return Ref<T>(pPtr, incRef);
  }

  template<typename T, typename... Args>
  Ref<T> MakeRef(Args&& ... args)
  {
    return MakeRef(new (flAllocT(T, 1)) T(std::forward<Args>(args)...), false);
  }
}
