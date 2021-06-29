#pragma once

#include "flInterface.h"
#include "math/flMath.h"

namespace flEngine
{
  class Impl_Mesh;

  struct Vertex
  {
    Math::Vec3D position;
    Math::Vec3D normal;
    Math::Vec2D texcoord;
    Math::Vec4D colour;
  };

  class flEXPORT Mesh : public Interface
  {
    flPIMPL_DEF(Mesh);
  public:
    static Mesh * Create();

    void Clear();

    int64_t GetVertexCount() const;

    Vertex * GetVertices();

    Vertex const * GetVertices() const;

    bool GetVertex(flIN int64_t index, flOUT Vertex * pVertex) const;

    bool SetVertex(flIN int64_t index, flIN Math::Vec3D position, flIN Math::Vec3D normal, flIN Math::Vec2D texcoord, flIN Math::Vec4D colour);

    bool SetVertices(flIN int64_t index, flIN Vertex const * pVertices, int64_t count);

    void SetVertexCount(flIN int64_t count);

    int64_t AddVertex(flIN Math::Vec3D position, flIN Math::Vec3D normal, flIN Math::Vec2D texcoord, flIN Math::Vec4D colour);

    int64_t AddVertices(flIN Vertex const * pVertices, flIN int64_t count);

    void SetVertices(flIN Vertex const * pVertices, flIN int64_t count);

    int64_t GetPolygonCount() const;

    int64_t GetPolygonSize(flIN int64_t polyIndex) const;

    int64_t * GetPolygonVertices(flIN int64_t polyIndex);

    int64_t const * GetPolygonVertices(flIN int64_t polyIndex) const;

    int64_t GetPolygonVertex(flIN int64_t polyIndex, flIN int64_t vertIndex) const;

    int64_t GetPolygonMaterial(flIN int64_t polyIndex) const;

    int64_t AddPolygon();

    int64_t AddPolygon(flIN int64_t const * pIndices, flIN int64_t vertexCount, flIN int64_t material);

    int64_t AddPolygonVertex(flIN int64_t polyIndex, flIN int64_t vertIndex);

    bool SetPolygonMaterial(flIN int64_t polyIndex, flIN int64_t material);

    bool SetPolygonSize(flIN int64_t polyIndex, flIN int64_t vertexCount);
    
    bool SetPolygonVertex(flIN int64_t polyIndex, flIN int64_t vertIndex, flIN int64_t index);

    bool SetPolygonVertices(flIN int64_t polyIndex, flIN int64_t const * pIndices, flIN int64_t count);
  };
}
