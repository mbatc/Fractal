#ifndef flUtil_Rect_h__
#define flUtil_Rect_h__

#include "flConfig.h"
#include "atRect.h"

namespace flEngine
{
  namespace Util
  {
    template<typename T> using Rect = atRect<T>;

    typedef Rect<float>    flEXPORT RectF;
    typedef Rect<double>   flEXPORT RectD;
    typedef Rect<int32_t>  flEXPORT RectI;
    typedef Rect<int64_t>  flEXPORT RectI64;
    typedef Rect<uint32_t> flEXPORT RectUI;
    typedef Rect<uint64_t> flEXPORT RectUI64;
  };
};

#endif // flUtil_Rect_h__
