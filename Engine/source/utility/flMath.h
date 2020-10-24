#ifndef flMath_h__
#define flMath_h__

#include "flConfig.h"

#include "atVector2.h"
#include "atVector3.h"
#include "atVector4.h"
#include "atMatrix.h"
#include "atQuaternion.h"

namespace flEngine
{
  namespace Math
  {
    template<typename T> using Vec2 = atVector2<T>;
    template<typename T> using Vec3 = atVector3<T>;
    template<typename T> using Vec4 = atVector4<T>;
    template<typename T> using Mat4 = atMatrix4x4<T>;
    template<typename T> using Quat = atQuaternion<T>;

    typedef Vec2<float>    flEXPORT Vec2F;
    typedef Vec2<double>   flEXPORT Vec2D;
    typedef Vec2<int32_t>  flEXPORT Vec2I;
    typedef Vec2<int64_t>  flEXPORT Vec2I64;
    typedef Vec2<uint32_t> flEXPORT Vec2UI;
    typedef Vec2<uint64_t> flEXPORT Vec2UI64;

    typedef Vec3<float>    flEXPORT Vec3F;
    typedef Vec3<double>   flEXPORT Vec3D;
    typedef Vec3<int32_t>  flEXPORT Vec3I;
    typedef Vec3<int64_t>  flEXPORT Vec3I64;
    typedef Vec3<uint32_t> flEXPORT Vec3UI;
    typedef Vec3<uint64_t> flEXPORT Vec3UI64;

    typedef Vec4<float>    flEXPORT Vec4F;
    typedef Vec4<double>   flEXPORT Vec4D;
    typedef Vec4<int32_t>  flEXPORT Vec4I;
    typedef Vec4<int64_t>  flEXPORT Vec4I64;
    typedef Vec4<uint32_t> flEXPORT Vec4UI;
    typedef Vec4<uint64_t> flEXPORT Vec4UI64;

    typedef Mat4<float>    flEXPORT Mat4F;
    typedef Mat4<double>   flEXPORT Mat4D;
    typedef Mat4<int32_t>  flEXPORT Mat4I;
    typedef Mat4<int64_t>  flEXPORT Mat4UI64;
    typedef Mat4<uint32_t> flEXPORT Mat4UI;
    typedef Mat4<uint64_t> flEXPORT Mat4UI64;

    typedef Quat<float>    flEXPORT QuatF;
    typedef Quat<double>   flEXPORT QuatD;
    typedef Quat<int32_t>  flEXPORT QuatI;
    typedef Quat<int64_t>  flEXPORT QuatUI64;
    typedef Quat<uint32_t> flEXPORT QuatUI;
    typedef Quat<uint64_t> flEXPORT QuatUI64;
  };
};

#endif // flMath_h__
