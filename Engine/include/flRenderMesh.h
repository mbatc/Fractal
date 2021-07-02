#pragma once

#include "flAPIResource.h"
#include "flMath.h"

namespace Fractal
{
  class Mesh;

  class API;
  class VertexArray;

  class Impl_RenderMesh;

  struct RenderVertex
  {
    Vec3F position;
    Vec3F normal;
    Vec2F texcoord;
    Vec4F colour;
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

    /**
     * @brief Construct a RenderMesh instance.
     *
     * @param [in] pAPI  The API to create the Mesh with.
     * @param [in] pMesh The Mesh to create the geometry from.
     */
    RenderMesh(flIN API* pAPI, flIN Mesh* pMesh);

    /**
     * @brief Create a RenderMesh instance.
     *
     * @param [in] pAPI  See constructor.
     * @param [in] pMesh See constructor.
     *
     * @return A pointer to a new RenderMesh instance.
     */
    static RenderMesh* Create(flIN API* pAPI, flIN Mesh* pMesh);

    /**
     * @brief The size of the RenderMesh's vertex buffer.
     *
     * @return The vertex count.
     */
    int64_t GetVertexCount() const;

    /**
     * @brief The size of the RenderMesh's index buffer.
     *
     * @return The index count.
     */
    int64_t GetIndexCount() const;

    /**
     * @brief Get the VertexArray that contains the RenderMesh geometry.
     *
     * @return A pointer to the VertexArray.
     */
    VertexArray* GetVertexArray();

    /**
     * @brief Get the VertexArray that contains the RenderMesh geometry. (const)
     *
     * @return A const pointer to the VertexArray.
     */
    VertexArray const* GetVertexArray() const;

    /**
     * @brief Get the number of sub-meshes in the RenderMesh.
     *
     * Each sub-mesh represents a Material slot in the Mesh the RenderMesh was created from.
     *
     * @return The sub-mesh count.
     */
    int64_t GetSubmeshCount() const;

    /**
     * @brief Get the details of a sub-mesh by index.
     *
     * @param [in] index The index of the sub-mesh.
     *
     * @return A pointer to the sub-mesh.
     */
    SubMesh* GetSubmesh(flIN int64_t index);

    /**
     * @brief Get the details of a sub-mesh by index. (const)
     *
     * @param [in] index The index of the sub-mesh.
     *
     * @return A const pointer to the sub-mesh.
     */
    SubMesh const* GetSubmesh(flIN int64_t index) const;
  };
}
