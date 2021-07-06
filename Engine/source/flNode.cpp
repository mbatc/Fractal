#include "flTransform.h"
#include "flComponent.h"
#include "flSceneGraph.h"
#include "flNode.h"
#include "ctString.h"

namespace Fractal
{
  class Impl_Node
  {
  public:
    ctString name;

    int64_t id = -1;
    bool isVisible = true;
    bool isActive  = true;

    ctVector<Ref<Component>> components;

    Transform* m_pTransform = nullptr;
    SceneGraph* m_pScene = nullptr;
  };

  flPIMPL_IMPL(Node);

  Node::Node(flIN SceneGraph* pScene, flIN int64_t id, flIN char const* name)
  {
    Impl()->id = id;
    Impl()->name = name;
    Impl()->m_pScene = pScene;
  }

  int64_t Node::GetID() const
  {
    return Impl()->id;
  }

  char const* Node::GetName() const
  {
    return Impl()->name.c_str();
  }

  void Node::SetName(flIN char const* name)
  {
    Impl()->name = name;
  }

  bool Node::IsVisible() const
  {
    return Impl()->isVisible;
  }

  void Node::SetVisible(flIN bool visible)
  {
    Impl()->isVisible = visible;
  }

  bool Node::IsActive() const
  {
    return Impl()->isActive;
  }

  void Node::SetActive(flIN bool active)
  {
    Impl()->isActive = active;
  }

  Node* Node::GetParent()
  {
    return GetTransform()->GetParent()->GetNode();
  }

  Node const* Node::GetParent() const
  {
    return GetTransform()->GetParent()->GetNode();
  }

  void Node::SetParent(flIN Node* pParent)
  {
    GetTransform()->SetParent(pParent->GetTransform());
  }

  Node* Node::GetChild(flIN int64_t index)
  {
    return GetTransform()->GetChild(index)->GetNode();
  }

  Node const* Node::GetChild(flIN int64_t index) const
  {
    return GetTransform()->GetChild(index)->GetNode();
  }

  int64_t Node::GetChildCount() const
  {
    return GetTransform()->GetChildCount();
  }

  int64_t Node::GetComponentCount() const
  {
    return Impl()->components.size();
  }

  Component* Node::AddComponent(flIN Component* pNewComponent)
  {
    for (Ref<Component> const& pComponent : Impl()->components)
    {
      if (pComponent->GetType() == pNewComponent->GetType())
      {
        return nullptr;
      }
    }

    pNewComponent->SetNode(this);

    if (Impl()->m_pTransform == nullptr && pNewComponent->Is<Transform>())
      Impl()->m_pTransform = (Transform*)pNewComponent;

    Impl()->components.push_back(MakeRef(pNewComponent, true));
    return pNewComponent;
  }

  Component* Node::GetComponentByType(flIN int64_t typeID)
  {
    return GetComponent(FindComponent(typeID));
  }

  Component const* Node::GetComponentByType(flIN int64_t typeID) const
  {
    return GetComponent(FindComponent(typeID));
  }

  Component* Node::GetComponentByType(flIN char const* typeName)
  {
    return GetComponent(FindComponent(typeName));
  }

  Component const* Node::GetComponentByType(flIN char const* typeName) const
  {
    return GetComponent(FindComponent(typeName));
  }

  Component* Node::GetComponent(flIN int64_t index)
  {
    return index < 0 || index >= GetComponentCount() ? nullptr : Impl()->components[index];
  }

  Component const* Node::GetComponent(flIN int64_t index) const
  {
    return index < 0 || index >= GetComponentCount() ? nullptr : Impl()->components[index];
  }

  Transform* Node::GetTransform()
  {
    return Impl()->m_pTransform;
  }

  Transform const* Node::GetTransform() const
  {
    return Impl()->m_pTransform;
  }

  int64_t Node::FindComponent(flIN int64_t typeID) const
  {
    int64_t numComponents = GetComponentCount();
    for (int64_t i = 0; i < numComponents; ++i)
    {
      if (GetComponent(i)->GetTypeID() == typeID)
      {
        return i;
      }
    }

    return -1;
  }

  int64_t Node::FindComponent(flIN char const* typeName) const
  {
    int64_t numComponents = GetComponentCount();
    for (int64_t i = 0; i < numComponents; ++i)
    {
      if (strcmp(typeName, GetComponent(i)->GetType()) == 0)
      {
        return i;
      }
    }

    return -1;
  }

  bool Node::RemoveComponent(flIN int64_t index)
  {
    if (index < 0 || index >= GetComponentCount())
      return false;

    Impl()->components[index]->SetNode(nullptr);
    Impl()->components.erase(index);
    return true;
  }

  bool Node::RemoveComponentByType(flIN int64_t typeID)
  {
    return RemoveComponent(FindComponent(typeID));
  }

  bool Node::RemoveComponentByType(flIN char const* typeName)
  {
    return RemoveComponent(FindComponent(typeName));
  }

  SceneGraph* Node::GetScene()
  {
    return Impl()->m_pScene;
  }

  SceneGraph const* Node::GetScene() const
  {
    return Impl()->m_pScene;
  }
}
