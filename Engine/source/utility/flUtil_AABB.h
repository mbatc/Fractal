#ifndef flUtil_AABB_h__
#define flUtil_AABB_h__

#include "flConfig.h"
#include "atAABB.h"

namespace flEngine
{
  namespace Util
  {
    template<typename T> using AABB = atAABB<T>;

    typedef AABB<float>    flEXPORT AABBF;
    typedef AABB<double>   flEXPORT AABBD;
    typedef AABB<int32_t>  flEXPORT AABBI;
    typedef AABB<int64_t>  flEXPORT AABBI64;
    typedef AABB<uint32_t> flEXPORT AABBUI;
    typedef AABB<uint64_t> flEXPORT AABBUI64;
  };
};

#endif // flUtil_AABB_h__
