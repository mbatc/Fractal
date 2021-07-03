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
      m_target = MakeRef(GetGUI()->GetGraphicsAPI()->CreateTextureRenderTarget(), false);
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

  DeviceState* pState = GetGUI()->GetGraphicsAPI()->GetState();
  pState->SetFeatureEnabled(DeviceFeature_DepthTest, true);

  Window* pWindow = GetGUI()->GetMainWindow();
  API* pGraphics = GetGUI()->GetGraphicsAPI();

  // Draw to the first window
  Mat4F projection = m_camera.ProjectionMatrix() * m_camera.ViewMatrix();

  pState->SetViewport(0, 0, m_target->GetWidth(), m_target->GetHeight());

  class RenderVisitor : public Visitor<Component>
  {
  public:
    RenderVisitor(Mat4F projection, API* pAPI)
      : m_projection(projection)
      , m_pGraphics(pAPI)
    {}

    bool OnEnter(Component* pComponent) override
    {
      MeshRenderer* pMesh = pComponent->As<MeshRenderer>();
      if (pMesh == nullptr)
        return false;

      Transform* pTransform = pMesh->GetNode()->GetTransform();

      if (pTransform)
      {
        Mat4F mvp = m_projection * (Mat4F)pTransform->GetTransform();
        pMesh->GetMesh()->GetVertexArray()->Bind();
        for (int64_t subMesh = 0; subMesh < pMesh->GetSubMeshCount(); ++subMesh)
        {
          Program*        pShader   = pMesh->GetShader(subMesh);
          ShaderMaterial* pMaterial = pMesh->GetMaterial(subMesh);
          pShader->SetMat4("mvp", mvp);
          pShader->Bind();
          pMaterial->Bind();
          RenderMesh::SubMesh const* pSubMesh  = pMesh->GetSubMesh(subMesh);
          m_pGraphics->Render(DrawMode_Triangles, true, pSubMesh->offset, pSubMesh->count);
        }
      }

      return true;
    }

    Mat4F m_projection;
    API* m_pGraphics;
  };

  SceneGraph* pScene = Application::Get().GetModule<SceneManager>()->ActiveScene();
  RenderVisitor renderVisitor(projection, pGraphics);

  pScene->Traverse(nullptr, &renderVisitor);
}

void SceneViewPanel::OnGUI()
{
  if (m_target != nullptr)
    Widgets::Image(m_target->GetColourTarget(), ContentAreaSize().x, ContentAreaSize().y);
}

PerspectiveCamera::PerspectiveCamera(Keyboard* pKeyboard, Mouse* pMouse)
{
  m_pKeyboard = pKeyboard;
  m_pMouse = pMouse;
}

Mat4F PerspectiveCamera::ViewMatrix()
{
  return (Mat4F::Translation(position) * Mat4F::YawPitchRoll(ypr)).Inverse();
}

Mat4F PerspectiveCamera::ProjectionMatrix()
{
  return Mat4F::Projection(width / height, FOV, nearPlane, height);
}

void PerspectiveCamera::Update()
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
