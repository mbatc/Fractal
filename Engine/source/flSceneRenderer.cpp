#include "flSceneRenderer.h"
#include "flSceneGraph.h"
#include "flComponent.h"
#include "flNode.h"
#include "flLog.h"

#include "flShaderMaterial.h"
#include "flVertexArray.h"
#include "flProgram.h"

#include "flApplication.h"
#include "flAPI.h"

#include "flMeshRenderer.h"
#include "flTransform.h"
#include "flCamera.h"
#include "flLight.h"

#include "ctVector.h"

namespace Fractal
{
  typedef void(*ComponentHandler)(SceneRenderer* pRenderer, Component* pComponent);

  class Impl_SceneRenderer
  {
  public:
    struct RenderJob
    {
      Mat4D modelMat;

      int64_t elementOffset = 0;
      int64_t elementCount  = 0;

      Ref<VertexArray>    pVertexArray;

      Ref<Program>        pShader;
      Ref<ShaderMaterial> pMaterial;
    };

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
        m_handlerLookup.resize(ComponentRegistry::ComponentCount());
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
        RenderJob job;
        job.modelMat     = pTransform->GetTransform();
        job.pVertexArray = MakeRef(pMesh->GetMesh()->GetVertexArray(), true);

        for (int64_t subMesh = 0; subMesh < pMesh->GetSubMeshCount(); ++subMesh)
        {
          Program*        pShader   = pMesh->GetShader(subMesh);
          ShaderMaterial* pMaterial = pMesh->GetMaterial(subMesh);
          RenderMesh::SubMesh const* pSubMesh = pMesh->GetSubMesh(subMesh);

          job.pShader       = MakeRef(pShader, true);
          job.pMaterial     = MakeRef(pMaterial, true);
          job.elementOffset = pSubMesh->offset;
          job.elementCount  = pSubMesh->count;

          pRenderer->Impl()->m_renderQueue.push_back(job);
        }
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

    ctVector<RenderJob>        m_renderQueue;
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

  void SceneRenderer::End() {}

  void SceneRenderer::Draw(flIN Mat4D viewMatrix, flIN Mat4D projMat)
  {
    VertexArray    *pActiveVertexArray = nullptr;
    Program        *pActiveProgram     = nullptr;
    ShaderMaterial *pActiveMaterial    = nullptr;

    API *pGraphics = GetGraphicsAPI();

    for (auto &job : Impl()->m_renderQueue)
    {
      if (job.pVertexArray != pActiveVertexArray)
      {
        pActiveVertexArray = job.pVertexArray;
        pActiveVertexArray->Bind();
      }

      if (job.pShader != pActiveProgram)
      {
        pActiveProgram = job.pShader;
        pActiveProgram->Bind();
      }

      if (job.pMaterial != pActiveMaterial)
      {
        pActiveMaterial = job.pMaterial;
        pActiveMaterial->Bind();
      }

      pActiveProgram->SetMat4("mvp", projMat * viewMatrix * job.modelMat);
      pGraphics->Render(DrawMode_Triangles, pActiveVertexArray->GetIndexBuffer() != nullptr, job.elementOffset, job.elementCount);
    }
  }
}
