#pragma once

#include "flRef.h"
#include "flInterface.h"
#include "flComponentRegistry.h"

/**
 * @brief This define is used to implement a new component type.
 *
 * This define implements the necessary functions for a component.
 */
#define FL_IMPLEMENT_COMPONENT(ClassName, TypeName, BaseClass)                               \
public:                                                                                      \
static char const *  Type()   { return TypeName; }                                           \
static int64_t       TypeID() { static int64_t id = Component::GetNextTypeID(); return id; } \
static int64_t       BaseID() { return BaseClass::TypeID(); }                                \
virtual char const * GetType()   const override  { return ClassName::Type(); }               \
virtual int64_t      GetTypeID() const override  { return ClassName::TypeID(); }             \
static bool Register() {                                                                     \
  static bool done = false;                                                                  \
  static bool result = false;                                                                \
  if (!done) {                                                                               \
    result |= BaseClass::Register();                                                         \
    result |= Fractal::ComponentRegistry::Register<ClassName>();                             \
    done = true;                                                                             \
  }                                                                                          \
  return result;                                                                             \
}                                                                                            \
private:

namespace Fractal
{
  class Node;

  class Impl_Component;

  /*
   * @brief The scene component base class.
   *
   * This is the base class for component types. Components can be attached to
   * Node's to add data or augment their behavior.
   */
  class flEXPORT Component : public Interface
  {
    friend Node;

    flPIMPL_DEF(Component);

  public:
    /**
     * @brief Called on the Update step.
     */
    virtual void OnUpdate();

    /**
     * @brief Called before the update step.
     */
    virtual void OnPreUpdate();

    /**
     * @brief Called after the Update step.
     */
    virtual void OnPostUpdate();

    /**
     * @brief Called on the Render step.
     */
    virtual void OnRender();

    /**
     * @brief Called before the Render step.
     */
    virtual void OnPreRender();

    /**
     * @brief Called after the Render step.
     */
    virtual void OnPostRender();

    /**
     * @brief Get the string ID of the component class.
     */
    static char const* Type()   { return "Unknown"; }

    /**
     * @brief Get the integer ID of the component class.
     *
     * This ID is assigned at runtime and may not be the same across
     */
    static int64_t TypeID() { return 0; }

    /**
     * @brief Get the string ID of the component instance.
     *
     * This coresponds to the value returned by Type() for a specific
     * Component subclass. This string can be used to determine the type
     * of a component instance at runtime, however GetTypeID() is
     * recommended in most situations.
     */
    virtual char const* GetType()   const = 0;

    /**
     * @brief Get the integer ID of the component instance.
     *
     * This coresponds to the value returned by TypeID() for a specific
     * Component subclass. This ID can be used to determine the type
     * of the component instance at runtime.
     *
     * @return The integer ID of the component instance.
     */
    virtual int64_t GetTypeID() const = 0;

    /**
     * @brief Get the Node that this component is attached to.
     *
     * @return A pointer to the Node.
     */
    Node* GetNode();

    /**
     * @brief Get the Node that the component is attached to.
     *
     * @return A const pointer to the Node.
     */
    Node const* GetNode() const;

    /**
     * @brief Check if a component instance is of a specific component type.
     *
     * @return Returns true if the component is, or is derived from, the component
     *         with the specified typeID.
     */
    bool Is(flIN int64_t typeID) const;

    /**
     * @brief Check if a component instance is of a specific component type.
     *
     * @return Returns true if the component is, or is derived from, the specified
     *         type.
     */
    template<typename T> bool Is() const
    {
      return Is(T::TypeID());
    }

    /**
     * @brief Get the component as a specific component type.
     *
     * @return Returns this component as a T pointer if it is, or is derived from,
     *         the specified type. Otherwise, nullptr is returned.
     */
    template<typename T> T* As() const
    {
      return Is(T::TypeID()) ? (T*)this : nullptr;
    }

  protected:
    static int64_t GetNextTypeID();
    static bool Register();

  private:
    void SetNode(Node* pParent);
  };
}
