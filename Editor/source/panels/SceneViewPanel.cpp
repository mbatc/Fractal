#include "SceneViewPanel.h"

#include "ctFile.h"
#include "ctFilename.h"

using namespace Fractal;

SceneViewPanel::SceneViewPanel(GUIModule* pGUI)
  : Panel(pGUI, "Scene View")
  , m_camera(pGUI->GetKeyboard(), pGUI->GetMouse())
{
  GetStyle()->Set(
  {
    { GUIStyle_WindowPadding, Vec2F(0, 0)},
    { GUIStyle_WindowBorderSize, 0.0f }
  }
  );
}

bool SceneViewPanel::OnStartup()
{
  return true;
}

void SceneViewPanel::OnUpdate()
{
  m_camera.Update();
  m_camera.width = (float)ContentAreaSize().x;
  m_camera.height = (float)ContentAreaSize().y;

  if (!m_target || m_target->GetWidth() != ContentAreaSize().x || m_target->GetHeight() != ContentAreaSize().y)
  {
    RenderTargetOptions opts;
    opts.colourFormat = PixelFormat_RGBA;
    opts.pixelComponentType = PixelComponentType_UNorm8;
    opts.depthFormat = DepthFormat_Float24Stencil8;
    opts.width = (int64_t)ContentAreaSize().x;
    opts.height = (int64_t)ContentAreaSize().y;

    m_target = nullptr;
    if (opts.width > 0 && opts.height > 0)
    {
      m_target = MakeRef(GetGraphicsAPI()->CreateTextureRenderTarget(), false);
      m_target->SetFormat(&opts);
    }
  }
}

void SceneViewPanel::OnRender()
{
  if (m_target == nullptr)
    return;

  m_target->Bind();
  m_target->Clear(0xFFFFFFFF);

  DeviceState* pState = GetGraphicsAPI()->GetState();
  pState->SetFeatureEnabled(DeviceFeature_DepthTest, true);

  Window* pWindow = GetMainWindow();
  API* pGraphics = GetGraphicsAPI();

  pState->SetViewport(0, 0, m_target->GetWidth(), m_target->GetHeight());

  SceneGraph* pScene = GetApplication()->GetModule<SceneManager>()->ActiveScene();

  SceneRenderer renderer;
  renderer.Begin(pScene);
  renderer.Submit(pScene->GetRootNode());
  renderer.End();
  renderer.Draw(m_camera.ViewMatrix(), m_camera.ProjectionMatrix());
}

void SceneViewPanel::OnGUI()
{
  if (m_target != nullptr)
    Widgets::Image(m_target->GetColourTarget(), ContentAreaSize().x, ContentAreaSize().y);
}

EditorPerspectiveCamera::EditorPerspectiveCamera(Keyboard* pKeyboard, Mouse* pMouse)
{
  m_pKeyboard = pKeyboard;
  m_pMouse = pMouse;
}

Mat4F EditorPerspectiveCamera::ViewMatrix()
{
  return (Mat4F::Translation(position) * Mat4F::YawPitchRoll(ypr)).Inverse();
}

Mat4F EditorPerspectiveCamera::ProjectionMatrix()
{
  return Mat4F::Projection(width / height, FOV, nearPlane, height);
}

void EditorPerspectiveCamera::Update()
{
  Vec3F velocity;
  if (m_pKeyboard->GetKeyDown(KC_A))
    velocity.x -= 1;
  if (m_pKeyboard->GetKeyDown(KC_D))
    velocity.x += 1;
  if (m_pKeyboard->GetKeyDown(KC_W))
    velocity.z -= 1;
  if (m_pKeyboard->GetKeyDown(KC_S))
    velocity.z += 1;
  if (m_pKeyboard->GetKeyDown(KC_E))
    velocity.y += 1;
  if (m_pKeyboard->GetKeyDown(KC_Q))
    velocity.y -= 1;

  velocity = Mat4F::YawPitchRoll(ypr) * velocity;

  position += velocity * 0.025;

  if (m_pMouse->GetDown(MB_Right))
  {
    Vec3F deltaYPR;
    float aspect = width / height;
    deltaYPR.x -= m_pMouse->GetPositionDelta().x / aspect;
    deltaYPR.y -= m_pMouse->GetPositionDelta().y;

    ypr += deltaYPR * 0.005;
  }
}
