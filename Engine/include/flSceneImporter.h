#pragma once

#include "flInterface.h"

namespace Fractal
{
  class Node;
  class SceneGraph;

  /**
   * @brief Base class for scene asset importers.
   */
  class flEXPORT SceneImporter : public Interface
  {
  public:
    /**
     * @brief Import a file.
     */
    virtual bool Import(Node* pNode, char const* filepath, void* pUserData) = 0;
  };
}
