#include "flSceneImporter.h"
#include "flSceneManager.h"
#include "flSceneGraph.h"
#include "flComponent.h"
#include "flVisitor.h"

#include "ctFilename.h"
#include "ctHashMap.h"
#include "ctString.h"
#include "flSceneMeshImporter.h"

namespace Fractal
{
  class BehaviourVisitor : public Visitor<Component>
  {
  public:
    BehaviourVisitor(void (Component::* func)()) : m_method(func) {}

    virtual bool OnEnter(flIN Component* pComponent) override
    {
      (pComponent->*m_method)();
      return true;
    }

    void (Component::*m_method)(); // The method to invoke on the behavior
  };

  class Impl_SceneManager
  {
  public:
    Impl_SceneManager()
      : m_activeScene(MakeRef<SceneGraph>())
    {
      m_importers.Add("obj", MakeRef<SceneMeshImporter>().StaticCast<SceneImporter>());
    }

    Ref<SceneGraph> m_activeScene;

    ctHashMap<ctString, Ref<SceneImporter>> m_importers;
  };

  flPIMPL_IMPL(SceneManager);

  SceneGraph* SceneManager::ActiveScene()
  {
    return Impl()->m_activeScene.Get();
  }

  SceneGraph const* SceneManager::ActiveScene() const
  {
    return Impl()->m_activeScene.Get();
  }

  Node* SceneManager::Import(char const* filepath)
  {
    Node* pNode = ActiveScene()->AddNode();
    if (!Import(pNode, filepath))
    {
      ActiveScene()->RemoveNode(pNode->GetID());
      return nullptr;
    }

    return pNode;
  }

  bool SceneManager::Import(Node* pNode, char const* filepath)
  {
    ctFilename fullPath = ctString(filepath).to_lower();
    fullPath = fullPath.ResolveFullPath();

    Ref<SceneImporter> importer = Impl()->m_importers.GetOr(fullPath.Extension(), nullptr);

    if (importer == nullptr)
      return false;

    if (!importer->Import(pNode, fullPath.c_str(), nullptr))
      return false;

    return true;
  }

  bool SceneManager::OnStartup() { return true; }

  void SceneManager::OnShutdown() {}

  void SceneManager::OnUpdate()
  {
    BehaviourVisitor visitor(&Component::OnUpdate);
    Impl()->m_activeScene->Traverse(nullptr, &visitor);
  }

  void SceneManager::OnRender()
  {
    BehaviourVisitor visitor(&Component::OnRender);
    Impl()->m_activeScene->Traverse(nullptr, &visitor);
  }

  void SceneManager::OnPreUpdate()
  {
    BehaviourVisitor visitor(&Component::OnPreUpdate);
    Impl()->m_activeScene->Traverse(nullptr, &visitor);
  }

  void SceneManager::OnPreRender()
  {
    BehaviourVisitor visitor(&Component::OnPreRender);
    Impl()->m_activeScene->Traverse(nullptr, &visitor);
  }

  void SceneManager::OnPostUpdate()
  {
    BehaviourVisitor visitor(&Component::OnPostUpdate);
    Impl()->m_activeScene->Traverse(nullptr, &visitor);
  }

  void SceneManager::OnPostRender()
  {
    BehaviourVisitor visitor(&Component::OnPostRender);
    Impl()->m_activeScene->Traverse(nullptr, &visitor);
  }
}
