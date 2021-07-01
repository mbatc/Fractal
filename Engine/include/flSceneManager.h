#pragma once

#include "flModule.h"

namespace Fractal
{
  class SceneGraph;

  class Impl_SceneManager;

  class flEXPORT SceneManager : public Fractal::Module
  {
    flPIMPL_DEF(SceneManager);

  public:
    virtual bool OnStartup() override;
    virtual void OnShutdown() override;
    virtual void OnUpdate() override;
    virtual void OnRender() override;
    virtual void OnPreUpdate() override;
    virtual void OnPreRender() override;
    virtual void OnPostUpdate() override;
    virtual void OnPostRender() override;

    SceneGraph* ActiveScene();
    SceneGraph const* ActiveScene() const;
  };
}