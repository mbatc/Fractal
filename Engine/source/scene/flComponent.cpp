#include "scene/flComponent.h"
#include "scene/flNode.h"

namespace flEngine
{
  namespace Scene
  {
    class Impl_Component
    {
    public:
      Node *m_pNode;
    };

    flPIMPL_IMPL(Component);

    int64_t Component::GetNextTypeID()
    {
      static int64_t typeID = 1;
      return typeID++;
    }

    bool Component::Is(flIN int64_t typeID)
    {
      return flEngine::Scene::ComponentRegistry::IsBase(typeID, GetTypeID());
    }

    Node const *Component::_GetNode() const
    {
      return Impl()->m_pNode;
    }

    void Component::SetNode(Node * pParent) {
      Impl()->m_pNode = pParent;
    }

    Node *Component::_GetNode()
    {
      return Impl()->m_pNode;
    }
  }

}

