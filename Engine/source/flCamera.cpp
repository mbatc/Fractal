#include "flCamera.h"
#include "flNode.h"
#include "flTransform.h"

namespace Fractal
{
  class Impl_Camera
  {
  public:
    Mat4D projectionMatrix;
  };

  flPIMPL_IMPL(Camera);

  Mat4D Camera::GetViewMatrix()
  {
    return GetNode()->GetTransform()->GetInverseTransform();
  }

  Mat4D Camera::GetProjectionMatrix()
  {
    return Impl()->projectionMatrix;
  }

  void Camera::SetProjectionMatrix(flIN Mat4D projection)
  {
    Impl()->projectionMatrix = projection;
  }

  class Impl_PerspectiveCamera
  {
  public:
    double nearPlane;
    double farPlane;
    double fov;
    double viewportX;
    double viewportY;
    double viewportWidth;
    double viewportHeight;
  };

  flPIMPL_IMPL(PerspectiveCamera);

  void PerspectiveCamera::OnPreUpdate()
  {
    SetProjectionMatrix(Mat4D::Projection(
                          GetViewportAspectRatio(),
                          Impl()->fov,
                          Impl()->nearPlane,
                          Impl()->farPlane
                        )
                       );
  }

  double PerspectiveCamera::GetFieldOfView() const
  {
    return Impl()->fov;
  }

  double PerspectiveCamera::GetNearPlane() const
  {
    return Impl()->nearPlane;
  }

  double PerspectiveCamera::GetFarPlane() const
  {
    return Impl()->farPlane;
  }

  void PerspectiveCamera::SetFieldOfView(flIN double fov)
  {
    Impl()->fov = fov;
  }

  void PerspectiveCamera::SetNearPlane(flIN double nearPlane)
  {
    Impl()->nearPlane = nearPlane;
  }

  void PerspectiveCamera::SetFarPlane(flIN double farPlane)
  {
    Impl()->farPlane = farPlane;
  }

  double PerspectiveCamera::GetViewportWidth() const
  {
    return Impl()->viewportWidth;
  }

  double PerspectiveCamera::GetViewportHeight() const
  {
    return Impl()->viewportHeight;
  }

  double PerspectiveCamera::GetViewportAspectRatio() const
  {
    return Impl()->viewportWidth / Impl()->viewportHeight;
  }

  double PerspectiveCamera::GetViewportX() const
  {
    return Impl()->viewportX;
  }

  double PerspectiveCamera::GetViewportY() const
  {
    return Impl()->viewportY;
  }

  void PerspectiveCamera::SetViewportSize(flIN double width, flIN double height)
  {
    Impl()->viewportWidth = width;
    Impl()->viewportHeight = height;
  }

  void PerspectiveCamera::SetViewportPosition(flIN double x, flIN double y)
  {
    Impl()->viewportX = x;
    Impl()->viewportY = y;
  }
}
