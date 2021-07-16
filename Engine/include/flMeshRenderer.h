#pragma once

#include "flComponent.h"
#include "flRenderMesh.h"

namespace Fractal
{
  class ShaderMaterial;
  class Program;

  class Impl_MeshRenderer;

  class flEXPORT MeshRenderer : public Component
  {
    FL_IMPLEMENT_COMPONENT(MeshRenderer, "MeshRenderer", Component);
    flPIMPL_DEF(MeshRenderer);
  public:
    void SetMesh(IRenderMesh* pMesh);

    IRenderMesh* GetMesh();
    IRenderMesh const* GetMesh() const;

    int64_t GetSubMeshCount() const;

    IRenderMesh::SubMesh const* GetSubMesh(flIN int64_t subMesh) const;

    void SetShader(flIN int64_t subMesh, flIN Program* pShader);
    void SetMaterial(flIN int64_t subMesh, flIN ShaderMaterial* pMaterial);

    Program* GetShader(flIN int64_t subMesh);
    ShaderMaterial* GetMaterial(flIN int64_t subMesh);

    Program const* GetShader(flIN int64_t subMesh) const;
    ShaderMaterial const* GetMaterial(flIN int64_t subMesh) const;
  };
}
