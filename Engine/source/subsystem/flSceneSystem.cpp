#include "subsystem/flSceneSystem.h"
#include "scene/flNodeBehaviour.h"
#include "scene/flSceneGraph.h"
#include "scene/flComponent.h"
#include "scene/flVisitor.h"

using namespace flEngine::Scene;

namespace flEngine
{
  class BehaviourVisitor : public Visitor<Component>
  {
  public:
    BehaviourVisitor(void (NodeBehaviour::* func)()) : m_method(func) {}

    virtual bool OnEnter(flIN Component* pComponent) override {
      NodeBehaviour* pBehaviour = pComponent->As<NodeBehaviour>();
      if (pBehaviour == nullptr)
        return false;

      (pBehaviour->*m_method)();
      return true;
    }

    void (NodeBehaviour::* m_method)(); // The method to invoke on the behavior
  };

  class Impl_SceneSystem
  {
  public:
    Impl_SceneSystem()
      : m_activeScene(flEngine::MakeRef<flEngine::Scene::SceneGraph>())
    {}

    Ref<SceneGraph> m_activeScene;
  };

  flPIMPL_IMPL(SceneSystem);

  bool SceneSystem::OnStartup() { return true; }

  void SceneSystem::OnShutdown() {}

  void SceneSystem::OnUpdate() {
    BehaviourVisitor visitor(&NodeBehaviour::OnUpdate);
    Impl()->m_activeScene->Visit(nullptr, &visitor);
  }

  void SceneSystem::OnRender() {
    BehaviourVisitor visitor(&NodeBehaviour::OnRender);
    Impl()->m_activeScene->Visit(nullptr, &visitor);
  }

  void SceneSystem::OnPreUpdate() {
    BehaviourVisitor visitor(&NodeBehaviour::OnPreUpdate);
    Impl()->m_activeScene->Visit(nullptr, &visitor);
  }

  void SceneSystem::OnPreRender() {
    BehaviourVisitor visitor(&NodeBehaviour::OnPreRender);
    Impl()->m_activeScene->Visit(nullptr, &visitor);
  }

  void SceneSystem::OnPostUpdate() {
    BehaviourVisitor visitor(&NodeBehaviour::OnPostUpdate);
    Impl()->m_activeScene->Visit(nullptr, &visitor);
  }

  void SceneSystem::OnPostRender() {
    BehaviourVisitor visitor(&NodeBehaviour::OnPostRender);
    Impl()->m_activeScene->Visit(nullptr, &visitor);
  }

  SceneGraph const * SceneSystem::ActiveScene() const {
    return Impl()->m_activeScene.Get();
  }

  SceneGraph * SceneSystem::ActiveScene() {
    return Impl()->m_activeScene.Get();
  }
}
