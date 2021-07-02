#include "flTransform.h"
#include "flVisitor.h"
#include "flSceneGraph.h"
#include "ctHashMap.h"
#include <time.h>
#include <random>

namespace Fractal
{
  class Impl_SceneGraph
  {
  public:
    Impl_SceneGraph()
    {
      m_idGenerator.seed((unsigned int)time(0));
    }

    int64_t GenerateID()
    {
      uint32_t id[2] = { m_idGenerator(), m_idGenerator() };
      return abs(*(int64_t*)id);
    }

    void Traverse(Node* pNode, flIN Visitor<Node>* pNodeVisitor, flIN Visitor<Component>* pComponentVisitor)
    {
      if (pNode == nullptr)
      {
        return;
      }

      bool enterNode = pNodeVisitor == nullptr || pNodeVisitor->OnEnter(pNode);

      if (enterNode)
      {
        int64_t componentCount = pNode->GetComponentCount();

        Transform* pTransform = nullptr;

        for (int64_t componentIdx = 0; componentIdx < componentCount; ++componentIdx)
        {
          Component* pComponent = pNode->GetComponent(componentIdx);

          if (pComponentVisitor && pComponentVisitor->OnEnter(pComponent))
          {
            pComponentVisitor->OnLeave(pComponent);
          }

          if (pComponent->Is<Transform>())
          {
            pTransform = (Transform*)pComponent;
          }
        }

        if (pTransform)
        {
          int64_t childCount = pTransform->GetChildCount();
          for (int64_t childIdx = 0; childIdx < childCount; ++childIdx)
            Traverse(pTransform->GetChild(childIdx)->GetNode(), pNodeVisitor, pComponentVisitor);
        }

        if (pNodeVisitor != nullptr)
        {
          pNodeVisitor->OnLeave(pNode);
        }
      }
    }

    Ref<Node> m_root;

    ctHashMap<int64_t, Node*> m_nodes;

    std::default_random_engine m_idGenerator;
  };

  flPIMPL_IMPL(SceneGraph);

  SceneGraph::SceneGraph()
  {
    Impl()->m_root = MakeRef(AddNode("Root"), true);
  }

  Node* SceneGraph::AddNode(char const* name, flIN int64_t parentID)
  {
    int64_t nodeID = Impl()->GenerateID();

    while (!Impl()->m_nodes.TryAdd(nodeID, nullptr))
      nodeID = Impl()->GenerateID();

    Node* pNode = flNew Node(this, nodeID, name);
    pNode->AddComponent<Transform>();

    Impl()->m_nodes[nodeID] = pNode;

    // Set the nodes parent transform
    Node* pParent = Impl()->m_nodes.GetOr(parentID, nullptr);
    if (pParent)
      pNode->GetComponent<Transform>()->SetParent(pParent->GetComponent<Transform>());

    return pNode;
  }

  Node* SceneGraph::GetNode(flIN int64_t id)
  {
    return Impl()->m_nodes.GetOr(id, nullptr);
  }

  Node const* SceneGraph::GetNode(flIN int64_t id) const
  {
    return Impl()->m_nodes.GetOr(id, nullptr);
  }

  Node* SceneGraph::GetRootNode()
  {
    return Impl()->m_root.Get();
  }

  Node const* SceneGraph::GetRootNode() const
  {
    return Impl()->m_root.Get();
  }

  int64_t SceneGraph::GetNodeCount() const
  {
    return Impl()->m_nodes.Size();
  }

  void SceneGraph::RemoveNode(flIN int64_t id)
  {
    Node* pNode = GetNode(id);
    if (Impl()->m_nodes.Remove(id))
      pNode->DecRef();
  }

  void SceneGraph::GetNodeIDs(flOUT int64_t* pIDs) const
  {
    for (auto& kvp : Impl()->m_nodes)
      *(pIDs++) = kvp.m_key;
  }

  void SceneGraph::Visit(flIN Visitor<Node>* pNodeVisitor, flIN Visitor<Component>* pComponentVisitor)
  {
    for (auto& kvp : Impl()->m_nodes)
    {
      Node* pNode = kvp.m_val;

      bool enterNode = pNodeVisitor == nullptr || pNodeVisitor->OnEnter(pNode);

      if (enterNode)
      {
        int64_t componentCount = pNode->GetComponentCount();

        for (int64_t componentIdx = 0; componentIdx < componentCount; ++componentIdx)
        {
          Component* pComponent = pNode->GetComponent(componentIdx);

          if (pComponentVisitor && pComponentVisitor->OnEnter(pComponent))
          {
            pComponentVisitor->OnLeave(pComponent);
          }
        }

        if (pNodeVisitor != nullptr)
        {
          pNodeVisitor->OnLeave(pNode);
        }
      }
    }
  }

  void SceneGraph::Traverse(flIN Visitor<Node>* pNodeVisitor, flIN Visitor<Component>* pComponentVisitor, flIN int64_t id)
  {
    Impl()->Traverse(id == -1 ? GetRootNode() : GetNode(id), pNodeVisitor, pComponentVisitor);
  }
}
