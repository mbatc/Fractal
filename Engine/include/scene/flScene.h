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

      inline Ref<Node> AddNode(char const * name = "Node", flIN int64_t parentID = -1) {
        return AddNode(GetNextNodeID(), name, parentID);
      }

      inline Ref<Node> AddNode(flIN int64_t id, flIN char const* name = "Node", flIN int64_t parentID = -1) {
        return MakeRef<Node>(_AddNode(id, name), true);
      }

    protected:
      int64_t GetNextNodeID();

      Node* _AddNode(flIN int64_t id, flIN char const* name);
    };
  }
}