#pragma once

#include "flInterface.h"
#include "flMath.h"

namespace Fractal
{
  class SceneGraph;
  class Component;
  class Node;

  class Impl_SceneRenderer;

  class flEXPORT SceneRenderer : public Interface
  {
    flPIMPL_DEF(SceneRenderer);

  public:
    SceneRenderer();

    void Begin(flIN SceneGraph* pScene);
    void Submit(flIN Node* pNode);
    void Submit(flIN Component* pComponent);
    void End();

    void Clear();

    void Draw(flIN Mat4D viewMatrix, flIN Mat4D projMat);
  };
}
