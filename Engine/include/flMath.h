#pragma once

#include "flConfig.h"
#include "math/flQuaternion.h"
#include "math/flMatrix4.h"
#include "math/flVector2.h"
#include "math/flVector3.h"
#include "math/flVector4.h"

namespace Fractal
{
  typedef flEXPORT Vector2<int32_t>   Vec2I;
  typedef flEXPORT Vector3<int32_t>   Vec3I;
  typedef flEXPORT Vector4<int32_t>   Vec4I;

  typedef flEXPORT Vector2<int64_t>   Vec2I64;
  typedef flEXPORT Vector3<int64_t>   Vec3I64;
  typedef flEXPORT Vector4<int64_t>   Vec4I64;

  typedef flEXPORT Vector2<float>     Vec2F;
  typedef flEXPORT Vector3<float>     Vec3F;
  typedef flEXPORT Vector4<float>     Vec4F;

  typedef flEXPORT Vector2<double>    Vec2D;
  typedef flEXPORT Vector3<double>    Vec3D;
  typedef flEXPORT Vector4<double>    Vec4D;

  typedef flEXPORT Matrix4<double>    Mat4D;
  typedef flEXPORT Matrix4<float>     Mat4F;

  typedef flEXPORT Quaternion<double> QuatD;
  typedef flEXPORT Quaternion<float>  QuatF;
}
