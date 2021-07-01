#pragma once

#include "flEngine.h"
#include "ctVector.h"

class PerspectiveCamera
{
public:
  PerspectiveCamera(flEngine::Input::Keyboard* pKeyboard, flEngine::Input::Mouse* pMouse);

  flEngine::Math::Mat4F ViewMatrix();
  flEngine::Math::Mat4F ProjectionMatrix();

  void Update();

  float nearPlane = 0.01;
  float farPlane = 100;
  float FOV = ctDegs2Radsf(50);
  float width = 1;
  float height = 1;
  flEngine::Math::Vec3D position = { 0, 0, 0 };
  flEngine::Math::Vec3D ypr = { 0, 0, 0 };

  flEngine::Input::Keyboard *m_pKeyboard;
  flEngine::Input::Mouse *m_pMouse;
};

class SceneViewPanel : public flEngine::GUI::Panel
{
public:
  SceneViewPanel(flEngine::GUI::GUIModule* pGUI);

  virtual bool OnStartup() override;
  virtual void OnUpdate() override;
  virtual void OnRender() override;
  virtual void OnGUI() override;

  PerspectiveCamera m_camera;

  flEngine::Ref<flEngine::Graphics::Program>        pProgram;
  flEngine::Ref<flEngine::Graphics::Sampler>        pSampler;
  flEngine::Ref<flEngine::Graphics::RenderMesh>     pRenderMesh;

  ctVector<flEngine::Ref<flEngine::Graphics::ShaderMaterial>> materials;

  flEngine::Ref<flEngine::Graphics::TextureRenderTarget> m_target;
};
