#pragma once

#include "../flRef.h"

namespace flEngine
{
  namespace Scene
  {
    class Node;
    class Component;

    class flEXPORT Visitor : public Interface
    {
    public:
      inline bool VisitNode(flIN Ref<Node> pNode) {
        return _VisitNode(pNode);
      }

      inline bool VisitComponent(flIN Ref<Component> pComponent) {
        return _VisitComponent(pComponent);
      }

      inline bool OnEnterNode(flIN Ref<Node> pNode) {
        return _OnEnterNode(pNode);
      }

      inline bool OnLeaveNode(flIN Ref<Node> pNode) {
        return _OnLeaveNode(pNode);
      }

      inline bool OnEnterComponent(flIN Ref<Component> pComponent) {
        return _OnEnterComponent(pComponent);
      }

      inline bool OnLeaveComponent(flIN Ref<Component> pComponent) {
        return _OnLeaveComponent(pComponent);
      }

    protected:
      virtual bool _OnEnterNode(flIN Node *pNode);
      virtual bool _OnLeaveNode(flIN Node *pNode);

      virtual bool _OnEnterComponent(flIN Component *pComponent);
      virtual bool _OnLeaveComponent(flIN Component *pComponent);

    private:
      bool _VisitNode(flIN Node *pNode);
      bool _VisitComponent(flIN Component *pComponent);
    };
  }
}
