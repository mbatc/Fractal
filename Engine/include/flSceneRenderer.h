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

/*
SceneRenderer renderer;

renderer.Clear();
renderer.Begin(pScene);           // Begin rendering from a scene
renderer.Submit(pSomeRandomNode); // Submit a node from the scene
renderer.End();                   // Finished drawing from this scene

// Actually do the render - sends GPU commands
renderer.Draw(viewMatrix, projectionMatrix);

*/