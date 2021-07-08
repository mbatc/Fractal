#pragma once

#include "flComponent.h"
#include "flRef.h"
#include "flMath.h"

namespace Fractal
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
    Mat4D GetTransform();

    /**
     * @brief Get the inverse of the global transformation matrix.
     */
    Mat4D GetInverseTransform();

    /**
     * @brief Get the global position.
     */
    Vec3D GetPosition();

    /**
     * @brief Get the global scale.
     */
    Vec3D GetScale();

    /**
     * @brief Get the global orientation.
     */
    QuatD GetOrientation();

    /**
     * @brief Set the global transform using a transformation matrix.
     */
    void SetTransform(flIN Mat4D transform);

    /**
     * @brief Set the global position.
     */
    void SetPosition(flIN Vec3D pos);

    /**
     * @brief Set the global scale.
     */
    void SetScale(flIN Vec3D scale);

    /**
     * @brief Set the global orientation.
     */
    void SetOrientation(flIN QuatD quat);

    /**
     * @brief Set the local transformation matrix.
     */
    Mat4D GetLocalTransform();

    /**
     * @brief Set the inverse of the local transformation matrix.
     */
    Mat4D GetInverseLocalTransform();

    /**
     * @brief Set the local position.
     */
    Vec3D GetLocalPosition();

    /**
     * @brief Set the local scale.
     */
    Vec3D GetLocalScale();

    /**
     * @brief Set the local orientation.
     */
    QuatD GetLocalOrientation();

    /**
     * @brief Set the local transform using a transformation matrix.
     */
    void SetLocalTransform(flIN Mat4D transform);

    /**
     * @brief Set the local position.
     */
    void SetLocalPosition(flIN Vec3D pos);

    /**
     * @brief Set the local scale.
     */
    void SetLocalScale(flIN Vec3D scale);

    /**
     * @brief Set the local orientation
     */
    void SetLocalOrientation(flIN QuatD quat);

    /**
     * @brief Implicit conversion to a 4x4 Matrix.
     */
    inline operator Mat4D() { return GetTransform(); }

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
    Transform* GetParent();

    /**
     * @brief Get a child of this Transform.
     *
     * Get a child of this Transform using an index, where 0 <= index < GetChildCount().
     */
    Transform* GetChild(flIN int64_t index);

    /**
     * @brief Get this Transforms' parent. (const)
     */
    Transform const* GetParent() const;

    /**
     * @brief Get a child of this Transform. (const)
     *
     * Get a child of this Transform using an index, where 0 <= index < GetChildCount().
     */
    Transform const* GetChild(flIN int64_t index) const;

    bool RemoveChild(Transform const * pTransform);

    bool RemoveChild(flIN int64_t index);
  };
}
