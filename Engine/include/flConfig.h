#pragma once

#include <stdint.h>
#include <memory>

#ifdef flSTATICLIB
#define flEXPORT
#define flCCONV
#else
#ifdef flCOMPILESHARED
#define flEXPORT _declspec(dllexport)
#else
#define flEXPORT _declspec(dllimport)
#endif
#define flCCONV _cdecl
#endif

#define flPLATFORM_WINDOWS 0
#define flPLATFORM_LINUX 0

#ifdef _WIN32
#undef flPLATFORM_WINDOWS
#define flPLATFORM_WINDOWS 1
#elif __linux__
#undef flPLATFORM_LINUX
#define flPLATFORM_LINUX 1
#else
static_assert(false, "The current platform is not supported. Must be Windows or Linux");
#endif

#define flUSING(x) x

#define flOUT
#define flIN

#define flBITWISE_ENUM_OPERATOR(type, op)\
inline type operator op (const type &a, const type &b) { return (type)((int64_t)a op (int64_t)b); }\

#define flBITWISE_ENUM_OPERATORS(type)\
flBITWISE_ENUM_OPERATOR(type, | )\
flBITWISE_ENUM_OPERATOR(type, & )\
inline type operator~(const type &a) { return (type)(~(int64_t)a); }

#define flHasFlag(bitfield, flag) bool((bitfield & flag) != 0)
