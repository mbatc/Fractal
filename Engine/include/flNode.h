#pragma once

#include "flInterface.h"
#include "flRef.h"
#include <vector>

namespace Fractal
{
  class Impl_Node;

  class SceneGraph;
  class Component;
  class Transform;

  class flEXPORT Node : public Interface
  {
    flPIMPL_DEF(Node);

    friend class SceneGraph;

  public:
    /**
     * @brief Construct a new node with the given ID and name.
     *
     * @param [in] pScene A pointer to the scene that created the node.
     * @param [in] id     The ID to assign to the node.
     * @param [in] name   The name of the node.
     */
    Node(flIN SceneGraph* pScene, flIN int64_t id, flIN char const* name = "Node");

    /**
     * @brief Get the ID of the Node.
     *
     * @return The int ID of the node
     */
    int64_t GetID() const;

    /**
     * @brief Get the name of this node.
     *
     * @return The name of the node as a c-string.
     */
    char const* GetName() const;

    /**
     * @brief Set the name of this node.
     *
     * @param [in] name The name to assign to the node.
     */
    void SetName(flIN char const* name);

    /**
     * @brief Get the number of components attached to this node.
     *
     * @return The number of components attached to the node.
     */
    int64_t GetComponentCount() const;

    /**
     * @brief Get this nodes parent.
     *
     * @return A pointer this nodes parent Node.
     */
    Node* GetParent();
    Node const* GetParent() const;

    /**
     * @brief Set this nodes parent
     */
    void SetParent(flIN Node* pParent);

    /**
     * @brief Get a child of this node
     *
     * @param [in] index The index of the child to retrieve, where 0 <= index < GetChildCount().
     *
     * @return A pointer to the child Node, or nullptr if index is out of bounds.
     */
    Node* GetChild(flIN int64_t index);
    Node const* GetChild(flIN int64_t index) const;

    /**
     * @brief Get the number of children attached to this node.
     *
     * @return The number of children.
     */
    int64_t GetChildCount() const;

    /**
     * @brief Get a pointer to the SceneGraph that this Node belongs to.
     *
     * @return A pointer to the scene.
     */
    SceneGraph* GetScene();
    SceneGraph const* GetScene() const;

    /**
     * @brief Get a component attached to this node using it's type ID
     */
    Component* GetComponentByType(flIN int64_t typeID);
    Component const* GetComponentByType(flIN int64_t typeID) const;

    /**
     * @brief Get a component attached to this node using it's registered type name.
     */
    Component* GetComponentByType(flIN char const* typeName);
    Component const* GetComponentByType(flIN char const* typeName) const;

    /**
     * @brief Get a component attached to this node using it's index
     */
    Component* GetComponent(flIN int64_t index);
    Component const* GetComponent(flIN int64_t index) const;

    /**
     * @brief Get the transform component attached to this node.
     */
    Transform* GetTransform();
    Transform const* GetTransform() const;

    /**
     * @brief Find the index of a component attached to this node.
     *
     * @return The index of the component, or -1 if it does not exist.
     */
    int64_t FindComponent(flIN int64_t typeID) const;
    int64_t FindComponent(flIN char const* typeName) const;

    /**
     * @brief Remove a component from the node.
     */
    bool RemoveComponent(flIN int64_t index);
    bool RemoveComponentByType(flIN int64_t typeID);
    bool RemoveComponentByType(flIN char const* typeName);

    /**
     * @brief Add a component to the node.
     *
     * @param args... Arguments to be forwarded to the Component's constructor.
     */
    template<typename T, typename... Args>
    Ref<T> AddComponent(Args&& ... args)
    {
      T* pNewComponent = flNew(flAllocT(T, 1)) T(std::forward<Args>(args)...);
      Ref<T> pRef = MakeRef((T*)AddComponent(pNewComponent), true);
      pNewComponent->DecRef();
      return pRef;
    }

    /**
     * @brief Get a component attached to this node.
     */
    template<typename T>
    T const* GetComponent() const
    {
      return (T const*)GetComponentByType(T::TypeID());
    }

    /**
     * @brief Get a component attached to this node.
     *
     * @return A pointer to the component if it exists.
     */
    template<typename T>
    T* GetComponent()
    {
      return (T*)GetComponentByType(T::TypeID());
    }

    template<typename T>
    bool RemoveComponent()
    {
      return RemoveComponent(T::TypeID());
    }

    inline std::vector<Node const*> GetChildren() const
    {
      int64_t childCount = GetChildCount();
      std::vector<Node const*> ret;
      ret.reserve(childCount);
      for (int64_t i = 0; i < childCount; ++i)
        ret.push_back(GetChild(i));
      return ret;
    }

    inline std::vector<Node*> GetChildren()
    {
      int64_t childCount = GetChildCount();
      std::vector<Node*> ret;
      ret.reserve(childCount);
      for (int64_t i = 0; i < childCount; ++i)
        ret.push_back(GetChild(i));
      return ret;
    }

  private:
    Component* AddComponent(flIN Component* pComponent);
  };
}
