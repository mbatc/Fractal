#pragma once

#include "../flInterface.h"
#include "../flRef.h"

namespace flEngine
{
  namespace Scene
  {
    class Impl_Node;

    class Component;

    class Node : public Interface
    {
      flPIMPL_DEF(Node);
    public:
      char const * GetName() const;

      void SetName(flIN char const * name) const;

      int64_t GetComponentCount() const;

      template<typename T>
      Ref<T> AddComponent();

    protected:
      Component* AddComponent(Component *pComponent);
    };
  }
}
