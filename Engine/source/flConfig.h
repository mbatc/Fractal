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

#endif // flConfig_h__
