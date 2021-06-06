#pragma once

#include "../flConfig.h"

namespace flEngine
{
  namespace Scene
  {
    class flEXPORT ComponentRegistry
    {
    public:
      template<typename T>
      static inline bool Register() { return Register(T::Type(), T::TypeID(), T::BaseID()); }

      static bool Register(flIN char const * typeName, flIN int64_t typeID, flIN int64_t baseTypeID);

      static bool IsBase(flIN int64_t baseID, flIN int64_t derivedID);

      static int64_t ComponentCount();

      static char const * GetComponentName(flIN int64_t typeID);
    };
  }
}