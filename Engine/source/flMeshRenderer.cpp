#include "flMeshRenderer.h"
#include "flShaderMaterial.h"
#include "flProgram.h"

#include "ctVector.h"

namespace Fractal
{
  class Impl_MeshRenderer
  {
  public:
    Ref<IRenderMesh> pRenderMesh;

    ctVector<Ref<Program>> shaders;
    ctVector<Ref<ShaderMaterial>> materials;
  };

  flPIMPL_IMPL(MeshRenderer);

  void MeshRenderer::SetMesh(IRenderMesh* pMesh)
  {
    Impl()->pRenderMesh = MakeRef(pMesh, true);

    Impl()->shaders.resize(pMesh->GetSubmeshCount());
    Impl()->materials.resize(pMesh->GetSubmeshCount());
  }

  IRenderMesh* MeshRenderer::GetMesh()
  {
    return Impl()->pRenderMesh;
  }

  IRenderMesh const* MeshRenderer::GetMesh() const
  {
    return Impl()->pRenderMesh;
  }

  int64_t MeshRenderer::GetSubMeshCount() const
  {
    return Impl()->pRenderMesh ? Impl()->pRenderMesh->GetSubmeshCount() : 0;
  }

  IRenderMesh::SubMesh const* MeshRenderer::GetSubMesh(flIN int64_t subMesh) const
  {
    return Impl()->pRenderMesh->GetSubmesh(subMesh);
  }

  void MeshRenderer::SetShader(flIN int64_t subMesh, flIN Program* pShader)
  {
    Impl()->shaders[subMesh] = MakeRef(pShader, true);
  }

  void MeshRenderer::SetMaterial(flIN int64_t subMesh, flIN ShaderMaterial* pMaterial)
  {
    Impl()->materials[subMesh] = MakeRef(pMaterial, true);
  }

  Program* MeshRenderer::GetShader(flIN int64_t subMesh)
  {
    return Impl()->shaders[subMesh];
  }

  ShaderMaterial* MeshRenderer::GetMaterial(flIN int64_t subMesh)
  {
    return Impl()->materials[subMesh];
  }

  Program const* MeshRenderer::GetShader(flIN int64_t subMesh) const
  {
    return Impl()->shaders[subMesh];
  }

  ShaderMaterial const* MeshRenderer::GetMaterial(flIN int64_t subMesh) const
  {
    return Impl()->materials[subMesh];
  }
}
