#ifndef flUtil_OBB_h__
#define flUtil_OBB_h__

#include "flConfig.h"
#include "atOBB.h"

namespace flEngine
{
  namespace Util
  {
    template<typename T> using OBB = OBB<T>;

    typedef OBB<float>    flEXPORT OBBF;
    typedef OBB<double>   flEXPORT OBBD;
    typedef OBB<int32_t>  flEXPORT OBBI;
    typedef OBB<int64_t>  flEXPORT OBBI64;
    typedef OBB<uint32_t> flEXPORT OBBUI;
    typedef OBB<uint64_t> flEXPORT OBBUI64;
  };
};

#endif // flUtil_OBB_h__
