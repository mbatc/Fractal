#include "scene/flTransform.h"
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

    Scene::Scene()
    {
      // Add a node and set it to the root node
      Impl()->m_root = MakeRef(AddNode("Root"), true);
    }

    Node* Scene::AddNode(char const* name, flIN int64_t parentID) {
      return AddNode(GetNextNodeID(), name, parentID);
    }

    int64_t Scene::GetNextNodeID() {
      static int64_t id = 0;
      return id++;
    }

    Node* Scene::AddNode(flIN int64_t id, flIN char const* name, flIN int64_t parentID) {
      if (Impl()->m_nodes.Contains(id))
        return nullptr;

      // Create and add the node
      Node * pNode = flNew Node(id, name);
      pNode->SetScene(this);
      pNode->AddComponent<Transform>();
      Impl()->m_nodes.Add(id, pNode);

      // Set the nodes parent transform
      Node * pParent = Impl()->m_nodes.GetOr(parentID, Impl()->m_root.Get());
      if (pParent)
        pNode->GetComponent<Transform>()->SetParent(pParent->GetComponent<Transform>());

      // Return the node
      return pNode;
    }

    Node * Scene::GetNode(flIN int64_t id) {
      return Impl()->m_nodes.GetOr(id, nullptr);
    }
    
    Node const * Scene::GetNode(flIN int64_t id) const {
      return Impl()->m_nodes.GetOr(id, nullptr);
    }

    Node * Scene::GetRootNode() {
      return Impl()->m_root.Get();
    }
    Node const * Scene::GetRootNode() const {
      return Impl()->m_root.Get();
    }
  }
}
