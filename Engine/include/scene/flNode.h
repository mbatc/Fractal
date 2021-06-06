#pragma once

#include "../flInterface.h"
#include "../flRef.h"

namespace flEngine
{
  namespace Scene
  {
    class Impl_Node;

    class Scene;
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
      T * GetComponent() const {
        return (T*)GetComponent(T::TypeID());
      }

      Scene * GetScene();
      Scene const * GetScene() const;

      /**
       * @brief Get a component attached to this node using it's type ID
       */
      Component * GetComponent(flIN int64_t typeID);
      Component const * GetComponent(flIN int64_t typeID) const;

      /**
       * @brief Get a component attached to this node using it's registered type name.
       */
      Component * GetComponent(flIN char const *typeName);
      Component const * GetComponent(flIN char const * typeName) const;

      /**
       * @brief Get a component attached to this node using it's index
       */
      Component * GetComponentByIndex(flIN int64_t index);
      Component const * GetComponentByIndex(flIN int64_t index) const;

      int64_t FindComponent(flIN int64_t typeID) const;
      int64_t FindComponent(flIN char const * typeName) const;

    protected:
      Component * AddComponent(flIN Component * pComponent);

    private:
      void SetScene(flIN Scene *pScene);
    };
  }
}
