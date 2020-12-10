#ifndef fl_PImpl_h__
#define fl_PImpl_h__

/**
 * Implementation typename for a class
 */
#define flPIMPL_CLASS(Class) Impl_ ## Class

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
  friend flPIMPL_CLASS(Class);\
public:                                                  \
  ~Class();                                              \
  flPIMPL_CLASS(Class)* GetImpl() const;                 \
private:                                                 \
  static flPIMPL_CLASS(Class)* __CreateImpl();           \
  flPIMPL_CLASS(Class)* flPIMPL(Class) = __CreateImpl();

#define flPIMPL_DEF_COPY(Class) Class &operator=(const Class &rhs);

#define flPIMPL_DEF_MOVE(Class) Class &operator=(Class &&rhs);


 /**
  * @brief Define that implements the PImpl declared in a class.
  *
  * This define can be used in a source file to implement a PImpl idiom definition. That was
  * created using the flPIMPL_DEF define.
  */
#define flPIMPL_IMPL(Class)\
template<typename T> inline T __remove_ptr(T *p) { return *p; }\
Class::~Class() { flDelete flPIMPL(Class); }\
flPIMPL_CLASS(Class)* Class::GetImpl() const { return flPIMPL(Class); }\
decltype(Class::flPIMPL(Class)) Class::__CreateImpl() { return flNew decltype(__remove_ptr(Class::flPIMPL(Class))); }

#define flPIMPL_IMPL_COPY(Class) Class& Class::operator=(const Class &rhs) { *flPIMPL(Class) = *rhs.flPIMPL(Class); return *this; }

#define flPIMPL_IMPL_MOVE(Class) Class& Class::operator=(Class &&rhs) \
Class& Class::operator=(Class &&rhs)                                  \
{                                                                     \
  flPIMPL_NAME(Class) *pTemp = flPIMPL(Class);                        \
  flPIMPL(Class) = rhs.flPIMPL(Class);                                \
  rhs.flPIMPL(Class) = pTemp;                                         \
  return *this;                                                       \
}


#endif // flPImpl_h__
