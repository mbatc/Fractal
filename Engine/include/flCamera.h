#pragma once

#include "flComponent.h"
#include "flMath.h"

namespace Fractal
{
  class Impl_Camera;

  class flEXPORT Camera : public Component
  {
    FL_IMPLEMENT_COMPONENT(Camera, "Camera", Component);

    flPIMPL_DEF(Camera);

  public:
    Mat4D GetViewMatrix();

    Mat4D GetProjectionMatrix();

    void SetProjectionMatrix(flIN Mat4D projection);
  };

  class Impl_PerspectiveCamera;

  class flEXPORT PerspectiveCamera : public Camera
  {
    FL_IMPLEMENT_COMPONENT(PerspectiveCamera, "Perspective Camera", Camera);

    flPIMPL_DEF(PerspectiveCamera);

  public:
    virtual void OnPreUpdate() override;

    double GetFieldOfView() const;

    double GetNearPlane() const;

    double GetFarPlane() const;

    void SetFieldOfView(flIN double fov);

    void SetNearPlane(flIN double nearPlane);

    void SetFarPlane(flIN double nearPlane);

    double GetViewportWidth() const;

    double GetViewportHeight() const;

    double GetViewportX() const;

    double GetViewportY() const;

    double GetViewportAspectRatio() const;

    void SetViewportSize(flIN double width, flIN double height);

    void SetViewportPosition(flIN double x, flIN double y);
  };
}