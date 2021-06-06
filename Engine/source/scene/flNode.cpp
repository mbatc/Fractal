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

    Component const * Node::GetComponent(flIN int64_t typeID) const {
      for (Ref<Component> const& pComponent : Impl()->components) {
        if (pComponent->GetTypeID() == typeID) {
          return pComponent;
        }
      }

      return nullptr;
    }

    void Node::SetScene(flIN Scene *pScene) {
      Impl()->m_pScene = pScene;
    }

    Scene *Node::_GetScene() {
      return Impl()->m_pScene;
    }

    Scene const *Node::_GetScene() const {
      return Impl()->m_pScene;
    }
  }
}
