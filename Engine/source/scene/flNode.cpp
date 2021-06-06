#include "scene/flComponent.h"
#include "scene/flScene.h"
#include "scene/flNode.h"
#include "ctString.h"

namespace flEngine
{
  namespace Scene
  {
    class Impl_Node
    {
    public:
      ctString name;

      int64_t id;

      ctVector<Ref<Component>> components;

      Scene * m_pScene;
    };

    flPIMPL_IMPL(Node);

    Node::Node(flIN int64_t id, flIN char const* name) {
      Impl()->id   = id;
      Impl()->name = name;
    }

    int64_t Node::GetID() const {
      return Impl()->id;
    }

    char const* Node::GetName() const {
      return Impl()->name.c_str();
    }

    void Node::SetName(flIN char const* name) {
      Impl()->name = name;
    }

    int64_t Node::GetComponentCount() const {
      return Impl()->components.size();
    }

    Component* Node::AddComponent(flIN Component* pNewComponent) {
      for (Ref<Component> const & pComponent : Impl()->components) {
        if (pComponent->GetType() == pNewComponent->GetType()) {
          return nullptr;
        }
      }

      pNewComponent->SetNode(this);
      Impl()->components.push_back(MakeRef(pNewComponent, true));
      return pNewComponent;
    }

    Component *Node::GetComponent(flIN int64_t typeID) {
      return GetComponentByIndex(FindComponent(typeID));
    }

    Component const *Node::GetComponent(flIN int64_t typeID) const {
      return GetComponentByIndex(FindComponent(typeID));
    }

    Component *Node::GetComponent(flIN char const *typeName) {
      return GetComponentByIndex(FindComponent(typeName));
    }

    Component const *Node::GetComponent(flIN char const *typeName) const {
      return GetComponentByIndex(FindComponent(typeName));
    }

    Component *Node::GetComponentByIndex(flIN int64_t index) {
      return index < 0 || index >= GetComponentCount() ? nullptr : Impl()->components[index];
    }

    Component const *Node::GetComponentByIndex(flIN int64_t index) const {
      return index < 0 || index >= GetComponentCount() ? nullptr : Impl()->components[index];
    }

    int64_t Node::FindComponent(flIN int64_t typeID) const {
      int64_t numComponents = GetComponentCount();
      for (int64_t i = 0; i < numComponents; ++i) {
        if (GetComponentByIndex(i)->GetTypeID() == typeID) {
          return i;
        }
      }

      return -1;
    }

    int64_t Node::FindComponent(flIN char const * typeName) const {
      int64_t numComponents = GetComponentCount();
      for (int64_t i = 0; i < numComponents; ++i) {
        if (strcmp(typeName, GetComponentByIndex(i)->GetType()) == 0) {
          return i;
        }
      }

      return -1;
    }

    void Node::SetScene(flIN Scene *pScene) {
      Impl()->m_pScene = pScene;
    }

    Scene *Node::GetScene() {
      return Impl()->m_pScene;
    }

    Scene const *Node::GetScene() const {
      return Impl()->m_pScene;
    }
  }
}
