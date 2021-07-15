#include "flMesh.h"

extern "C" {
  static Fractal::IMesh* Fractal_CreateMesh()
  {
    return flNew Fractal::Impl::Mesh;
  }
}

namespace Fractal
{
  namespace Impl
  {
    void Mesh::Clear()
    {
      m_vertices.clear();
      m_polygons.clear();
    }

    char const* Mesh::GetSourcePath()
    {
      return m_sourcePath.c_str();
    }

    char const* Mesh::GetSourceDirectory()
    {
      return m_sourcePath.Directory().c_str();
    }

    void Mesh::SetSourcePath(flIN char const* path)
    {
      m_sourcePath = path;
    }

    int64_t Mesh::GetVertexCount() const
    {
      return m_vertices.size();
    }

    Vertex* Mesh::GetVertices()
    {
      return m_vertices.data();
    }

    Vertex const* Mesh::GetVertices() const
    {
      return m_vertices.data();
    }

    bool Mesh::GetVertex(flIN int64_t index, flOUT Vertex* pVertex) const
    {
      if (index < 0 || index >= GetVertexCount())
        return false;

      *pVertex = m_vertices[index];
      return true;
    }

    bool Mesh::SetVertex(flIN int64_t index, flIN Vec3D position, flIN Vec3D normal, flIN Vec2D texcoord, flIN Vec4D colour)
    {
      if (index < 0 || index >= GetVertexCount())
        return false;

      Vertex& vertex = m_vertices[index];
      vertex.position = position;
      vertex.normal = normal;
      vertex.texcoord = texcoord;
      vertex.colour = colour;
      return true;
    }

    bool Mesh::SetVertices(flIN int64_t index, flIN Vertex const* pVertices, flIN int64_t count)
    {
      if (index < 0 || index + count > GetVertexCount())
        return false;
      memcpy(m_vertices.data() + index, pVertices, count * sizeof(Vertex));
      return true;
    }

    void Mesh::SetVertexCount(flIN int64_t count)
    {
      m_vertices.resize(count);
    }

    int64_t Mesh::AddVertex(flIN Vec3D position, flIN Vec3D normal, flIN Vec2D texcoord, flIN Vec4D colour)
    {
      m_vertices.emplace_back();
      Vertex& vertex = m_vertices.back();
      vertex.position = position;
      vertex.normal = normal;
      vertex.texcoord = texcoord;
      vertex.colour = colour;
      return GetVertexCount() - 1;
    }

    int64_t Mesh::AddVertices(flIN Vertex const* pVertices, flIN int64_t count)
    {
      int64_t firstIndex = GetVertexCount();
      m_vertices.insert(m_vertices.size(), pVertices, pVertices + count);
      return firstIndex;
    }

    void Mesh::SetVertices(flIN Vertex const* pVertices, flIN int64_t count)
    {
      m_vertices.clear();
      AddVertices(pVertices, count);
    }

    int64_t Mesh::GetPolygonCount() const
    {
      return m_polygons.size();
    }

    int64_t Mesh::GetPolygonSize(flIN int64_t polyIndex) const
    {
      return polyIndex < 0 || polyIndex >= GetPolygonCount() ? 0 : m_polygons[polyIndex].indices.size();
    }

    int64_t* Mesh::GetPolygonVertices(flIN int64_t polyIndex)
    {
      return polyIndex < 0 || polyIndex >= GetPolygonCount() ? nullptr : m_polygons[polyIndex].indices.data();
    }

    int64_t const* Mesh::GetPolygonVertices(flIN int64_t polyIndex) const
    {
      return polyIndex < 0 || polyIndex >= GetPolygonCount() ? nullptr : m_polygons[polyIndex].indices.data();
    }

    int64_t Mesh::GetPolygonVertex(flIN int64_t polyIndex, flIN int64_t vertIndex) const
    {
      return polyIndex < 0 || polyIndex >= GetPolygonCount() ? -1 : m_polygons[polyIndex].indices[vertIndex];
    }

    int64_t Mesh::GetPolygonMaterial(flIN int64_t polyIndex) const
    {
      return polyIndex < 0 || polyIndex >= GetPolygonCount() ? -1 : m_polygons[polyIndex].material;
    }

    int64_t Mesh::AddPolygon()
    {
      m_polygons.emplace_back();
      return GetPolygonCount() - 1;
    }

    int64_t Mesh::AddPolygon(flIN int64_t const* pIndices, flIN int64_t vertexCount, flIN int64_t material)
    {
      m_polygons.emplace_back();
      SetPolygonVertices(GetPolygonCount() - 1, pIndices, vertexCount);
      SetPolygonMaterial(GetPolygonCount() - 1, material);
      return GetPolygonCount() - 1;
    }

    int64_t Mesh::AddPolygonVertex(flIN int64_t polyIndex, flIN int64_t vertIndex)
    {
      if (polyIndex < 0 || polyIndex >= GetPolygonCount())
        return false;

      Polygon& poly = m_polygons[polyIndex];
      poly.indices.push_back(vertIndex);
      return poly.indices.size() - 1;
    }

    bool Mesh::SetPolygonSize(flIN int64_t polyIndex, flIN int64_t vertexCount)
    {
      if (polyIndex < 0 || polyIndex >= GetPolygonCount())
        return false;

      Polygon& poly = m_polygons[polyIndex];
      poly.indices.resize(vertexCount, -1);
      return true;
    }

    bool Mesh::SetPolygonVertex(flIN int64_t polyIndex, flIN int64_t vertIndex, flIN int64_t index)
    {
      if (polyIndex < 0 || polyIndex >= GetPolygonCount())
        return false;

      Polygon& poly = m_polygons[polyIndex];

      if (vertIndex < 0 || vertIndex >= poly.indices.size())
        return false;

      poly.indices[vertIndex] = index;
      return true;
    }

    bool Mesh::SetPolygonVertices(flIN int64_t polyIndex, flIN int64_t const* pIndices, flIN int64_t count)
    {
      if (polyIndex < 0 || polyIndex >= GetPolygonCount())
        return false;

      Polygon& poly = m_polygons[polyIndex];
      poly.indices.clear();
      poly.indices.insert(0, pIndices, pIndices + count);
      return true;
    }

    bool Mesh::SetPolygonMaterial(flIN int64_t polyIndex, flIN int64_t material)
    {
      if (polyIndex < 0 || polyIndex >= GetPolygonCount())
        return false;

      Polygon& poly = m_polygons[polyIndex];
      poly.material = material;
      return true;
    }

    int64_t Mesh::AddMaterial()
    {
      m_materials.push_back(MakeRef(SurfaceMaterial::Create(), false));
      return GetMaterialCount() - 1;
    }

    int64_t Mesh::AddMaterial(flIN SurfaceMaterial* pMaterial)
    {
      m_materials.push_back(MakeRef(pMaterial, true));
      return GetMaterialCount() - 1;
    }

    int64_t Mesh::FindMaterial(flIN char const* name) const
    {
      int64_t i = 0;
      for (auto pMaterial : m_materials)
      {
        if (strcmp(pMaterial->GetName(), name))
        {
          return i;
        }
        ++i;
      }
      return -1;
    }

    SurfaceMaterial* Mesh::GetMaterial(flIN int64_t materialIndex)
    {
      return m_materials[materialIndex].Get();
    }

    SurfaceMaterial const* Mesh::GetMaterial(flIN int64_t materialIndex) const
    {
      return m_materials[materialIndex].Get();
    }

    int64_t Mesh::GetMaterialCount() const
    {
      return m_materials.size();
    }

    int64_t Mesh::Triangulate()
    {
      ctVector<Polygon> newPolygons;

      newPolygons.reserve(GetPolygonCount());

      for (Polygon& poly : m_polygons)
      {
        int64_t triCount = poly.indices.size() - 2;
        for (int64_t tri = 0; tri < triCount; ++tri)
        {
          Polygon newTri;
          newTri.material = poly.material;
          newTri.indices.push_back(poly.indices[0]);
          newTri.indices.push_back(poly.indices[tri + 1]);
          newTri.indices.push_back(poly.indices[tri + 2]);
          newPolygons.push_back(newTri);
        }
      }

      int64_t newTris = newPolygons.size() - m_polygons.size();
      m_polygons = newPolygons;
      return newTris;
    }
  }
}
