#include "modules/flSceneManager.h"
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

  class Impl_SceneManager
  {
  public:
    Impl_SceneManager()
      : m_activeScene(flEngine::MakeRef<flEngine::Scene::SceneGraph>())
    {}

    Ref<SceneGraph> m_activeScene;
  };

  flPIMPL_IMPL(SceneManager);

  bool SceneManager::OnStartup() { return true; }

  void SceneManager::OnShutdown() {}

  void SceneManager::OnUpdate() {
    BehaviourVisitor visitor(&NodeBehaviour::OnUpdate);
    Impl()->m_activeScene->Visit(nullptr, &visitor);
  }

  void SceneManager::OnRender() {
    BehaviourVisitor visitor(&NodeBehaviour::OnRender);
    Impl()->m_activeScene->Visit(nullptr, &visitor);
  }

  void SceneManager::OnPreUpdate() {
    BehaviourVisitor visitor(&NodeBehaviour::OnPreUpdate);
    Impl()->m_activeScene->Visit(nullptr, &visitor);
  }

  void SceneManager::OnPreRender() {
    BehaviourVisitor visitor(&NodeBehaviour::OnPreRender);
    Impl()->m_activeScene->Visit(nullptr, &visitor);
  }

  void SceneManager::OnPostUpdate() {
    BehaviourVisitor visitor(&NodeBehaviour::OnPostUpdate);
    Impl()->m_activeScene->Visit(nullptr, &visitor);
  }

  void SceneManager::OnPostRender() {
    BehaviourVisitor visitor(&NodeBehaviour::OnPostRender);
    Impl()->m_activeScene->Visit(nullptr, &visitor);
  }

  SceneGraph const * SceneManager::ActiveScene() const {
    return Impl()->m_activeScene.Get();
  }

  SceneGraph * SceneManager::ActiveScene() {
    return Impl()->m_activeScene.Get();
  }
}
