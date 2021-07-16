#pragma once

#include "flAPIResource.h"
#include "flMath.h"

namespace Fractal
{
  class IMesh;

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

  class flEXPORT IRenderMesh : public APIResource
  {
  public:
    struct SubMesh
    {
      int64_t offset;
      int64_t count;
    };

    /**
     * @brief The size of the RenderMesh's vertex buffer.
     *
     * @return The vertex count.
     */
    virtual int64_t GetVertexCount() const = 0;

    /**
     * @brief The size of the RenderMesh's index buffer.
     *
     * @return The index count.
     */
    virtual int64_t GetIndexCount() const = 0;

    /**
     * @brief Get the VertexArray that contains the RenderMesh geometry.
     *
     * @return A pointer to the VertexArray.
     */
    virtual VertexArray* GetVertexArray() = 0;

    /**
     * @brief Get the VertexArray that contains the RenderMesh geometry. (const)
     *
     * @return A const pointer to the VertexArray.
     */
    virtual VertexArray const* GetVertexArray() const = 0;

    /**
     * @brief Get the number of sub-meshes in the RenderMesh.
     *
     * Each sub-mesh represents a Material slot in the Mesh the RenderMesh was created from.
     *
     * @return The sub-mesh count.
     */
    virtual int64_t GetSubmeshCount() const = 0;

    /**
     * @brief Get the details of a sub-mesh by index.
     *
     * @param [in] index The index of the sub-mesh.
     *
     * @return A pointer to the sub-mesh.
     */
    virtual SubMesh* GetSubmesh(flIN int64_t index) = 0;

    /**
     * @brief Get the details of a sub-mesh by index. (const)
     *
     * @param [in] index The index of the sub-mesh.
     *
     * @return A const pointer to the sub-mesh.
     */
    virtual SubMesh const* GetSubmesh(flIN int64_t index) const = 0;
  };
}

extern "C" {
  /**
   * @brief Create a RenderMesh instance.
   *
   * @param [in] pAPI  See constructor.
   * @param [in] pMesh See constructor.
   *
   * @return A pointer to a new RenderMesh instance.
   */
  flEXPORT Fractal::IRenderMesh* flCCONV Fractal_CreateRenderMesh(flIN Fractal::API* pAPI, flIN Fractal::IMesh* pMesh);
}