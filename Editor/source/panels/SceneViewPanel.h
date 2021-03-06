#pragma once

#include "flEngine.h"
#include "ctVector.h"

class EditorPerspectiveCamera
{
public:
  EditorPerspectiveCamera(Fractal::Keyboard* pKeyboard, Fractal::Mouse* pMouse);

  Fractal::Mat4F ViewMatrix();
  Fractal::Mat4F ProjectionMatrix();

  void Update();

  float nearPlane = 0.01;
  float farPlane = 100;
  float FOV = ctDegs2Radsf(50);
  float width = 1;
  float height = 1;
  Fractal::Vec3D position = { 0, 0, 0 };
  Fractal::Vec3D ypr = { 0, 0, 0 };

  Fractal::Keyboard* m_pKeyboard;
  Fractal::Mouse* m_pMouse;
};

class SceneViewPanel : public Fractal::Panel
{
public:
  SceneViewPanel(Fractal::GUIModule* pGUI);

  virtual bool OnStartup() override;
  virtual void OnUpdate() override;
  virtual void OnRender() override;
  virtual void OnGUI() override;

  EditorPerspectiveCamera m_camera;

  Fractal::Ref<Fractal::TextureRenderTarget> m_target;
};
