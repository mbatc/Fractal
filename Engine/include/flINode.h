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

  class flEXPORT INode : public Interface
  {
    friend class SceneGraph;

  public:
    /**
     * @brief Get the ID of the Node.
     *
     * @return The int ID of the node
     */
    virtual int64_t GetID() const = 0;

    /**
     * @brief Get the name of this node.
     *
     * @return The name of the node as a c-string.
     */
    virtual char const* GetName() const = 0;

    /**
     * @brief Set the name of this node.
     *
     * @param [in] name The name to assign to the node.
     */
    virtual void SetName(flIN char const* name) = 0;

    /**
     * @brief Check if the node is active.
     */
    virtual bool IsActive() const = 0;

    virtual void SetActive(flIN bool active) = 0;

    /**
     * @brief Check if the node should be visible.
     */
    virtual bool IsVisible() const = 0;

    virtual void SetVisible(flIN bool visible) = 0;

    /**
     * @brief Get the number of components attached to this node.
     *
     * @return The number of components attached to the node.
     */
    virtual int64_t GetComponentCount() const = 0;

    /**
     * @brief Get this nodes parent.
     *
     * @return A pointer this nodes parent Node.
     */
    virtual INode* GetParent() = 0;
    virtual INode const* GetParent() const = 0;

    /**
     * @brief Set this nodes parent
     */
    virtual void SetParent(flIN INode* pParent) = 0;

    /**
     * @brief Get a child of this node
     *
     * @param [in] index The index of the child to retrieve, where 0 <= index < GetChildCount().
     *
     * @return A pointer to the child Node, or nullptr if index is out of bounds.
     */
    virtual INode* GetChild(flIN int64_t index) = 0;
    virtual INode const* GetChild(flIN int64_t index) const = 0;

    /**
     * @brief Get the number of children attached to this node.
     *
     * @return The number of children.
     */
    virtual int64_t GetChildCount() const = 0;

    virtual bool RemoveChild(flIN int64_t index) = 0;

    /**
     * @brief Get a pointer to the SceneGraph that this Node belongs to.
     *
     * @return A pointer to the scene.
     */
    virtual SceneGraph* GetScene() = 0;
    virtual SceneGraph const* GetScene() const = 0;

    /**
     * @brief Get a component attached to this node using it's type ID
     */
    virtual Component* GetComponentByType(flIN int64_t typeID) = 0;
    virtual Component const* GetComponentByType(flIN int64_t typeID) const = 0;

    /**
     * @brief Get a component attached to this node using it's registered type name.
     */
    virtual Component* GetComponentByType(flIN char const* typeName) = 0;
    virtual Component const* GetComponentByType(flIN char const* typeName) const = 0;

    /**
     * @brief Get a component attached to this node using it's index
     */
    virtual Component* GetComponent(flIN int64_t index) = 0;
    virtual Component const* GetComponent(flIN int64_t index) const = 0;

    /**
     * @brief Get the transform component attached to this node.
     */
    virtual Transform* GetTransform() = 0;
    virtual Transform const* GetTransform() const = 0;

    /**
     * @brief Find the index of a component attached to this node.
     *
     * @return The index of the component, or -1 if it does not exist.
     */
    virtual int64_t FindComponent(flIN int64_t typeID) const = 0;
    virtual int64_t FindComponent(flIN char const* typeName) const = 0;

    /**
     * @brief Remove a component from the node.
     */
    virtual bool RemoveComponent(flIN int64_t index) = 0;
    virtual bool RemoveComponentByType(flIN int64_t typeID) = 0;
    virtual bool RemoveComponentByType(flIN char const* typeName) = 0;

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

    inline std::vector<INode const*> GetChildren() const
    {
      int64_t childCount = GetChildCount();
      std::vector<INode const*> ret;
      ret.reserve(childCount);
      for (int64_t i = 0; i < childCount; ++i)
        ret.push_back(GetChild(i));
      return ret;
    }

    inline std::vector<INode*> GetChildren()
    {
      int64_t childCount = GetChildCount();
      std::vector<INode*> ret;
      ret.reserve(childCount);
      for (int64_t i = 0; i < childCount; ++i)
        ret.push_back(GetChild(i));
      return ret;
    }
  };
}

extern "C" {
  flEXPORT Fractal::INode* Fractal_CreateNode(flIN Fractal::SceneGraph* pScene, flIN int64_t id, flIN char const* name);
}
