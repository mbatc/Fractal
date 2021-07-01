#pragma once

namespace flEngine
{
  namespace Scene
  {
    class Node;
    class SceneGraph;

    /**
     * @brief Base class for scene asset importers.
     */
    class SceneImporter
    {
    public:
      /**
       * @brief Import a file.
       */
      virtual Node * Import(char const * filepath, SceneGraph *pScene) = 0;
    };
  }
}
