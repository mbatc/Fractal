#include "SceneViewPanel.h"

using namespace flEngine;
using namespace flEngine::GUI;
using namespace flEngine::Util;
using namespace flEngine::Math;
using namespace flEngine::Input;
using namespace flEngine::Graphics;
using namespace flEngine::Platform;

SceneViewPanel::SceneViewPanel(GUISystem* pGUI)
    : Panel(pGUI, "Scene View")
    , m_camera(pGUI->GetKeyboard(), pGUI->GetMouse())
  {}

bool SceneViewPanel::OnStartup()
{
  Graphics::API* pGraphics = GetGUI()->GetGraphicsAPI();

  pProgram = MakeRef(pGraphics->CreateProgram(), false);
  pProgram->SetShaderFromFile("../../Engine/assets/shader-library/textured.frag", ProgramStage_Fragment);
  pProgram->SetShaderFromFile("../../Engine/assets/shader-library/transform.vert", ProgramStage_Vertex);
  pProgram->Compile();

  pTexture = MakeRef(pGraphics->CreateTexture2D(PixelFormat_RGBA, PixelComponentType_UNorm8), false);
  // Image image("C:/Users/mickb/Pictures/test.jpg");
  Image image("../../Engine/assets/texture-library/albedo/test0.jpg");
  pTexture->SetFromImage(&image);
  pTexture->GenerateMipMaps();

  pMaterial = MakeRef(pGraphics->CreateMaterial(pProgram), false);
  pMaterial->SetTexture("texture0", pTexture);
  pMaterial->SetValue("albedo0", Vec4F(1, 0, 0, 1));
  pMaterial->Apply();

  pSampler = MakeRef(pGraphics->CreateSampler(), false);
  pSampler->SetWrapMode(WrapMode_Mirror);
  pSampler->SetFilterMinMode(FilterMode_Linear, true);

  pGeometry = MakeRef(pGraphics->CreateVertexArray(), false);

  // Construct a simple cube
  {
    // Create vertex and index buffers
    Ref<VertexBuffer> pPositionBuffer = MakeRef(pGraphics->CreateVertexBuffer(sizeof(float) * 3 * 8, nullptr), false);
    Ref<VertexBuffer> pColourBuffer = MakeRef(pGraphics->CreateVertexBuffer(sizeof(float) * 4 * 8, nullptr), false);
    Ref<VertexBuffer> pTexcoordBuffer = MakeRef(pGraphics->CreateVertexBuffer(sizeof(float) * 2 * 8, nullptr), false);
    Ref<IndexBuffer>  pIndexBuffer = MakeRef(pGraphics->CreateIndexBuffer(36), false);

    // Map buffers to client memory
    Vec3F* pPositions = (Vec3F*)pPositionBuffer->GetBuffer()->Map(AccessFlag_Write);
    Vec2F* pTexcoords = (Vec2F*)pTexcoordBuffer->GetBuffer()->Map(AccessFlag_Write);
    Vec4F* pColours = (Vec4F*)pColourBuffer->GetBuffer()->Map(AccessFlag_Write);

    uint32_t* pIndices = (uint32_t*)pIndexBuffer->GetBuffer()->Map(AccessFlag_Write);
    pPositionBuffer->SetLayout({ { "position0", Type_Float32, 3 } });
    pColourBuffer->SetLayout({ { "colour0",   Type_Float32, 4 } });
    pTexcoordBuffer->SetLayout({ { "texcoord0", Type_Float32, 2 } });

    // Set vertex data
    pPositions[0] = { -1, -1, -1 };  pColours[0] = { 1, 0, 0, 1 }; pTexcoords[0] = { 0, 0 };
    pPositions[1] = { -1, -1,  1 };  pColours[1] = { 0, 1, 0, 1 }; pTexcoords[1] = { 2, 0 };
    pPositions[2] = { 1, -1,  1 };   pColours[2] = { 0, 0, 1, 1 }; pTexcoords[2] = { 2, 2 };
    pPositions[3] = { 1, -1, -1 };   pColours[3] = { 1, 0, 0, 1 }; pTexcoords[3] = { 0, 2 };
    pPositions[4] = { -1,  1, -1 };  pColours[4] = { 0, 1, 0, 1 }; pTexcoords[4] = { 2, 2 };
    pPositions[5] = { -1,  1,  1 };  pColours[5] = { 0, 0, 1, 1 }; pTexcoords[5] = { 0, 2 };
    pPositions[6] = { 1,  1,  1 };   pColours[6] = { 1, 0, 0, 1 }; pTexcoords[6] = { 0, 0 };
    pPositions[7] = { 1,  1, -1 };   pColours[7] = { 0, 1, 0, 1 }; pTexcoords[7] = { 2, 0 };

    // Set index data
    // Bottom        // Front         // Left          // Back          // Right         // Top
    pIndices[0] = 0; pIndices[6] = 0;  pIndices[12] = 1; pIndices[18] = 2; pIndices[24] = 3; pIndices[30] = 4;
    pIndices[1] = 1; pIndices[7] = 4;  pIndices[13] = 5; pIndices[19] = 6; pIndices[25] = 7; pIndices[31] = 5;
    pIndices[2] = 2; pIndices[8] = 7;  pIndices[14] = 4; pIndices[20] = 5; pIndices[26] = 6; pIndices[32] = 6;
    pIndices[3] = 0; pIndices[9] = 0;  pIndices[15] = 1; pIndices[21] = 2; pIndices[27] = 3; pIndices[33] = 4;
    pIndices[4] = 2; pIndices[10] = 7; pIndices[16] = 4; pIndices[22] = 5; pIndices[28] = 6; pIndices[34] = 6;
    pIndices[5] = 3; pIndices[11] = 3; pIndices[17] = 0; pIndices[23] = 1; pIndices[29] = 2; pIndices[35] = 7;

    // Unmap the buffers
    pPositionBuffer->GetBuffer()->Unmap();
    pColourBuffer->GetBuffer()->Unmap();
    pTexcoordBuffer->GetBuffer()->Unmap();
    pIndexBuffer->GetBuffer()->Unmap();

    // Add buffers to the geometry
    pGeometry->AddVertexBuffer(pPositionBuffer);
    pGeometry->AddVertexBuffer(pColourBuffer);
    pGeometry->AddVertexBuffer(pTexcoordBuffer);
    pGeometry->SetIndexBuffer(pIndexBuffer);
  }

  return true;
}

void SceneViewPanel::OnUpdate()
{
  m_camera.Update();
  m_camera.width = (float)ContentAreaSize().x;
  m_camera.height = (float)ContentAreaSize().y;

  pMaterial->SetValue("albedo0", Math::Vec4F((float)abs(ctSin(clock() / 1000.0)), (float)abs(ctCos(clock() / 1000.0)), 0, 1));
  pMaterial->Apply();

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

  pGeometry->Bind();
  pProgram->Bind();

  Window* pWindow = GetGUI()->GetMainWindow();
  API* pGraphics = GetGUI()->GetGraphicsAPI();

  // Draw to the first window
  Mat4F projection = m_camera.ProjectionMatrix() * m_camera.ViewMatrix();

  pMaterial->Bind();
  pState->SetViewport(0, 0, m_target->GetWidth(), m_target->GetHeight());

  class RenderVisitor : public flEngine::Scene::Visitor<flEngine::Scene::Node>
  {
  public:
    RenderVisitor(Mat4F projection, Ref<Program> pProgram, Ref<VertexArray> pVertArray, API* pAPI)
      : m_projection(projection)
      , m_pProgram(pProgram)
      , m_pGraphics(pAPI)
      , m_pVertArray(pVertArray)
    {}

    bool OnEnter(flEngine::Scene::Node* pNode) override {
      if (pNode == pNode->GetScene()->GetRootNode())
        return true;

      flEngine::Scene::Transform* pTransform = pNode->GetComponent<flEngine::Scene::Transform>();

      if (pTransform)
      {
        Mat4F mvp = m_projection * (Mat4F)pTransform->GetTransform();
        m_pProgram->SetMat4("mvp", mvp);
        m_pGraphics->Render(DrawMode_Triangles, true, 0, m_pVertArray->GetIndexCount());
      }

      return true;
    }

    Mat4F m_projection;
    Ref<Program> m_pProgram;
    Ref<VertexArray> m_pVertArray;
    API* m_pGraphics;
  };

  flEngine::Scene::SceneGraph* pScene = Application::Get().GetSubSystem<SceneSystem>()->ActiveScene();
  RenderVisitor renderVisitor(projection, pProgram, pGeometry, pGraphics);

  pScene->Traverse(&renderVisitor, nullptr);
}

void SceneViewPanel::OnGUI()
{
  if (m_target != nullptr)
    GUI::Widgets::Image(m_target->GetColourTarget(), ContentAreaSize().x, ContentAreaSize().y);
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
  if (m_pKeyboard->GetKeyDown(KC_A)) velocity.x -= 1;
  if (m_pKeyboard->GetKeyDown(KC_D)) velocity.x += 1;
  if (m_pKeyboard->GetKeyDown(KC_W)) velocity.z -= 1;
  if (m_pKeyboard->GetKeyDown(KC_S)) velocity.z += 1;
  if (m_pKeyboard->GetKeyDown(KC_E)) velocity.y += 1;
  if (m_pKeyboard->GetKeyDown(KC_Q)) velocity.y -= 1;

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
