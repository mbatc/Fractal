#pragma once

#include "../flRef.h"
#include "../flInterface.h"
#include "flComponentRegistry.h"

#define FL_IMPLEMENT_COMPONENT(ClassName, TypeName, BaseClass)                                   \
public:                                                                                          \
static char const *  Type()   { return TypeName; }                                               \
static int64_t       TypeID() { static int64_t id = Component::GetNextTypeID(); return id; }     \
static int64_t       BaseID() { return BaseClass::TypeID(); }                                    \
virtual char const * GetType()   const override  { return ClassName::Type(); }                   \
virtual int64_t      GetTypeID() const override  { return ClassName::TypeID(); }                 \
private:                                                                                         \
static bool Register() {                                                                         \
  static bool done = false;                                                                      \
  static bool result = false;                                                                    \
  if (!done) {                                                                                   \
    result = flEngine::Scene::ComponentRegistry::Register<ClassName>();                          \
    done = true;                                                                                 \
  }                                                                                              \
  return result;                                                                                 \
}                                                                                                \
inline static bool __registered = ClassName::Register();                                         \

namespace flEngine
{
  namespace Scene
  {
    class Node;

    class Impl_Component;

    class flEXPORT Component : public Interface
    {
      friend Node;

      flPIMPL_DEF(Component);

    public:
      static char const * Type()   { return "Unknown"; }
      static int64_t      TypeID() { return 0; }

      virtual char const * GetType()   const = 0;
      virtual int64_t      GetTypeID() const = 0;

      bool Is(flIN int64_t typeID);

      template<typename T> Ref<T> As() {
        return Is(T::TypeID()) ? MakeRef((T *), true) : nullptr;
      }

      inline Ref<Node> GetNode() {
        return MakeRef(_GetNode(), true);
      }

    protected:
      static int64_t GetNextTypeID();

    private:
      void SetNode(Node * pParent);

      Node * _GetNode();
      Node const *_GetNode() const;
    };
  }
}
