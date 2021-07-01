#pragma once

#include "flInterface.h"

namespace Fractal
{
  class SurfaceMaterial;

  class Impl_MTLImporter;

  class flEXPORT MTLImporter : public Interface
  {
    flPIMPL_DEF(MTLImporter);
  public:
    /**
     * @brief Create an MTLImporter instance.
     */
    static MTLImporter * Create();

    /**
     * @brief Import an MTL file.
     * 
     * @param [in] path The path to the MTL file to import.
     * 
     * @return True if the MTL file is imported successfully. Otherwise, False.
     */
    bool Import(flIN char const * path);

    /**
     * @brief Get the number of SurfaceMaterial's imported.
     * 
     * @return The number of SurfaceMaterial's imported
     */
    int64_t GetMaterialCount();

    /**
     * @brief Get an imported SurfaceMaterial by name.
     * 
     * @param [in] name The name of the SurfaceMaterial to retrieve.
     * 
     * @return A pointer to a SurfaceMaterial, or null if it could not be found.
     */
    SurfaceMaterial * GetMaterial(flIN char const *name);

    /**
     * @brief Get an imported SurfaceMaterial by index.
     *
     * @param [in] index The index of the SurfaceMaterial to retrieve.
     *
     * @return A pointer to a SurfaceMaterial if index is valid. Otherwise, null.
     */
    SurfaceMaterial * GetMaterial(flIN int64_t index);
  };
}
