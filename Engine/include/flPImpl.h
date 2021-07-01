#pragma once

#include "flMemory.h"

/**
 * Implementation member variable name for a class
 */
#define flPIMPL(Class) pImpl ## Class

/**
 * @brief Define that declares the PImpl idiom in a class.
 * 
 * This define can be used within a class declaration to define a basic PImpl implementation.
 * This will define copy and move constructors and assignment operators and a destructor to
 * destruct the internal data.
 */
#define flPIMPL_DEF(Class)\
  friend Impl_ ## Class;\
public:                                                  \
  ~Class();                                              \
  Impl_ ## Class * Impl();                         \
  Impl_ ## Class const * Impl() const;             \
private:                                                 \
  static Impl_ ## Class* __CreateImpl();           \
  Impl_ ## Class* flPIMPL(Class) = __CreateImpl();

#define flPIMPL_DEF_COPY(Class) Class &operator=(const Class &rhs);

#define flPIMPL_DEF_MOVE(Class) Class &operator=(Class &&rhs);

 /**
  * @brief Define that implements the PImpl declared in a class.
  *
  * This define can be used in a source file to implement a PImpl idiom definition that was
  * created using the flPIMPL_DEF define.
  */
#define flPIMPL_IMPL(Class)\
Class::~Class()                            { flDelete flPIMPL(Class); }     \
Impl_ ## Class * Class::__CreateImpl()     { return flNew Impl_ ## Class; } \
Impl_ ## Class * Class::Impl()             { return flPIMPL(Class); }       \
Impl_ ## Class const * Class::Impl() const { return flPIMPL(Class); }

#define flPIMPL_IMPL_COPY(Class) Class& Class::operator=(const Class &rhs) { *Impl() = *rhs.Impl(); return *this; }

#define flPIMPL_IMPL_MOVE(Class)\
Class& Class::operator=(Class &&rhs) \
{                                    \
  Impl_ ## Class *pTemp = Impl();    \
  flPIMPL(Class) = rhs.Impl();       \
  rhs.flPIMPL(Class) = pTemp;        \
  return *this;                      \
}
