#pragma once

#include "flComponent.h"
#include "../graphics/flRenderMesh.h"

namespace flEngine
{
  namespace Graphics
  {
    class ShaderMaterial;
    class Program;
  }

  namespace Scene
  {
    class Impl_MeshRenderer;

    class flEXPORT MeshRenderer : public Component
    {
      flPIMPL_DEF(MeshRenderer);
    public:
      void SetMesh(Graphics::RenderMesh *pMesh);

      Graphics::RenderMesh * GetMesh();
      Graphics::RenderMesh const * GetMesh() const;

      int64_t GetSubMeshCount() const;

      Graphics::RenderMesh::SubMesh const * GetSubMesh(flIN int64_t subMesh) const;

      void SetShader(flIN int64_t subMesh, flIN Graphics::Program * pShader);
      void SetMaterial(flIN int64_t subMesh, flIN Graphics::ShaderMaterial * pMaterial);

      Graphics::Program * GetShader(flIN int64_t subMesh);
      Graphics::ShaderMaterial * GetMaterial(flIN int64_t subMesh);

      Graphics::Program const * GetShader(flIN int64_t subMesh) const;
      Graphics::ShaderMaterial const * GetMaterial(flIN int64_t subMesh) const;
    };
  }
}
