#pragma once

#include "../flInterface.h"
#include "flNode.h"

namespace flEngine
{
  namespace Scene
  {
    class Impl_Scene;

    class Node;

    class flEXPORT Scene : public Interface
    {
      flPIMPL_DEF(Scene);
    public:
      Scene();

      Node* AddNode(char const* name = "Node", flIN int64_t parentID = -1);

      Node* AddNode(flIN int64_t id, flIN char const* name = "Node", flIN int64_t parentID = -1);

      Node* GetNode(flIN int64_t id);
      Node const * GetNode(flIN int64_t id) const;

      Node * GetRootNode();
      Node const * GetRootNode() const;

    protected:
      int64_t GetNextNodeID();
    };
  }
}