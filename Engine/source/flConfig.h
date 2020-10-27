#ifndef flConfig_h__
#define flConfig_h__

#include <stdint.h>

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

#define flNew new
#define flDelete delete

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

#endif // flConfig_h__
