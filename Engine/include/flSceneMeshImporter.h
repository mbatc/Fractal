#pragma once

#include "flSceneImporter.h"

namespace Fractal
{
  class flEXPORT SceneMeshImporter : public SceneImporter
  {
  public:
    static SceneMeshImporter* Create();

    virtual bool Import(Node* pNode, char const* filepath, void* pUserData) override;
  };
}
