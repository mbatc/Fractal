#pragma once

#include "flEngine.h"

class SceneSystem : public flEngine::SubSystem
{
public:
  SceneSystem()
    : m_scene(flEngine::MakeRef<flEngine::Scene::SceneGraph>())
  {}

  flEngine::Ref<flEngine::Scene::SceneGraph> ActiveScene() const {
    return m_scene;
  }

  class BehaviourVisitor : public flEngine::Scene::Visitor<flEngine::Scene::Component>
  {
  public:
    BehaviourVisitor(void (flEngine::Scene::NodeBehaviour::*func)()) : m_method(func) {}

    virtual bool OnEnter(flIN flEngine::Scene::Component* pComponent) override {
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
    BehaviourVisitor visitor(&flEngine::Scene::NodeBehaviour::OnUpdate);
    m_scene->Visit(nullptr, &visitor);
  }

  virtual void OnRender() override {
    BehaviourVisitor visitor(&flEngine::Scene::NodeBehaviour::OnRender);
    m_scene->Visit(nullptr, &visitor);
  }

  virtual void OnPreUpdate() override {
    BehaviourVisitor visitor(&flEngine::Scene::NodeBehaviour::OnPreUpdate);
    m_scene->Visit(nullptr, &visitor);
  }

  virtual void OnPreRender() override {
    BehaviourVisitor visitor(&flEngine::Scene::NodeBehaviour::OnPreRender);
    m_scene->Visit(nullptr, &visitor);
  }

  virtual void OnPostUpdate() override {
    BehaviourVisitor visitor(&flEngine::Scene::NodeBehaviour::OnPostUpdate);
    m_scene->Visit(nullptr, &visitor);
  }

  virtual void OnPostRender() override {
    BehaviourVisitor visitor(&flEngine::Scene::NodeBehaviour::OnPostRender);
    m_scene->Visit(nullptr, &visitor);
  }

private:
  flEngine::Ref<flEngine::Scene::SceneGraph> m_scene;
};
