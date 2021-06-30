#pragma once

#include "flAPIResource.h"
#include "../math/flMath.h"

namespace flEngine
{
  class Mesh;

  namespace Graphics
  {
    class API;
    class VertexArray;

    class Impl_RenderMesh;

    struct RenderVertex
    {
      Math::Vec3F position;
      Math::Vec3F normal;
      Math::Vec2F texcoord;
      Math::Vec4F colour;
    };

    class flEXPORT RenderMesh : public APIResource
    {
      flPIMPL_DEF(RenderMesh);
    public:
      struct SubMesh
      {
        int64_t offset;
        int64_t count;
      };

      RenderMesh(flIN API *pAPI, flIN Mesh *pMesh);

      static RenderMesh * Create(flIN API *pAPI, flIN Mesh *pMesh);

      int64_t GetVertexCount() const;

      int64_t GetIndexCount() const;

      VertexArray * GetVertexArray();

      VertexArray const * GetVertexArray() const;

      int64_t GetSubmeshCount() const;
      
      SubMesh * GetSubmesh(flIN int64_t index);

      SubMesh const * GetSubmesh(flIN int64_t index) const;
    };
  }
}
