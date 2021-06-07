#include "scene/flVisitor.h"
#include "scene/flComponent.h"
#include "scene/flNode.h"
#include "scene/flTransform.h"

namespace flEngine
{
  namespace Scene
  {
    bool Visitor::VisitNode(flIN Node * pNode)
    {
      if (pNode == nullptr)
        return false;

      if (OnEnterNode(pNode))
      {
        Transform * pNextTransform = nullptr;
        for (int64_t i = 0; i < pNode->GetComponentCount(); ++i)
        {
          Component * pComponent = pNode->GetComponentByIndex(i);
          if (pNextTransform == nullptr && pComponent->Is(Transform::TypeID())) {
            pNextTransform = (Transform*)pComponent;
          }
          else {
            VisitComponent(pComponent);
          }
        }

        // If the node had a transform attached, visit the children
        if (pNextTransform != nullptr) {
          for (int64_t i = 0; i < pNextTransform->GetChildCount(); ++i)
            VisitNode(pNextTransform->GetChild(i)->GetNode());
        }

        OnLeaveNode(pNode);
        return true;
      }

      return false;
    }

    bool Visitor::VisitComponent(flIN Component * pComponent)
    {
      if (pComponent == nullptr)
        return false;

      if (OnEnterComponent(pComponent)) {
        OnLeaveComponent(pComponent);
        return true;
      }

      return false;
    }

    bool Visitor::OnEnterNode(flIN Node * pNode) { return true; }
    void Visitor::OnLeaveNode(flIN Node * pNode) {}
    bool Visitor::OnEnterComponent(flIN Component * pComponent) { return true; }
    void Visitor::OnLeaveComponent(flIN Component * pComponent) {}
  }
}
