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
     * @param [in] name The name of the Material value.
     *
     * @return The material value.
     */
    float GetValue(flIN char const* name) const;

    /**
     * @brief Get a material colour by name.
     *
     * @param [in] name The name of the Material colour.
     *
     * @return The material colour.
     */
    Colour GetColour(flIN char const* name) const;

    /**
     * @brief Get a material texture path by name.
     *
     * @param [in] name The name of the Material texture.
     *
     * @return The material texture's file path.
     */
    char const* GetTexture(flIN char const* name) const;

    /**
     * @brief Set a material value by name.
     *
     * @param [in] name  The name of the Material value.
     * @param [in] value The value to be assigned.
     */
    void SetValue(flIN char const* name, flIN float value);

    /**
     * @brief Set a material colour by name.
     *
     * @param [in] name   The name of the Material colour.
     * @param [in] colour The colour to be assigned.
     */
    void SetColour(flIN char const* name, flIN Colour colour);

    /**
     * @brief Set a material texture path by name.
     *
     * @param [in] name The name of the Material texture.
     * @param [in] path The file path to be assigned.
     */
    void SetTexture(flIN char const* name, flIN char const* path);

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
  };
}
