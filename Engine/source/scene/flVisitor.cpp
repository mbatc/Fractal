#include "scene/flVisitor.h"
#include "scene/flComponent.h"
#include "scene/flNode.h"
#include "scene/flTransform.h"

namespace flEngine
{
  namespace Scene
  {
    bool Visitor::_VisitNode(flIN Node *pNode)
    {
      if (OnEnterNode(pNode))
      {
        for (int64_t i = 0; i < pNode->GetComponentCount(); ++i)
          VisitComponent(pNode->GetComponent(i));
      }
    }

    bool Visitor::_VisitComponent(flIN Component *pComponent)
    {
      if (pComponent->Is(Transform::TypeID())) {
        Ref<Transform> transform = pComponent->As<Transform>();
        for (int64_t i = 0; i < transform->GetChildCount(); ++i)
          _VisitNode(transform->GetChild(i)->GetNode());
      }
    }

    bool Visitor::_OnEnterNode(flIN Node *pNode) { return true; }
    bool Visitor::_OnLeaveNode(flIN Node *pNode) { return true; }
    bool Visitor::_OnEnterComponent(flIN Component *pComponent) { return true; }
    bool Visitor::_OnLeaveComponent(flIN Component *pComponent) { return true; }

  }
}
