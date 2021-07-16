#pragma once

#include "flIRenderMesh.h"
#include "flRef.h"

#include "ctVector.h"

namespace Fractal
{
  namespace Impl
  {
    class RenderMesh : public IRenderMesh
    {
      FRACTAL_DEFAULT_INTERFACE;

    public:
      RenderMesh(flIN API* pAPI, flIN IMesh* pMesh);

      virtual int64_t GetVertexCount() const override;

      virtual int64_t GetIndexCount() const override;

      virtual VertexArray* GetVertexArray() override;

      virtual VertexArray const* GetVertexArray() const override;

      virtual int64_t GetSubmeshCount() const override;

      virtual SubMesh* GetSubmesh(flIN int64_t index) override;

      virtual SubMesh const* GetSubmesh(flIN int64_t index) const override;

      virtual API* GetAPI() const override;

    private:
      API* m_pAPI;
      Ref<VertexArray> pVertexArray;
      ctVector<SubMesh> subMeshes;
    };
  }
}
