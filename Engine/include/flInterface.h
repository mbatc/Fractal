#ifndef fl_Interface_h__
#define fl_Interface_h__

#include "flConfig.h"
#include "flPImpl.h"

namespace flEngine
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
    void IncRef();

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
    void DecRef();

    /**
     * @brief Explicitly destroy the Interface instance.
     *
     * This function will destruct the interface instance. Using DecRef() should
     * be preferred in case there are still outstanding active references to the
     * interface.
     *
     * This will invalidate the pointer to the interface.
     */
    void Destroy();

    /**
     * @brief Get the active reference count.
     *
     * This function returns the number of references acquired through the IncRef
     * function. This will always return 1 or greater.
     */
    int64_t GetReferenceCount() const;

  protected:
    /**
    * @brief Construct a new Interface.
    *
    * Interface object constructor. This is protected as only derived classes should
    * construct Interface instances.
    */
    Interface();

    /**
    * @brief Destruct an Interface instance.
    *
    * Interface object destructor. This is protected as Engine API objects should only be
    * destroyed via the DecRef() or Destroy() functions.
    */
    virtual ~Interface();

  private:
    int64_t m_refCount = 0; // Internal reference count
  };
}

#endif // fl_Interface_h__
