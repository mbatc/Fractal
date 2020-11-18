#ifndef fl_Math_h__
#define fl_Math_h__

#include "../../tml/include/tmlMath.h"
#include "../flConfig.h"

namespace flEngine
{
  namespace Math
  {
    typedef flEXPORT tmlVector2<int32_t>   flVec2I;
    typedef flEXPORT tmlVector3<int32_t>   flVec3I;
    typedef flEXPORT tmlVector4<int32_t>   flVec4I;

    typedef flEXPORT tmlVector2<int64_t>   flVec2I64;
    typedef flEXPORT tmlVector3<int64_t>   flVec3I64;
    typedef flEXPORT tmlVector4<int64_t>   flVec4I64;

    typedef flEXPORT tmlVector2<float>     flVec2F;
    typedef flEXPORT tmlVector3<float>     flVec3F;
    typedef flEXPORT tmlVector4<float>     flVec4F;

    typedef flEXPORT tmlVector2<double>    flVec2D;
    typedef flEXPORT tmlVector3<double>    flVec3D;
    typedef flEXPORT tmlVector4<double>    flVec4D;

    typedef flEXPORT tmlMatrix4<double>    flMat4D;
    typedef flEXPORT tmlMatrix4<float>     flMat4F;

    typedef flEXPORT tmlQuaternion<double> flQuatD;
    typedef flEXPORT tmlQuaternion<float>  flQuatF;
  }
}

#endif // flMath_h__
