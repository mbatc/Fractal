#pragma once

#include "flInterface.h"
#include "flNode.h"
#include "flVisitor.h"
#include <vector>

namespace Fractal
{
  class Impl_SceneGraph;

  class Node;

  class flEXPORT SceneGraph : public Interface
  {
    flPIMPL_DEF(SceneGraph);
  public:
    SceneGraph();

    /**
     * @brief Add a node to the scene.
     */
    Node* AddNode(char const* name = "Node", flIN int64_t parentID = -1);

    /**
     * @brief Get a node in the scene using its ID
     */
    Node* GetNode(flIN int64_t id);

    /**
     * @brief Get a node in the scene using its ID
     */
    Node const* GetNode(flIN int64_t id) const;

    /**
     * @brief Get the root node of the scene transform hierarchy
     */
    Node* GetRootNode();

    /**
     * @brief Get the root node of the scene transform hierarchy
     */
    Node const* GetRootNode() const;

    /**
     * @brief Get the number of IDs in the scene.
     */
    int64_t GetNodeCount() const;

    /**
     * @brief Remove a node from the scene by its ID.
     *
     * @param [in] id the ID of the node to be removed.
     */
    void RemoveNode(flIN int64_t id);

    /**
     * @brief Get the IDs of all the nodes in the scene.
     */
    void GetNodeIDs(flOUT int64_t* pIDs) const;

    /**
     * @brief Visit all the nodes in the scene.
     *
     * @param [in] pNodeVisitor      A visitor to handle Node's in the scene. Can be nullptr.
     * @param [in] pComponentVisitor A visitor to handle Component's in the scene. Can be nullptr.
     */
    void Visit(flIN Visitor<Node>* pNodeVisitor, flIN Visitor<Component>* pComponentVisitor);

    /**
     * @brief Traverse the transform hierarchy in the scene.
     *
     * @param [in] pNodeVisitor      A visitor to handle Node's in the scene. Can be nullptr.
     * @param [in] pComponentVisitor A visitor to handle Component's in the scene. Can be nullptr.
     * @param [in] id                The ID of the root node to traverse from.
     */
    void Traverse(flIN Visitor<Node>* pNodeVisitor, flIN Visitor<Component>* pComponentVisitor, flIN int64_t id = -1);

    inline std::vector<int64_t> GetNodeIDs() const
    {
      std::vector<int64_t> ids;
      ids.resize(GetNodeCount());
      GetNodeIDs(ids.data());
      return ids;
    }
  };
}