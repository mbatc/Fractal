#include "flMesh.h"
#include "ctVector.h"

namespace flEngine
{
  struct Polygon
  {
    int64_t material = -1;

    ctVector<int64_t> indices;
  };

  class Impl_Mesh
  {
  public:
    ctVector<Vertex> vertices;
    ctVector<Polygon> polygons;
  };

  flPIMPL_IMPL(Mesh);

  Mesh* Mesh::Create()
  {
    return flNew(Mesh);
  }

  void Mesh::Clear()
  {
    Impl()->vertices.clear();
    Impl()->polygons.clear();
  }

  int64_t Mesh::GetVertexCount() const
  {
    return Impl()->vertices.size();
  }

  Vertex* Mesh::GetVertices()
  {
    return Impl()->vertices.data();
  }

  Vertex const * Mesh::GetVertices() const
  {
    return Impl()->vertices.data();
  }

  bool Mesh::GetVertex(flIN int64_t index, flOUT Vertex * pVertex) const
  {
    if (index < 0 || index >= GetVertexCount())
      return false;

    *pVertex = Impl()->vertices[index];
    return true;
  }

  bool Mesh::SetVertex(flIN int64_t index, flIN Math::Vec3D position, flIN Math::Vec3D normal, flIN Math::Vec2D texcoord, flIN Math::Vec4D colour)
  {
    if (index < 0 || index >= GetVertexCount())
      return false;

    Vertex &vertex = Impl()->vertices[index];
    vertex.position = position;
    vertex.normal = normal;
    vertex.texcoord = texcoord;
    vertex.colour = colour;
    return true;
  }

  bool Mesh::SetVertices(flIN int64_t index, flIN Vertex const * pVertices, int64_t count)
  {
    if (index < 0 || index + count > GetVertexCount())
      return false;
    memcpy(Impl()->vertices.data() + index, pVertices, count * sizeof(Vertex));
    return true;
  }

  void Mesh::SetVertexCount(flIN int64_t count)
  {
    Impl()->vertices.resize(count);
  }

  int64_t Mesh::AddVertex(flIN Math::Vec3D position, flIN Math::Vec3D normal, flIN Math::Vec2D texcoord, flIN Math::Vec4D colour)
  {
    Impl()->vertices.emplace_back();
    Vertex& vertex = Impl()->vertices.back();
    vertex.position = position;
    vertex.normal = normal;
    vertex.texcoord = texcoord;
    vertex.colour = colour;
    return GetVertexCount() - 1;
  }

  int64_t Mesh::AddVertices(flIN Vertex const * pVertices, flIN int64_t count)
  {
    Impl()->vertices.insert(Impl()->vertices.size(), pVertices, pVertices + count);
    return GetVertexCount() - 1;
  }

  void Mesh::SetVertices(flIN Vertex const * pVertices, flIN int64_t count)
  {
    Impl()->vertices.clear();
    AddVertices(pVertices, count);
  }

  int64_t Mesh::GetPolygonCount() const
  {
    return Impl()->polygons.size();
  }

  int64_t Mesh::GetPolygonSize(flIN int64_t polyIndex) const
  {
    return polyIndex < 0 || polyIndex >= GetPolygonCount() ? 0 : Impl()->polygons[polyIndex].indices.size();
  }

  int64_t * Mesh::GetPolygonVertices(flIN int64_t polyIndex)
  {
    return polyIndex < 0 || polyIndex >= GetPolygonCount() ? nullptr : Impl()->polygons[polyIndex].indices.data();
  }

  int64_t const * Mesh::GetPolygonVertices(flIN int64_t polyIndex) const
  {
    return polyIndex < 0 || polyIndex >= GetPolygonCount() ? nullptr : Impl()->polygons[polyIndex].indices.data();
  }

  int64_t Mesh::GetPolygonVertex(flIN int64_t polyIndex, flIN int64_t vertIndex) const
  {
    return polyIndex < 0 || polyIndex >= GetPolygonCount() ? -1 : Impl()->polygons[polyIndex].indices[vertIndex];
  }

  int64_t Mesh::GetPolygonMaterial(flIN int64_t polyIndex) const
  {
    return polyIndex < 0 || polyIndex >= GetPolygonCount() ? -1 : Impl()->polygons[polyIndex].material;
  }
  
  int64_t Mesh::AddPolygon()
  {
    Impl()->polygons.emplace_back();
    return GetPolygonCount() - 1;
  }

  int64_t Mesh::AddPolygon(flIN int64_t const * pIndices, flIN int64_t vertexCount, flIN int64_t material)
  {
    Impl()->polygons.emplace_back();
    SetPolygonVertices(GetPolygonCount() - 1, pIndices, vertexCount);
    SetPolygonMaterial(GetPolygonCount() - 1, material);
    return GetPolygonCount() - 1;
  }

  int64_t Mesh::AddPolygonVertex(flIN int64_t polyIndex, flIN int64_t vertIndex)
  {
    if (polyIndex < 0 || polyIndex >= GetPolygonCount())
      return false;

    Polygon &poly = Impl()->polygons[polyIndex];
    poly.indices.push_back(vertIndex);
    return poly.indices.size();
  }

  bool Mesh::SetPolygonSize(flIN int64_t polyIndex, flIN int64_t vertexCount)
  {
    if (polyIndex < 0 || polyIndex >= GetPolygonCount())
      return false;

    Polygon& poly = Impl()->polygons[polyIndex];
    poly.indices.resize(vertexCount, -1);
    return true;
  }

  bool Mesh::SetPolygonVertex(flIN int64_t polyIndex, flIN int64_t vertIndex, flIN int64_t index)
  {
    if (polyIndex < 0 || polyIndex >= GetPolygonCount())
      return false;

    Polygon &poly = Impl()->polygons[polyIndex];

    if (vertIndex < 0 || vertIndex >= poly.indices.size())
      return false;

    poly.indices[vertIndex] = index;
    return true;
  }

  bool Mesh::SetPolygonVertices(flIN int64_t polyIndex, flIN int64_t const * pIndices, flIN int64_t count)
  {
    if (polyIndex < 0 || polyIndex >= GetPolygonCount())
      return false;

    Polygon &poly = Impl()->polygons[polyIndex];
    poly.indices.clear();
    poly.indices.insert(0, pIndices, pIndices + count);
    return true;
  }

  bool Mesh::SetPolygonMaterial(flIN int64_t polyIndex, flIN int64_t material)
  {
    if (polyIndex < 0 || polyIndex >= GetPolygonCount())
      return false;

    Polygon& poly = Impl()->polygons[polyIndex];
    poly.material = material;
    return true;
  }
}
