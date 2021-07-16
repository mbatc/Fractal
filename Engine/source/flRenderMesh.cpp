#include "flRenderMesh.h"
#include "flVertexArray.h"
#include "flVertexBuffer.h"
#include "flIndexBuffer.h"
#include "flHardwareBuffer.h"
#include "flAPI.h"
#include "flMesh.h"
#include "flRef.h"

namespace Fractal
{
  namespace Impl
  {
    RenderMesh::RenderMesh(flIN API* pAPI, flIN IMesh* pMesh)
      : m_pAPI(pAPI)
    {
      pVertexArray = MakeRef(pAPI->CreateVertexArray(), false);

      // Upload vertices
      Ref<VertexBuffer> pMeshVertices = MakeRef(pAPI->CreateVertexBuffer(sizeof(RenderVertex) * pMesh->GetVertexCount()), false);
      pMeshVertices->SetLayout(
        {
          { 0, Type_Float32, 3 }, // pos
          { 1, Type_Float32, 3 }, // nrm
          { 2, Type_Float32, 2 }, // uv
          { 3, Type_Float32, 4 }  // col
        }
      );

      Vertex* pVerticesD = pMesh->GetVertices();
      RenderVertex* pVertices = (RenderVertex*)pMeshVertices->GetBuffer()->Map(AccessFlag_ReadWrite);
      // Convert/copy vertices to the index buffer (from 64bit to 32bit floats)
      for (int64_t i = 0; i < pMesh->GetVertexCount(); ++i)
      {
        pVertices[i].position = pVerticesD[i].position;
        pVertices[i].texcoord = pVerticesD[i].texcoord;
        pVertices[i].normal = pVerticesD[i].normal;
        pVertices[i].colour = pVerticesD[i].colour;
      }
      pMeshVertices->GetBuffer()->Unmap();

      // Upload indices
      Ref<IndexBuffer>  pIndexBuffer = MakeRef(pAPI->CreateIndexBuffer(pMesh->GetPolygonCount() * 3), false);

      // Generate an index buffer that groups together different materials
      ctVector<ctVector<uint32_t>> subMeshIndices;
      subMeshIndices.resize(pMesh->GetMaterialCount());
      for (int64_t tri = 0; tri < pMesh->GetPolygonCount(); ++tri)
      {
        ctVector<uint32_t>& indices = subMeshIndices[pMesh->GetPolygonMaterial(tri)];
        for (int64_t vert = 0; vert < 3; ++vert)
        {
          indices.push_back((uint32_t)pMesh->GetPolygonVertex(tri, vert));
        }
      }

      uint32_t* pIndices = (uint32_t*)pIndexBuffer->GetBuffer()->Map(AccessFlag_Write);
      int64_t indexOffset = 0;
      for (ctVector<uint32_t>& indices : subMeshIndices)
      {
        // Copy indices to the index buffer
        memcpy(pIndices + indexOffset, indices.data(), indices.size() * sizeof(uint32_t));

        // Record submesh index range
        SubMesh subMesh;
        subMesh.offset = indexOffset;
        subMesh.count = indices.size();
        indexOffset += indices.size();
        // Add the submesh
        subMeshes.push_back(subMesh);
      }

      pIndexBuffer->GetBuffer()->Unmap();

      // Add buffers to the geometry
      pVertexArray->AddVertexBuffer(pMeshVertices);
      pVertexArray->SetIndexBuffer(pIndexBuffer);
    }

    int64_t RenderMesh::GetVertexCount() const
    {
      return pVertexArray->GetVertexCount();
    }

    int64_t RenderMesh::GetIndexCount() const
    {
      return pVertexArray->GetIndexCount();
    }

    Fractal::VertexArray const* RenderMesh::GetVertexArray() const
    {
      return pVertexArray;
    }

    Fractal::VertexArray* RenderMesh::GetVertexArray()
    {
      return pVertexArray;
    }

    int64_t RenderMesh::GetSubmeshCount() const
    {
      return subMeshes.size();
    }

    Fractal::IRenderMesh::SubMesh const* RenderMesh::GetSubmesh(flIN int64_t index) const
    {
      return &subMeshes[index];
    }

    API* RenderMesh::GetAPI() const
    {
      return m_pAPI;
    }

    Fractal::IRenderMesh::SubMesh* RenderMesh::GetSubmesh(flIN int64_t index)
    {
      return &subMeshes[index];
    }
  }
}

Fractal::IRenderMesh* Fractal_CreateRenderMesh(flIN Fractal::API* pAPI, flIN Fractal::IMesh* pMesh)
{
  return flNew Fractal::Impl::RenderMesh(pAPI, pMesh);
}