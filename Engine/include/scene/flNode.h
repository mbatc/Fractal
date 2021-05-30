#pragma once

#include "../flInterface.h"
#include "../flRef.h"

namespace flEngine
{
  namespace Scene
  {
    class Impl_Node;

    class Component;

    class flEXPORT Node : public Interface
    {
      flPIMPL_DEF(Node);

    public:
      Node(flIN int64_t id, flIN char const * name = "Node");

      /**
       * @brief Get the ID of the Node.
       */
      int64_t GetID() const;

      /**
       * @brief Get the name of this node.
       */
      char const * GetName() const;

      /**
       * @brief Set the name of this node.
       */
      void SetName(flIN char const * name);

      /**
       * @brief Get the number of components attached to this node.
       */
      int64_t GetComponentCount() const;

      /**
       * @brief Add a component to the node.
       */
      template<typename T, typename... Args>
      Ref<T> AddComponent(Args&&... args) {
        T* pNewComponent = flNew (flAllocT(T, 1)) T(std::forward<Args>(args)...);
        Ref<T> pRef = MakeRef((T*)AddComponent(pNewComponent), true);
        pNewComponent->DecRef();
        return pRef;
      }

      /**
       * @brief Get a component attached to this node.
       */
      template<typename T>
      Ref<T> GetComponent() const {
        return MakeRef((T*)GetComponent(T::TypeID()), true);
      }

    protected:
      Component * AddComponent(flIN Component* pComponent);
      Component const * GetComponent(flIN int64_t typeID) const;
    };
  }
}
