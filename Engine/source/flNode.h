#pragma once

#include "flINode.h"
#include "flTransform.h"
#include "flComponent.h"
#include "flSceneGraph.h"
#include "ctString.h"

namespace Fractal
{
  namespace Impl
  {
    class Node : public INode
    {
      FRACTAL_DEFAULT_INTERFACE

    public:
      Node(flIN SceneGraph* pScene, flIN int64_t id, flIN char const* name);

      virtual int64_t GetID() const override;

      virtual char const* GetName() const override;

      virtual void SetName(flIN char const* name) override;

      virtual bool IsVisible() const override;

      virtual void SetVisible(flIN bool visible) override;

      virtual bool IsActive() const override;

      virtual void SetActive(flIN bool active) override;

      virtual INode* GetParent() override;

      virtual INode const* GetParent() const override;

      virtual void SetParent(flIN INode* pParent) override;

      virtual INode* GetChild(flIN int64_t index) override;

      virtual INode const* GetChild(flIN int64_t index) const override;

      virtual int64_t GetChildCount() const override;

      virtual bool RemoveChild(flIN int64_t index) override;

      virtual int64_t GetComponentCount() const override;

      virtual Component* GetComponentByType(flIN int64_t typeID) override;

      virtual Component const* GetComponentByType(flIN int64_t typeID) const override;

      virtual  Component* GetComponentByType(flIN char const* typeName) override;

      virtual Component const* GetComponentByType(flIN char const* typeName) const override;

      virtual   Component* GetComponent(flIN int64_t index) override;

      virtual   Component const* GetComponent(flIN int64_t index) const override;

      virtual   Transform* GetTransform() override;

      virtual  Transform const* GetTransform() const override;

      virtual     int64_t FindComponent(flIN int64_t typeID) const override;

      virtual   int64_t FindComponent(flIN char const* typeName) const;

      virtual  bool RemoveComponent(flIN int64_t index) override;

      virtual  bool RemoveComponentByType(flIN int64_t typeID) override;

      virtual bool RemoveComponentByType(flIN char const* typeName) override;

      virtual  SceneGraph* GetScene() override;

      virtual  SceneGraph const* GetScene() const override;

    private:
      Component* AddComponent(flIN Component* pNewComponent);

      ctString name;

      int64_t id = -1;
      bool isVisible = true;
      bool isActive = true;

      ctVector<Ref<Component>> components;

      Transform* m_pTransform = nullptr;
      SceneGraph* m_pScene = nullptr;
    };
  }
}
