#pragma once

#include "flComponent.h"
#include "../flRef.h"
#include "../math/flMath.h"

namespace flEngine
{
  namespace Scene
  {
    class Impl_Transform;

    /**
     * @brief A transform hierarchy component.
     * 
     * This component represents a 3D transform in the hierarchy,
     */
    class flEXPORT Transform : public Component
    {
      flPIMPL_DEF(Transform);
      FL_IMPLEMENT_COMPONENT(Transform, "Transform", Component);

    public:
      /**
       * @brief Get the global transformation matrix.
       */
      Math::Mat4D GetTransform();

      /**
       * @brief Get the inverse of the global transformation matrix.
       */
      Math::Mat4D GetInverseTransform();

      /**
       * @brief Get the global position.
       */
      Math::Vec3D GetPosition();

      /**
       * @brief Get the global scale.
       */
      Math::Vec3D GetScale();

      /**
       * @brief Get the global orientation.
       */
      Math::QuatD GetOrientation();

      /**
       * @bref Set the global transform using a transformation matrix.
       */
      void SetTransform(flIN Math::Mat4D transform);

      /**
       * @bref Set the global position.
       */
      void SetPosition(flIN Math::Vec3D pos);

      /**
       * @bref Set the global scale.
       */
      void SetScale(flIN Math::Vec3D scale);

      /**
       * @bref Set the global orientation.
       */
      void SetOrientation(flIN Math::QuatD quat);

      /**
       * @bref Set the local transformation matrix.
       */
      Math::Mat4D GetLocalTransform();

      /**
       * @bref Set the inverse of the local transformation matrix.
       */
      Math::Mat4D GetInverseLocalTransform();

      /**
       * @brief Set the local position.
       */
      Math::Vec3D GetLocalPosition();

      /**
       * @brief Set the local scale.
       */
      Math::Vec3D GetLocalScale();

      /**
       * @brief Set the local orientation.
       */
      Math::QuatD GetLocalOrientation();

      /**
       * @brief Set the local transform using a transformation matrix.
       */
      void SetLocalTransform(flIN Math::Mat4D transform);

      /**
       * @brief Set the local position.
       */
      void SetLocalPosition(flIN Math::Vec3D pos);

      /**
       * @brief Set the local scale.
       */
      void SetLocalScale(flIN Math::Vec3D scale);

      /**
       * @brief Set the local orientation
       */
      void SetLocalOrientation(flIN Math::QuatD quat);

      /**
       * @brief Implicit conversion to a 4x4 Matrix.
       */
      inline operator Math::Mat4D() { return GetTransform(); }

      /**
       * @brief Get this Transforms' child count.
       */
      int64_t GetChildCount() const;

      /**
       * @brief Set this Transforms' parent.
       */
      void SetParent(flIN Transform* pParent);

      /**
       * @brief Get this Transforms' parent.
       */
      Transform * GetParent();

      /**
       * @brief Get a child of this Transform.
       * 
       * Get a child of this Transform using an index, where 0 <= index < GetChildCount().
       */
      Transform * GetChild(flIN int64_t index);

      /**
       * @brief Get this Transforms' parent. (const)
       */
      Transform const * GetParent() const;

      /**
       * @brief Get a child of this Transform. (const)
       *
       * Get a child of this Transform using an index, where 0 <= index < GetChildCount().
       */
      Transform const * GetChild(flIN int64_t index) const;
    };
  }
}
