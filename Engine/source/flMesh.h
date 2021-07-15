#pragma once

#include "flIMesh.h"
#include "flIImage.h"
#include "flSurfaceMaterial.h"
#include "flRef.h"
#include "ctFilename.h"

namespace Fractal
{
  namespace Impl
  {
    struct Polygon
    {
      int64_t material = -1;

      ctVector<int64_t> indices;
    };

    class Mesh : public IMesh
    {
      FRACTAL_DEFAULT_INTERFACE;

    public:
      virtual void Clear() override;

      virtual char const* GetSourcePath() override;

      virtual char const* GetSourceDirectory() override;

      virtual void SetSourcePath(flIN char const* path) override;

      virtual int64_t GetVertexCount() const override;

      virtual Vertex* GetVertices() override;

      virtual Vertex const* GetVertices() const override;

      virtual bool GetVertex(flIN int64_t index, flOUT Vertex* pVertex) const override;

      virtual bool SetVertex(flIN int64_t index, flIN Vec3D position, flIN Vec3D normal, flIN Vec2D texcoord, flIN Vec4D colour) override;

      virtual bool SetVertices(flIN int64_t index, flIN Vertex const* pVertices, flIN int64_t count) override;

      virtual void SetVertexCount(flIN int64_t count) override;

      virtual int64_t AddVertex(flIN Vec3D position, flIN Vec3D normal, flIN Vec2D texcoord, flIN Vec4D colour) override;

      virtual int64_t AddVertices(flIN Vertex const* pVertices, flIN int64_t count) override;

      virtual void SetVertices(flIN Vertex const* pVertices, flIN int64_t count) override;

      virtual int64_t GetPolygonCount() const override;

      virtual int64_t GetPolygonSize(flIN int64_t polyIndex) const override;

      virtual int64_t* GetPolygonVertices(flIN int64_t polyIndex) override;

      virtual int64_t const* GetPolygonVertices(flIN int64_t polyIndex) const override;

      virtual int64_t GetPolygonVertex(flIN int64_t polyIndex, flIN int64_t vertIndex) const override;

      virtual int64_t GetPolygonMaterial(flIN int64_t polyIndex) const override;

      virtual int64_t AddPolygon() override;

      virtual int64_t AddPolygon(flIN int64_t const* pIndices, flIN int64_t vertexCount, flIN int64_t material) override;

      virtual int64_t AddPolygonVertex(flIN int64_t polyIndex, flIN int64_t vertIndex) override;

      virtual bool SetPolygonSize(flIN int64_t polyIndex, flIN int64_t vertexCount) override;

      virtual bool SetPolygonVertex(flIN int64_t polyIndex, flIN int64_t vertIndex, flIN int64_t index) override;
      
      virtual bool SetPolygonVertices(flIN int64_t polyIndex, flIN int64_t const* pIndices, flIN int64_t count) override;

      virtual bool SetPolygonMaterial(flIN int64_t polyIndex, flIN int64_t material) override;

      virtual int64_t AddMaterial() override;

      virtual int64_t AddMaterial(flIN SurfaceMaterial* pMaterial) override;

      virtual int64_t FindMaterial(flIN char const* name) const override;

      virtual SurfaceMaterial* GetMaterial(flIN int64_t materialIndex) override;

      virtual SurfaceMaterial const* GetMaterial(flIN int64_t materialIndex) const override;

      virtual int64_t GetMaterialCount() const override;

      virtual int64_t Triangulate() override;

    private:
      ctFilename m_sourcePath;

      ctVector<Vertex> m_vertices;
      ctVector<Polygon> m_polygons;
      ctVector<Ref<SurfaceMaterial>> m_materials;
    };
  }
}