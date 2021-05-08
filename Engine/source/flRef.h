#ifndef fl_Ref_h__
#define fl_Ref_h__

#include "flInterface.h"
#include <type_traits>

namespace flEngine
{
  template<typename T>
  class Ref
  {
  public:
    Ref(Interface *pInterface = nullptr) { Set(pInterface); }
    Ref(Ref&& o) { *this = std::move(o); }
    Ref(Ref const& o) { *this = o; }
    ~Ref() { Set(nullptr); }

    T & operator*() { return *Get(); }
    T * operator->() { return Get(); }

    T const &operator*() const { return *Get(); }
    T const *operator->() const { return Get(); }

    T * Get() { return (T*)m_pInterface; }
    T const* Get() const { return (T*)m_pInterface; }

    template<typename T2>
    T2 * As() { return (T2 const *)m_pInterface };
    template<typename T2>
    T2 const * As() const { return (T2 *)m_pInterface };

    explicit operator T* ()              { return Get(); }
    explicit operator T const * () const { return Get(); }

    operator bool() const { return Get() != nullptr; }

    bool operator==(T const *pPtr) const { return pPtr == Get(); }
    bool operator!=(T const *pPtr) const { return !(*this == pPtr); }

    Ref &operator=(Ref const &o)
    {
      Set(o.m_pInterface);
      return *this;
    }

    Ref &operator=(Ref &&o)
    {
      Set(o.m_pInterface);
      o.Set(nullptr);
      return *this;
    }

    void Set(Interface* pNewInterface)
    {
      m_pInterface->DecRef();
      m_pInterface = pNewInterface;
      m_pInterface->IncRef();
    }

  private:
    Interface* m_pInterface = nullptr;
  };
}

#endif // fl_Ref_h__
