#ifndef flPImpl_h__
#define flPImpl_h__

/**
 * Implementation typename for a class
 */
#define flPIMPL_NAME(Class) Impl_ ## Class

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
public:                                                 \
  ~Class();                                             \
  Class &operator=(const Class &rhs);                   \
  Class &operator=(Class &&rhs);                        \
private:                                                \
  static flPIMPL_NAME(Class)* __CreateImpl();           \
  flPIMPL_NAME(Class)* flPIMPL(Class) = __CreateImpl(); \


 /**
  * @brief Define that implements the PImpl declared in a class.
  *
  * This define can be used in a source file to implement a PImpl idiom definition. That was
  * created using the flPIMPL_DEF define.
  */
#define flPIMPL_IMPL(Class)\
Class::~Class() { flDelete flPIMPL(Class); }\
Class& Class::operator=(const Class &rhs) { *flPIMPL(Class) = *rhs.flPIMPL(Class); return *this; }\
Class& Class::operator=(Class &&rhs) { std::swap(flPIMPL(Class), rhs.flPIMPL(Class)); return *this; }\
decltype(Class::flPIMPL(Class)) Class::__CreateImpl() { return flNew std::remove_pointer<decltype(Class::flPIMPL(Class))>::type; }\

#endif // flPImpl_h__
