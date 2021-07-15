#include "flTransform.h"
#include "flComponent.h"
#include "flSceneGraph.h"
#include "flNode.h"
#include "ctString.h"

extern "C" {
  Fractal::INode* Fractal_CreateNode(flIN Fractal::SceneGraph* pScene, flIN int64_t id, flIN char const* name)
  {
    return flNew Fractal::Impl::Node(pScene, id, name);
  }
}

namespace Fractal
{
  namespace Impl
  {
    Node::Node(flIN SceneGraph* pScene, flIN int64_t id, flIN char const* name)
    {
      id = id;
      name = name;
      m_pScene = pScene;
    }

    int64_t Node::GetID() const
    {
      return id;
    }

    char const* Node::GetName() const
    {
      return name.c_str();
    }

    void Node::SetName(flIN char const* name)
    {
      name = name;
    }

    bool Node::IsVisible() const
    {
      return isVisible;
    }

    void Node::SetVisible(flIN bool visible)
    {
      isVisible = visible;
    }

    bool Node::IsActive() const
    {
      return isActive;
    }

    void Node::SetActive(flIN bool active)
    {
      isActive = active;
    }

    INode* Node::GetParent()
    {
      return GetTransform()->GetParent()->GetNode();
    }

    INode const* Node::GetParent() const
    {
      return GetTransform()->GetParent()->GetNode();
    }

    void Node::SetParent(flIN INode* pParent)
    {
      GetTransform()->SetParent(pParent != nullptr ? pParent->GetTransform() : nullptr);
    }

    INode* Node::GetChild(flIN int64_t index)
    {
      return GetTransform()->GetChild(index)->GetNode();
    }

    INode const* Node::GetChild(flIN int64_t index) const
    {
      return GetTransform()->GetChild(index)->GetNode();
    }

    int64_t Node::GetChildCount() const
    {
      return GetTransform()->GetChildCount();
    }

    bool Node::RemoveChild(flIN int64_t index)
    {
      return GetTransform()->RemoveChild(index);
    }

    int64_t Node::GetComponentCount() const
    {
      return components.size();
    }

    Component* Node::AddComponent(flIN Component* pNewComponent)
    {
      for (Ref<Component> const& pComponent : components)
      {
        if (pComponent->GetType() == pNewComponent->GetType())
        {
          return nullptr;
        }
      }

      pNewComponent->SetNode(this);

      if (m_pTransform == nullptr && pNewComponent->Is<Transform>())
        m_pTransform = (Transform*)pNewComponent;

      components.push_back(MakeRef(pNewComponent, true));
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
      return index < 0 || index >= GetComponentCount() ? nullptr : components[index];
    }

    Component const* Node::GetComponent(flIN int64_t index) const
    {
      return index < 0 || index >= GetComponentCount() ? nullptr : components[index];
    }

    Transform* Node::GetTransform()
    {
      return m_pTransform;
    }

    Transform const* Node::GetTransform() const
    {
      return m_pTransform;
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

      components[index]->SetNode(nullptr);
      components.erase(index);
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
      return m_pScene;
    }

    SceneGraph const* Node::GetScene() const
    {
      return m_pScene;
    }
  }
}
