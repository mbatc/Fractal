#pragma once

#include "flConfig.h"

namespace Fractal
{
    /**
     * @brief The ComponentRegistry contains type information for the available components types.
     */
    class flEXPORT ComponentRegistry
    {
    public:
      /**
       * @brief Register a component type.
       * 
       * Register a component using a template type.
       */
      template<typename T>
      static inline bool Register() {
        return Register(T::Type(), T::TypeID(), T::BaseID());
      }

      /**
       * @brief Register a component type.
       */
      static bool Register(flIN char const * typeName, flIN int64_t typeID, flIN int64_t baseTypeID);

      /**
       * @brief Check the class relationship between two component types.
       */
      static bool IsBase(flIN int64_t baseID, flIN int64_t derivedID);

      /**
       * @brief Get the number of registered component types.
       */
      static int64_t ComponentCount();

      /**
       * @brief Get the string identifier of a component type using it's integer ID
       */
      static char const * GetComponentName(flIN int64_t typeID);

      /**
       * @brief Get the next available runtime ID for a Component type.
       */
      static int64_t NextTypeID();
    };
}