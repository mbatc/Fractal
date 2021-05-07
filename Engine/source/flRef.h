#ifndef fl_Ref_h__
#define fl_Ref_h__

#include "flInterface.h"

namespace flEngine
{
  template<typename T>
  class Ref
  {
  public:
    Ref(Interface *pInterface) { Set(pInterface); }
    Ref(Ref&& o) { *this = std::move(o); }
    Ref(Ref const& o) { *this = o; }
    ~Ref() { Set(nullptr); }

    T& operator*() { return *Get(); }
    T* operator->() { return Get(); }

    T const& operator*() const { return *Get(); }
    T const* operator->() const { return Get(); }

    T* Get() { return (T*)m_pInterface; }
    T const* Get() const { return (T*)m_pInterface; }

    operator T* ()              { return Get(); }
    operator T const * () const { return Get(); }

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
