#include "SceneViewPanel.h"

#include "ctFile.h"
#include "ctFilename.h"

using namespace Fractal;

SceneViewPanel::SceneViewPanel(GUIModule* pGUI)
  : Panel(pGUI, "Scene View")
  , m_camera(pGUI->GetKeyboard(), pGUI->GetMouse())
{}

bool SceneViewPanel::OnStartup()
{
  API* pGraphics = GetGUI()->GetGraphicsAPI();

  pProgram = MakeRef(pGraphics->CreateProgram(), false);
  pProgram->SetShaderFromFile("../../Engine/assets/shader-library/textured.frag", ProgramStage_Fragment);
  pProgram->SetShaderFromFile("../../Engine/assets/shader-library/transform.vert", ProgramStage_Vertex);
  pProgram->Compile();

  pSampler = MakeRef(pGraphics->CreateSampler(), false);
  pSampler->SetWrapMode(WrapMode_Mirror);
  pSampler->SetFilterMinMode(FilterMode_Linear, true);

  // Construct a simple cube
  {
    // Create vertex and index buffers
    OBJImporter importer;
    importer.Import("C:/Users/mickb/OneDrive/Documents/Test Models/Sponza/sponza.obj");

    Mesh* pMesh = importer.GetResult();
    pMesh->Triangulate();

    pRenderMesh = MakeRef(pGraphics->CreateRenderMesh(pMesh), false);

    for (int64_t matIdx = 0; matIdx < pMesh->GetMaterialCount(); ++matIdx)
    {
      SurfaceMaterial* pMaterialData = pMesh->GetMaterial(matIdx);
      Ref<ShaderMaterial> pShaderMat = MakeRef(pGraphics->CreateMaterial(pProgram), false);
      char const* path = pMaterialData->GetTexture("diffuse");
      if (path != nullptr)
      {
        bool found = false;
        ctFilename fullPath = ctFile::Find(ctString(pMesh->GetSourceDirectory()) + "/" + path, &found);

        if (found)
        {
          Image image(fullPath.c_str());

          Ref<Texture2D> pTexture = MakeRef(pGraphics->CreateTexture2D(PixelFormat_RGBA, PixelComponentType_UNorm8), false);
          pTexture->SetFromImage(&image);
          pTexture->GenerateMipMaps();

          pShaderMat->SetTexture("texture0", pTexture);
        }
      }

      pShaderMat->SetValue("albedo0", pMaterialData->GetColour("diffuse"));
      pShaderMat->Apply();
      materials.push_back(pShaderMat);
    }
  }

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

  pRenderMesh->GetVertexArray()->Bind();
  pProgram->Bind();

  Window* pWindow = GetGUI()->GetMainWindow();
  API* pGraphics = GetGUI()->GetGraphicsAPI();

  // Draw to the first window
  Mat4F projection = m_camera.ProjectionMatrix() * m_camera.ViewMatrix();

  pState->SetViewport(0, 0, m_target->GetWidth(), m_target->GetHeight());

  class RenderVisitor : public Fractal::Visitor<Fractal::Node>
  {
  public:
    RenderVisitor(Mat4F projection, ctVector<Ref<ShaderMaterial>> const& materials, Ref<Program> pProgram, Ref<RenderMesh> pMesh, API* pAPI)
      : m_projection(projection)
      , m_pProgram(pProgram)
      , m_pGraphics(pAPI)
      , m_pRenderMesh(pMesh)
      , m_materials(materials)
    {}

    bool OnEnter(Fractal::Node* pNode) override
    {
      if (pNode == pNode->GetScene()->GetRootNode())
        return true;

      Fractal::Transform* pTransform = pNode->GetComponent<Fractal::Transform>();

      if (pTransform)
      {
        Mat4F mvp = m_projection * (Mat4F)pTransform->GetTransform();
        m_pProgram->SetMat4("mvp", mvp);

        for (int64_t i = 0; i < m_pRenderMesh->GetSubmeshCount(); ++i)
        {
          m_materials[i]->Bind();

          RenderMesh::SubMesh* pSubMesh = m_pRenderMesh->GetSubmesh(i);
          m_pGraphics->Render(DrawMode_Triangles, true, pSubMesh->offset, pSubMesh->count);
        }
      }

      return true;
    }

    Mat4F m_projection;
    Ref<Program> m_pProgram;
    Ref<RenderMesh> m_pRenderMesh;
    ctVector<Ref<ShaderMaterial>> m_materials;
    API* m_pGraphics;
  };

  SceneGraph* pScene = Application::Get().GetModule<SceneManager>()->ActiveScene();
  RenderVisitor renderVisitor(projection, materials, pProgram, pRenderMesh, pGraphics);

  pScene->Traverse(&renderVisitor, nullptr);
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
