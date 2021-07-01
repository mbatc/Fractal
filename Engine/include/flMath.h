#pragma once

#include "flConfig.h"
#include "../../ctools/modules/math/include/LinearAlgebra/ctQuaternion.h"
#include "../../ctools/modules/math/include/LinearAlgebra/ctMatrix4.h"
#include "../../ctools/modules/math/include/LinearAlgebra/ctVector2.h"
#include "../../ctools/modules/math/include/LinearAlgebra/ctVector3.h"
#include "../../ctools/modules/math/include/LinearAlgebra/ctVector4.h"

namespace Fractal
{
  typedef flEXPORT ctVector2<int32_t>   Vec2I;
  typedef flEXPORT ctVector3<int32_t>   Vec3I;
  typedef flEXPORT ctVector4<int32_t>   Vec4I;

  typedef flEXPORT ctVector2<int64_t>   Vec2I64;
  typedef flEXPORT ctVector3<int64_t>   Vec3I64;
  typedef flEXPORT ctVector4<int64_t>   Vec4I64;

  typedef flEXPORT ctVector2<float>     Vec2F;
  typedef flEXPORT ctVector3<float>     Vec3F;
  typedef flEXPORT ctVector4<float>     Vec4F;

  typedef flEXPORT ctVector2<double>    Vec2D;
  typedef flEXPORT ctVector3<double>    Vec3D;
  typedef flEXPORT ctVector4<double>    Vec4D;

  typedef flEXPORT ctMatrix4<double>    Mat4D;
  typedef flEXPORT ctMatrix4<float>     Mat4F;

  typedef flEXPORT ctQuaternion<double> QuatD;
  typedef flEXPORT ctQuaternion<float>  QuatF;
}
