#include "scene/flMeshRenderer.h"
#include "graphics/flShaderMaterial.h"
#include "graphics/flProgram.h"

#include "ctVector.h"

using namespace flEngine::Graphics;

namespace flEngine
{
  namespace Scene
  {
    class Impl_MeshRenderer
    {
    public:
      Ref<RenderMesh> pRenderMesh;

      ctVector<Ref<Program>> shaders;
      ctVector<Ref<ShaderMaterial>> materials;
    };

    flPIMPL_IMPL(MeshRenderer);

    void MeshRenderer::SetMesh(Graphics::RenderMesh * pMesh)
    {
      Impl()->pRenderMesh = MakeRef(pMesh, true);

      Impl()->shaders.resize(pMesh->GetSubmeshCount());
      Impl()->materials.resize(pMesh->GetSubmeshCount());
    }

    Graphics::RenderMesh * MeshRenderer::GetMesh()
    {
      return Impl()->pRenderMesh;
    }

    Graphics::RenderMesh const *MeshRenderer::GetMesh() const
    {
      return Impl()->pRenderMesh;
    }

    int64_t MeshRenderer::GetSubMeshCount() const
    {
      return Impl()->pRenderMesh ? Impl()->pRenderMesh->GetSubmeshCount() : 0;
    }

    Graphics::RenderMesh::SubMesh const * MeshRenderer::GetSubMesh(flIN int64_t subMesh) const
    {
      return Impl()->pRenderMesh->GetSubmesh(subMesh);
    }

    void MeshRenderer::SetShader(flIN int64_t subMesh, flIN Graphics::Program * pShader)
    {
      Impl()->shaders[subMesh] = MakeRef(pShader, true);
    }

    void MeshRenderer::SetMaterial(flIN int64_t subMesh, flIN Graphics::ShaderMaterial * pMaterial)
    {
      Impl()->materials[subMesh] = MakeRef(pMaterial, true);
    }

    Graphics::Program *MeshRenderer::GetShader(flIN int64_t subMesh)
    {
      return Impl()->shaders[subMesh];
    }

    Graphics::ShaderMaterial *MeshRenderer::GetMaterial(flIN int64_t subMesh)
    {
      return Impl()->materials[subMesh];
    }

    Graphics::Program const * MeshRenderer::GetShader(flIN int64_t subMesh) const
    {
      return Impl()->shaders[subMesh];
    }

    Graphics::ShaderMaterial const * MeshRenderer::GetMaterial(flIN int64_t subMesh) const
    {
      return Impl()->materials[subMesh];
    }
  }
}
