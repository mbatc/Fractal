#pragma once

#include "flComponent.h"
#include "../flRef.h"
#include "../math/flMath.h"

namespace flEngine
{
  namespace Scene
  {
    class Impl_Transform;

    class flEXPORT Transform : public Component
    {
      flPIMPL_DEF(Transform);
      FL_IMPLEMENT_COMPONENT(Transform, "Transform", Component);

    public:
      Math::Mat4D GetTransform();

      Math::Mat4D GetInverseTransform();

      Math::Vec3D GetPosition();

      Math::Vec3D GetScale();

      Math::QuatD GetOrientation();

      void SetTransform(Math::Mat4D transform);

      void SetPosition(Math::Vec3D pos);

      void SetScale(Math::Vec3D scale);

      void SetOrientation(Math::QuatD quat);

      Math::Mat4D GetLocalTransform();

      Math::Mat4D GetInverseLocalTransform();

      Math::Vec3D GetLocalPosition();

      Math::Vec3D GetLocalScale();

      Math::QuatD GetLocalOrientation();

      void SetLocalTransform(Math::Mat4D transform);

      void SetLocalPosition(Math::Vec3D pos);

      void SetLocalScale(Math::Vec3D scale);

      void SetLocalOrientation(Math::QuatD quat);

      operator Math::Mat4D() { return GetTransform(); }

      int64_t GetChildCount() const;

      void        SetParent(Transform* pParent);
      Transform * GetParent();

      Transform * GetChild(int64_t index);

      Transform const * GetParent() const;
      Transform const * GetChild(int64_t index) const;
    };
  }
}
