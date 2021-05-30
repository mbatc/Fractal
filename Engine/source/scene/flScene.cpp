#include "scene/flScene.h"
#include "ctHashMap.h"

namespace flEngine
{
  namespace Scene
  {
    class Impl_Scene
    {
    public:
      Ref<Node> m_root;
      ctHashMap<int64_t, Node*> m_nodes;
    };

    flPIMPL_IMPL(Scene);


    int64_t Scene::GetNextNodeID()
    {
      static int64_t id = 0;
      return id++;
    }

    Node* Scene::_AddNode(flIN int64_t id, flIN char const* name)
    {
      if (Impl()->m_nodes.Contains(id))
        return nullptr;

      Node * pNode = flNew Node(id, name);
      Impl()->m_nodes.TryAdd(id, pNode);
      return pNode;
    }
  }
}
