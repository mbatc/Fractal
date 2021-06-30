#pragma once

#include "flInterface.h"
#include "math/flMath.h"

namespace flEngine
{
  class SurfaceMaterial;

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
    /**
     * @brief Create a Mesh instance
     */
    static Mesh * Create();

    /**
     * @brief Reset the mesh to it's default state.
     */
    void Clear();

    /**
     * @brief Get the source file path for the Mesh data.
     *
     * @return The source file path as a c-string.
     */
    char const * GetSourcePath();

    /**
     * @brief Get the directory that contains the Mesh data.
     * 
     * @return The source directory as a c-string.
     */
    char const * GetSourceDirectory();

    /**
     * @brief Set the source file path for the Mesh data.
     * 
     * @param [in] path The new source file path.
     */
    void SetSourcePath(flIN char const * path);

    /**
     * @brief Get the number of vertices the Mesh has.
     * 
     * @return The vertex count
     */
    int64_t GetVertexCount() const;

    /**
     * @brief Get a pointer to the meshes Vertex buffer.
     * 
     * @return A pointer to the first Vertex in the mesh.
     */
    Vertex * GetVertices();

    /**
     * @brief Get a pointer to the meshes Vertex buffer. (const)
     *
     * @return A pointer to the first Vertex in the mesh.
     */
    Vertex const * GetVertices() const;

    /**
     * @brief Get a Vertex by index.
     * 
     * @param [in]  index   The index of the vertex to retrieve.
     * @param [out] pVertex A pointer to a Vertex to write into.
     *
     * @return True if the index is valid. Otherwise, False.
     */
    bool GetVertex(flIN int64_t index, flOUT Vertex * pVertex) const;
    
    /**
     * @brief Set a Vertex by index.
     * 
     * @param [in] index    The index of the Vertex to set.
     * @param [in] position The new position to assign to the Vertex.
     * @param [in] normal   The new normal to assign to the Vertex.
     * @param [in] texcoord The new texcoord to assign to the Vertex.
     * @param [in] colour   The new colour to assign to the Vertex.
     * 
     * @return True if the index is valid. Otherwise, False.
     */
    bool SetVertex(flIN int64_t index, flIN Math::Vec3D position, flIN Math::Vec3D normal, flIN Math::Vec2D texcoord, flIN Math::Vec4D colour);

    /**
     * @brief Set a contiguous group of Vertices.
     * 
     * @param [in] index     The start index of the Vertices to set.
     * @param [in] pVertices A pointer to the vertex data to copy.
     * @param [in] count     The number of vertices to copy.
     *
     * @return True if the start index is valid and there is enough space for the new vertices. Otherwise, False.
     */
    bool SetVertices(flIN int64_t index, flIN Vertex const * pVertices, flIN int64_t count);

    /**
     * @brief Set the number of vertices in the Mesh.
     * 
     * @param [in] count The number of vertices to allocate.
     */
    void SetVertexCount(flIN int64_t count);

    /**
     * @brief Add a Vertex to the Mesh.
     * 
     * Adds a new vertex to the mesh. This vertex is appended to the back of the vertex buffer
     * and the index of the new Vertex is returned.
     * 
     * @param [in] position The position of the new Vertex.
     * @param [in] normal   The normal of the new Vertex.
     * @param [in] texcoord The texcoord of the new Vertex.
     * @param [in] colour   The colour of the new Vertex.
     * 
     * @return The index of the new vertex.
     */
    int64_t AddVertex(flIN Math::Vec3D position, flIN Math::Vec3D normal, flIN Math::Vec2D texcoord, flIN Math::Vec4D colour);

    /**
     * @brief Add multiple Vertices to the Mesh.
     * 
     * @param [in] pVertices A pointer to an array of vertices to add.
     * @param [in] count     The number of vertices to add.
     * 
     * @return The index of the first new Vertex added.
     */
    int64_t AddVertices(flIN Vertex const * pVertices, flIN int64_t count);

    /**
     * @brief Set the Vertices in the Mesh.
     * 
     * Set the vertices in the Mesh. This clears all previous mesh data.
     * The vertex data is copied from the source array into an internal buffer.
     * 
     * @param [in] pVertices A pointer to the new array of vertices.
     * @param [in] count     The number of vertices to copy.
     */
    void SetVertices(flIN Vertex const * pVertices, flIN int64_t count);

    /**
     * @brief Get the number of polygons in the Mesh.
     * 
     * @return The polygon count.
     */
    int64_t GetPolygonCount() const;

    /**
     * @brief Get the number of Vertices assigned to a polygon.
     *
     * @param [in] polyIndex The index of the Polygon to query.
     * 
     * @return The number of Vertex indices.
     */
    int64_t GetPolygonSize(flIN int64_t polyIndex) const;

    /**
     * @brief Get a pointer to a Polygons vertex indices.
     *
     * @param [in] polyIndex The index of the Polygon to query.
     * 
     * @return A pointer to the polygon's vertex indices.
     */
    int64_t * GetPolygonVertices(flIN int64_t polyIndex);

    /**
     * @brief Get a pointer to a Polygons vertex indices. (const)
     *
     * @param [in] polyIndex The index of the Polygon to query.
     * 
     * @return A pointer to the polygon's vertex indices.
     */
    int64_t const * GetPolygonVertices(flIN int64_t polyIndex) const;

    /**
     * @brief Get an index of a Vertex in a Polygon.
     *
     * @param [in] polyIndex The index of the Polygon to query.
     * @param [in] vertIndex The index of a vertex within the polygon, where 0 <= vertIndex < GetPolygonSize(polyIndex).
     * 
     * @return The index of the polygons vertex. This is an index into the Mesh's Vertex array.
     */
    int64_t GetPolygonVertex(flIN int64_t polyIndex, flIN int64_t vertIndex) const;

    /**
     * @brief Get the material index assigned to a Polygon.
     * 
     * @param [in] polyIndex The index of the Polygon to query.
     * 
     * @return The Material index. This is an index onto the Mesh's Material array.
     */
    int64_t GetPolygonMaterial(flIN int64_t polyIndex) const;

    /**
     * @brief Add an empty Polygon to the Mesh.
     * 
     * @return The index of the new Polygon.
     */
    int64_t AddPolygon();

    /**
     * @brief Add a Polygon with some initial data.
     * 
     * @param [in] pIndices    A pointer to the Polygon's index array.
     * @param [in] vertexCount The number of Vertex's in the index array.
     * @param [in] material    The index of the Material to assign to the Polygon.
     * 
     * @return The index of the new Polygon.
     */
    int64_t AddPolygon(flIN int64_t const * pIndices, flIN int64_t vertexCount, flIN int64_t material);

    /**
     * @brief Add a Vertex index to a Polygon.
     * 
     * @param [in] polyIndex The index of the polygon to add the vertex to.
     * @param [in] vertIndex The Vertex index to add.
     * 
     * @return The index of the new Vertex within the Polygon.
     */
    int64_t AddPolygonVertex(flIN int64_t polyIndex, flIN int64_t vertIndex);

    /**
     * @brief Set the Material index assigned to a Polygon.
     * 
     * @param [in] polyIndex The index of the Polygon to assign the Material index to.
     * @param [in] material  The index of the Material to assign to the Polygon.
     * 
     * @return True if polyIndex is valid. Otherwise, False.
     */
    bool SetPolygonMaterial(flIN int64_t polyIndex, flIN int64_t material);

    /**
     * @brief Set the number of Vertices assigned to a Polygon.
     * 
     * @param [in] polyIndex   The index of the Polygon to resize.
     * @param [in] vertexCount The number of Vertices to allocate.
     *
     * @return True if polyIndex is valid. Otherwise, False.
     */
    bool SetPolygonSize(flIN int64_t polyIndex, flIN int64_t vertexCount);

    /**
     * @brief Set the index of a Vertex in a Polygon.
     * 
     * @param [in] polyIndex The index of the Polygon to be modified.
     * @param [in] vertIndex The index of the Vertex within the Polygon.
     * @param [in] index     The index of the Vertex to assign to the Polygon.
     * 
     * @return True if polyIndex, and vertIndex, are valid. Otherwise, False.
     */
    bool SetPolygonVertex(flIN int64_t polyIndex, flIN int64_t vertIndex, flIN int64_t index);

    /**
     * @brief Set the indices assigned to a Polygon.
     * 
     * @param [in] polyIndex The index of the Polygon to be modified.
     * @param [in] pIndices  A pointer to the indices to assign to the Polygon.
     * @param [in] count     The number of indices in the buffer.
     * 
     * @return True if polyIndex is valid. Otherwise, false.
     */
    bool SetPolygonVertices(flIN int64_t polyIndex, flIN int64_t const * pIndices, flIN int64_t count);

    /**
     * @brief Add a new SurfaceMaterial to the Mesh.
     * 
     * @return The index of the new SurfaceMaterial in the Mesh.
     */
    int64_t AddMaterial();

    /**
     * @brief Add an existing SurfaceMaterial to the Mesh.
     * 
     * @return The index of the SurfaceMaterial in the Mesh.
     */
    int64_t AddMaterial(flIN SurfaceMaterial * pMaterial);

    /**
     * @brief Get the index of a Material in the Mesh by name.
     * 
     * @param [in] name The name of the Material as a c-string.
     * 
     * @return The index of the Material or -1 if it was not found.
     */
    int64_t FindMaterial(flIN char const * name) const;

    /**
     * @brief Get a SurfaceMaterial by its index.
     *
     * @param [in] materialIndex The index of the SurfaceMaterial to retrieve.
     *
     * @return A pointer to a SurfaceMaterial if it exists. Otherwise, null is returned.
     */
    SurfaceMaterial * GetMaterial(flIN int64_t materialIndex);

    /**
     * @brief Get a SurfaceMaterial by its index. (const)
     * 
     * @param [in] materialIndex The index of the SurfaceMaterial to retrieve.
     * 
     * @return A const pointer to a SurfaceMaterial if it exists. Otherwise, null is returned.
     */
    SurfaceMaterial const * GetMaterial(flIN int64_t materialIndex) const;

    /**
     * @brief Get the number of Materials in the Mesh.
     * 
     * @return The Material count.
     */
    int64_t GetMaterialCount() const;

    /**
     * @brief Triangulate the Mesh.
     * 
     * Ensures all Polygons only have 3 vertices (i.e. A triangle). Currently this
     * function only performs a basic triangle fan so convex polygons will produce
     * incorrect results.
     * 
     * @return The number of new polygons added. If 0 is returned the mesh is already Triangulated.
     */
    int64_t Triangulate();
  };
}
