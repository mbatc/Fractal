#pragma once

#include "flInterface.h"
#include "flMath.h"
#include "flColour.h"

namespace Fractal
{
  class Impl_SurfaceMaterial;

  class flEXPORT SurfaceMaterial : public Interface
  {
    flPIMPL_DEF(SurfaceMaterial);
  public:
    /**
     * @brief Create a SurfaceMaterial instance.
     */
    static SurfaceMaterial* Create();

    /**
     * @brief Get the name of the SurfaceMaterial.
     *
     * @return The SurfaceMaterial name as a c-string.
     */
    char const* GetName() const;

    /**
     * @brief Set the name of the SurfaceMaterial.
     *
     * @param [in] name The name to assign to the SurfaceMaterial.
     */
    void SetName(flIN char const* name);

    /**
     * @brief Get a material value by name.
     *
     * @param [in] name The name of the value.
     *
     * @return The material value.
     */
    float GetValue(flIN char const* name) const;

    /**
     * @brief Get a material value by index.
     *
     * @param [in] index The index of the value.
     *
     * @return The material value.
     */
    float GetValue(flIN int64_t index) const;

    /**
     * @brief Get a material colour by name.
     *
     * @param [in] name The name of the colour.
     *
     * @return The material colour.
     */
    Colour GetColour(flIN char const* name) const;

    /**
     * @brief Get a material colour by index.
     *
     * @param [in] index The index of the colour.
     *
     * @return The material colour.
     */
    Colour GetColour(flIN int64_t index) const;

    /**
     * @brief Get a material texture path by name.
     *
     * @param [in] name The name of the texture.
     *
     * @return The material texture's file path.
     */
    char const* GetTexture(flIN char const* name) const;

    /**
     * @brief Get a material texture path by index.
     *
     * @param [in] index The index of the texture.
     *
     * @return The texture's file path.
     */
    char const* GetTexture(flIN int64_t index) const;

    /**
     * @brief Set a material value by name.
     *
     * @param [in] name  The name of the value.
     * @param [in] value The value to be assigned.
     */
    void SetValue(flIN char const* name, flIN float value);

    /**
     * @brief Set a material value by index.
     *
     * @param [in] index The index of the value.
     * @param [in] value The value to be assigned.
     */
    void SetValue(flIN int64_t index, flIN float value);

    /**
     * @brief Set a material colour by name.
     *
     * @param [in] name   The name of the colour.
     * @param [in] colour The colour to be assigned.
     */
    void SetColour(flIN char const* name, flIN Colour colour);

    /**
     * @brief Set a material colour by index.
     *
     * @param [in] index  The name of the colour.
     * @param [in] colour The colour to be assigned.
     */
    void SetColour(flIN int64_t index, flIN Colour colour);

    /**
     * @brief Set a material texture path by name.
     *
     * @param [in] name The name of the texture.
     * @param [in] path The file path to be assigned.
     */
    void SetTexture(flIN char const* name, flIN char const* path);

    /**
     * @brief Set a material texture path by index.
     *
     * @param [in] index The index of the texture.
     * @param [in] path  The file path to be assigned.
     */
    void SetTexture(flIN int64_t index, flIN char const* path);

    /**
     * @brief Get the index of a material value.
     *
     * @param [in] name The name of the texture.
     *
     * @return The index of the texture.
     */
    int64_t FindValue(flIN char const* name) const;

    /**
     * @brief Get the index of a material value.
     *
     * @param [in] name The name of the texture.
     *
     * @return The index of the texture.
     */
    int64_t FindColour(flIN char const* name) const;

    /**
     * @brief Get the index of a material value.
     *
     * @param [in] name The name of the texture.
     *
     * @return The index of the texture.
     */
    int64_t FindTexture(flIN char const* name) const;

    /**
     * @brief Get the number of values in the material.
     *
     * @return The number of values.
     */
    int64_t GetValueCount() const;

    /**
     * @brief Get the number of colours in the material.
     *
     * @return The number of colours.
     */
    int64_t GetColourCount() const;

    /**
     * @brief Get the number of textures in the material.
     *
     * @return The number of textures.
     */
    int64_t GetTextureCount() const;

    /**
     * @brief Get the name of a Value at the specified index.
     *
     * @param [in] index The index of the Value.
     *
     * @return The Value name as a c-string.
     */
    char const* GetValueName(flIN int64_t index) const;

    /**
     * @brief Get the name of a Colour at the specified index.
     *
     * @param [in] index The index of the Value.
     *
     * @return The Colour name as a c-string.
     */
    char const* GetColourName(flIN int64_t index) const;

    /**
     * @brief Get the name of a Texture at the specified index.
     *
     * @param [in] index The index of the Value.
     *
     * @return The Texture name as a c-string.
     */
    char const* GetTextureName(flIN int64_t index) const;
  };

  /**
   * @brief A struct that contains string-ids of common SurfaceMaterial properties
   */
  struct flEXPORT MaterialProperty
  {
    /**
     * @brief Properties of a Phong shaded Material.
     */
    struct Phong
    {
      static char const* diffuse;
      static char const* ambient;
      static char const* specular;
      static char const* normal;
      static char const* alpha;
    };

    /**
     * @brief Properties of a PBR shaded Material.
     */
    struct PBR
    {
      static char const* albedo;
      static char const* emissive;
      static char const* roughness;
      static char const* metalness;
      static char const* alpha;
      static char const* ao;
      static char const* normal;
    };
  };
}
