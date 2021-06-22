#pragma once

#include "flSubSystem.h"

namespace flEngine
{
  namespace Scene {
    class SceneGraph;
  }

  class Impl_SceneSystem;

  class flEXPORT SceneSystem : public flEngine::SubSystem
  {
    flPIMPL_DEF(SceneSystem);

  public:
    virtual bool OnStartup() override;
    virtual void OnShutdown() override;
    virtual void OnUpdate() override;
    virtual void OnRender() override;
    virtual void OnPreUpdate() override;
    virtual void OnPreRender() override;
    virtual void OnPostUpdate() override;
    virtual void OnPostRender() override;

    Scene::SceneGraph * ActiveScene();
    Scene::SceneGraph const * ActiveScene() const;
  };
}