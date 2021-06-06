#include "scene/flVisitor.h"
#include "scene/flComponent.h"
#include "scene/flNode.h"
#include "scene/flTransform.h"

namespace flEngine
{
  namespace Scene
  {
    bool Visitor::VisitNode(flIN Node *pNode)
    {
      if (OnEnterNode(pNode))
      {
        for (int64_t i = 0; i < pNode->GetComponentCount(); ++i)
          VisitComponent(pNode->GetComponentByIndex(i));
      }
    }

    bool Visitor::VisitComponent(flIN Component *pComponent)
    {
      if (pComponent->Is(Transform::TypeID())) {
        Ref<Transform> transform = pComponent->As<Transform>();
        for (int64_t i = 0; i < transform->GetChildCount(); ++i)
          VisitNode(transform->GetChild(i)->GetNode());
      }
    }

    bool Visitor::OnEnterNode(flIN Node *pNode) { return true; }
    bool Visitor::OnLeaveNode(flIN Node *pNode) { return true; }
    bool Visitor::OnEnterComponent(flIN Component *pComponent) { return true; }
    bool Visitor::OnLeaveComponent(flIN Component *pComponent) { return true; }

  }
}
