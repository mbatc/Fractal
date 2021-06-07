#pragma once

#include "flEngine.h"

class SceneSystem : public flEngine::SubSystem
{
public:
  SceneSystem()
    : m_scene(flEngine::MakeRef<flEngine::Scene::Scene>())
  {}

  flEngine::Ref<flEngine::Scene::Scene> ActiveScene() const {
    return m_scene;
  }

  class BehaviourVisitor : public flEngine::Scene::Visitor
  {
  public:
    BehaviourVisitor(void (flEngine::Scene::NodeBehaviour::*func)()) : m_method(func) {}

    virtual bool OnEnterComponent(flIN flEngine::Scene::Component* pComponent) override {
      flEngine::Scene::NodeBehaviour * pBehaviour = pComponent->As<flEngine::Scene::NodeBehaviour>();
      if (pBehaviour == nullptr)
        return false;

      (pBehaviour->*m_method)();
      return true;
    }

    void (flEngine::Scene::NodeBehaviour::*m_method)(); // The method to invoke on the behavior
  };

  virtual bool OnStartup() override {
    return true;
  }

  virtual void OnShutdown() override {
  }

  virtual void OnUpdate() override {
    BehaviourVisitor(&flEngine::Scene::NodeBehaviour::OnUpdate).VisitNode(m_scene->GetRootNode());
  }

  virtual void OnRender() override {
    BehaviourVisitor(&flEngine::Scene::NodeBehaviour::OnRender).VisitNode(m_scene->GetRootNode());
  }

  virtual void OnPreUpdate() override {
    BehaviourVisitor(&flEngine::Scene::NodeBehaviour::OnPreUpdate).VisitNode(m_scene->GetRootNode());
  }

  virtual void OnPreRender() override {
    BehaviourVisitor(&flEngine::Scene::NodeBehaviour::OnPreRender).VisitNode(m_scene->GetRootNode());
  }

  virtual void OnPostUpdate() override {
    BehaviourVisitor(&flEngine::Scene::NodeBehaviour::OnPostUpdate).VisitNode(m_scene->GetRootNode());
  }

  virtual void OnPostRender() override {
    BehaviourVisitor(&flEngine::Scene::NodeBehaviour::OnPostRender).VisitNode(m_scene->GetRootNode());
  }

private:
  flEngine::Ref<flEngine::Scene::Scene> m_scene;
};
