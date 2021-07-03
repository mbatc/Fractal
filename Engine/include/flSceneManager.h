#pragma once

#include "flModule.h"

namespace Fractal
{
  class SceneGraph;
  class Node;

  class Impl_SceneManager;

  class flEXPORT SceneManager : public Fractal::Module
  {
    flPIMPL_DEF(SceneManager);

  public:
    /**
     * @brief Get the active scene.
     */
    SceneGraph* ActiveScene();

    /**
     * @brief Get the active scene. (const)
     */
    SceneGraph const* ActiveScene() const;

    /**
     * @brief Import a file into the active scene.
     */
    Node* Import(char const* filepath);

    /**
     * @brief Import a file into an existing node.
     */
    bool Import(Node* pNode, char const* filepath);

    // Module event functions
    virtual bool OnStartup() override;
    virtual void OnShutdown() override;
    virtual void OnUpdate() override;
    virtual void OnRender() override;
    virtual void OnPreUpdate() override;
    virtual void OnPreRender() override;
    virtual void OnPostUpdate() override;
    virtual void OnPostRender() override;
  };
}