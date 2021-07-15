#pragma once

#include "flMemory.h"
#include "flPImpl.h"

namespace Fractal
{
  /**
   * @brief Engine API base class.
   *
   * The Interface class is the common base class of the Engines components
   * and implements common behaviors. These are:
   *   1. Reference Counting [IncRef(), DecRef()]
   *   2. Object destruction [Destroy()]
   */
  class flEXPORT Interface
  {
  public:
    /**
     * @brief Increment the interface reference count.
     *
     * This function will increment the internal reference count for this
     * interface instance. Each IncRef() call should have a corresponding
     * DecRef() call (unless the interface is explicitly destroyed using
     * the Destroy() function, though be careful doing this).
     */
    virtual void IncRef() = 0;

    /**
     * @brief Decrement the Interface reference count.
     *
     * This function will decrement the internal reference count for this
     * interface instance. If, after decrementing the reference count, it
     * is 0, the interface will be destroyed.
     *
     * For that reason, after calling this function the pointer to the interface
     * should not be used (although there is nothing stopping you from doing so).
     */
    virtual void DecRef() = 0;

    /**
     * @brief Explicitly destroy the Interface instance.
     *
     * This function will destruct the interface instance. Using DecRef() should
     * be preferred in case there are still outstanding active references to the
     * interface.
     *
     * This will invalidate the pointer to the interface.
     */
    virtual void Destroy() = 0;
  };
}

#define FRACTAL_DEFAULT_INTERFACE \
public:\
  virtual void IncRef()  override { if (this != nullptr) ++m_refCount; } \
  virtual void DecRef()  override { if (this != nullptr) if (--m_refCount == 0) Destroy(); } \
  virtual void Destroy() override { flDelete this; }\
private: int64_t m_refCount = 1;