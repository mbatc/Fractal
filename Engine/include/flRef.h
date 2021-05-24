#ifndef fl_Ref_h__
#define fl_Ref_h__

#include "flInterface.h"
#include <type_traits>
#include <memory>
#include <utility>

namespace flEngine
{
  template<typename T>
  class Ref
  {
  public:
    Ref() = default;

    Ref(std::nullptr_t const &ptr) : m_pInterface(ptr) {}

    explicit Ref(T* pInterface, bool incRef) {
      Set(pInterface, incRef);
    }

    template<typename T2, std::enable_if_t<std::is_convertible_v<T*, T2*>, int> = 0>
    explicit Ref(T2* pInterface, bool incRef) {
      Set(pInterface, incRef);
    }

    template<typename T2, std::enable_if_t<std::is_convertible_v<T*, T2*>, int> = 0>
    Ref(Ref<T2> const & ref) {
      Set(ref.Get());
    }

    Ref(Ref&& o) {
      *this = std::move(o);
    }

    Ref(Ref const& o) {
      *this = o;
    }

    ~Ref() {
      Set(nullptr);
    }

    T& operator*() {
      return *Get();
    }

    T* operator->() {
      return Get();
    }

    T const & operator*() const {
      return *Get();
    }

    T const * operator->() const {
      return Get();
    }

    T* Get() {
      return (T*)m_pInterface;
    }

    T const* Get() const {
      return (T*)m_pInterface;
    }

    template<typename T2>
    T2* As() {
      return (T2 const*)m_pInterface
    };

    template<typename T2>
    T2 const* As() const {
      return (T2*)m_pInterface
    };

    operator T* () {
      return Get();
    }

    operator T const* () const {
      return Get();
    }

    operator bool() const {
      return Get() != nullptr;
    }

    bool operator==(T const* pPtr) const {
      return pPtr == Get();
    }

    bool operator!=(T const* pPtr) const {
      return !(*this == pPtr);
    }

    template<typename T2>
    Ref<T2> StaticCast() {
      return Ref<T2>(static_cast<T2*>(Get()), true);
    }

    template<typename T2>
    Ref<T2> DynamicCast() {
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
  Ref<T> MakeRef(T* pPtr, bool incRef) {
    return Ref<T>(pPtr, incRef);
  }

  template<typename T, typename... Args>
  Ref<T> MakeRef(Args&&... args) {
    return MakeRef(new (flAllocT(T, 1)) T(std::forward<Args>(args)...), false);
  }
}

#endif // fl_Ref_h__
