#pragma once

#include "../flInterface.h"

#define FL_IMPLEMENT_COMPONENT(ClassName, TypeName) \
static char const *  Type()   { return TypeName; } \
static int64_t       TypeID() { static int64_t id = Component::GetNextTypeID(); return id; } \
virtual char const * GetType()   const override  { return ClassName::Type(); } \
virtual int64_t      GetTypeID() const override  { return ClassName::TypeID(); } \

namespace flEngine
{
  namespace Scene
  {
    class flEXPORT Component : public Interface
    {
    public:
      static char const* Type()   { return "Unknown"; }
      static int64_t     TypeID() { return -1; }

      virtual char const * GetType()   const = 0;
      virtual int64_t      GetTypeID() const = 0;

    protected:
      static int64_t GetNextTypeID();
    };
  }
}
