#include "flSceneRenderer.h"
#include "flSceneGraph.h"
#include "flComponent.h"
#include "flNode.h"
#include "flLog.h"

#include "flMeshRenderer.h"
#include "flCamera.h"
#include "flLight.h"

#include "ctVector.h"

namespace Fractal
{
  typedef void(*ComponentHandler)(SceneRenderer* pRenderer, Component* pComponent);

  class Impl_SceneRenderer
  {
  public:
    Impl_SceneRenderer()
    {
      AddHandler(Camera::TypeID(),       HandleCamera);
      AddHandler(MeshRenderer::TypeID(), HandleMesh);
      AddHandler(Light::TypeID(),        HandleLight);
    }

    void AddHandler(int64_t componentTypeID, ComponentHandler handler)
    {
      m_handler.resize(ComponentRegistry::ComponentCount(), nullptr);
      m_handler[componentTypeID] = handler;
      m_handlerLookup.clear(); // We need to rebuild the handler lookup
    }

    void Handle(Component* pComponent)
    {
      ComponentHandler handler = GetHandler(pComponent->GetTypeID());

      if (handler != nullptr)
        handler(m_pRenderer, pComponent);
    }

    ComponentHandler GetHandler(flIN int64_t typeID)
    {
      if (m_handlerLookup.empty())
      {
        for (int64_t id = 0; id < ComponentRegistry::ComponentCount(); ++id)
        {
          int64_t handlerType = id;
          while (handlerType != 0 && m_handler[handlerType] == nullptr)
            handlerType = ComponentRegistry::GetBaseTypeID(handlerType);
          m_handlerLookup[id] = handlerType;
        }
      }

      return m_handler[m_handlerLookup[typeID]];
    }

    static void HandleMesh(SceneRenderer* pRenderer, Component* pComponent)
    {
      MeshRenderer* pMesh = (MeshRenderer*)pComponent;

      Transform* pTransform = pMesh->GetNode()->GetTransform();

      if (pTransform)
      {
        // Mat4F mvp = m_projection * (Mat4F)pTransform->GetTransform();
        // pMesh->GetMesh()->GetVertexArray()->Bind();
        // for (int64_t subMesh = 0; subMesh < pMesh->GetSubMeshCount(); ++subMesh)
        // {
        //   Program*        pShader   = pMesh->GetShader(subMesh);
        //   ShaderMaterial* pMaterial = pMesh->GetMaterial(subMesh);
        //   pShader->SetMat4("mvp", mvp);
        //   pShader->Bind();
        //   pMaterial->Bind();
        //   RenderMesh::SubMesh const* pSubMesh  = pMesh->GetSubMesh(subMesh);
        //   m_pGraphics->Render(DrawMode_Triangles, true, pSubMesh->offset, pSubMesh->count);
        // }
      }
    }

    static void HandleLight(SceneRenderer* pRenderer, Component* pComponent)
    {
      Light* pLight = (Light*)pComponent;
    }

    static void HandleCamera(SceneRenderer* pRenderer, Component* pComponent)
    {
      Camera* pCamera = (Camera*)pComponent;
    }

    ctVector<int64_t>          m_handlerLookup; // Handler to use for each component type
    ctVector<ComponentHandler> m_handler;   // Handler functions

    SceneRenderer* m_pRenderer = nullptr;
  };

  flPIMPL_IMPL(SceneRenderer);

  SceneRenderer::SceneRenderer()
  {
    Impl()->m_pRenderer = this;
  }

  void SceneRenderer::Begin(flIN SceneGraph* pGraph)
  {
    if (pGraph == nullptr)
    {
      flWarning("Begin(...) failed: pGraph was nullptr");
      return;
    }
  }

  void SceneRenderer::Submit(flIN Node* pNode)
  {
    if (pNode == nullptr)
    {
      flWarning("Submit(...) failed: pNode was nullptr");
      return;
    }

    if (!pNode->IsActive() || !pNode->IsVisible())
      return; // Invisible or inactive. Don't render

    for (int64_t componentIndex = 0; componentIndex < pNode->GetComponentCount(); ++componentIndex)
      Submit(pNode->GetComponent(componentIndex));

    for (int64_t childIndex = 0; childIndex < pNode->GetChildCount(); ++childIndex)
      Submit(pNode->GetChild(childIndex));
  }

  void SceneRenderer::Submit(flIN Component* pComponent)
  {
    if (pComponent == nullptr)
    {
      flWarning("Submit(...) failed: pComponent was nullptr");
      return;
    }

    Impl()->Handle(pComponent);
  }

  void SceneRenderer::End()
  {

  }
}
