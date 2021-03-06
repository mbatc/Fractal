#include "flComponent.h"
#include "flNode.h"

namespace Fractal
{
  class Impl_Component
  {
  public:
    Node* m_pNode;
  };

  flPIMPL_IMPL(Component);

  void Component::OnUpdate()     {}
  void Component::OnPreUpdate()  {}
  void Component::OnPostUpdate() {}

  void Component::OnRender()     {}
  void Component::OnPreRender()  {}
  void Component::OnPostRender() {}

  int64_t Component::GetNextTypeID()
  {
    static int64_t typeID = 1;
    return typeID++;
  }

  bool Component::Register() { return true; }

  bool Component::Is(flIN int64_t typeID) const
  {
    return this && (typeID == GetTypeID() || ComponentRegistry::IsBase(typeID, GetTypeID()));
  }

  Node const* Component::GetNode() const
  {
    return Impl()->m_pNode;
  }

  void Component::SetNode(Node* pParent)
  {
    Impl()->m_pNode = pParent;
  }

  Node* Component::GetNode()
  {
    return Impl()->m_pNode;
  }
}

