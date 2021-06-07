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
      bool VisitNode(flIN Node * pNode);
      bool VisitComponent(flIN Component * pComponent);

      virtual bool OnEnterNode(flIN Node * pNode);
      virtual void OnLeaveNode(flIN Node * pNode);
      virtual bool OnEnterComponent(flIN Component * pComponent);
      virtual void OnLeaveComponent(flIN Component * pComponent);
    };
  }
}
