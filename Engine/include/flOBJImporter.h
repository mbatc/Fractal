#pragma once

#include "flInterface.h"

namespace Fractal
{
  class Impl_OBJImporter;

  class Mesh;

  class flEXPORT OBJImporter : public Interface
  {
    flPIMPL_DEF(OBJImporter);

  public:
    /**
     * @brief Import an OBJ file.
     * 
     * @param [in] filename The path to the file to import
     * 
     * @return True if the file is imported successfully. Otherwise, False.
     */
    bool Import(flIN char const * filename);

    /**
     * @brief Get the Mesh that was imported.
     * 
     * @return A pointer to the Mesh that was imported.
     */
    Mesh * GetResult();
  };
}
