#ifndef fl_Math_h__
#define fl_Math_h__

#include "../../tml/include/tmlMath.h"
#include "../flConfig.h"

namespace flEngine
{
  namespace Math
  {
    typedef flEXPORT tmlVector2<int32_t>   Vec2I;
    typedef flEXPORT tmlVector3<int32_t>   Vec3I;
    typedef flEXPORT tmlVector4<int32_t>   Vec4I;

    typedef flEXPORT tmlVector2<int64_t>   Vec2I64;
    typedef flEXPORT tmlVector3<int64_t>   Vec3I64;
    typedef flEXPORT tmlVector4<int64_t>   Vec4I64;

    typedef flEXPORT tmlVector2<float>     Vec2F;
    typedef flEXPORT tmlVector3<float>     Vec3F;
    typedef flEXPORT tmlVector4<float>     Vec4F;

    typedef flEXPORT tmlVector2<double>    Vec2D;
    typedef flEXPORT tmlVector3<double>    Vec3D;
    typedef flEXPORT tmlVector4<double>    Vec4D;

    typedef flEXPORT tmlMatrix4<double>    Mat4D;
    typedef flEXPORT tmlMatrix4<float>     Mat4F;

    typedef flEXPORT tmlQuaternion<double> QuatD;
    typedef flEXPORT tmlQuaternion<float>  QuatF;
  }
}

#endif // flMath_h__
