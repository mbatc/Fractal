#include "flEngine.h"
#include "flEntryPoint.h"
#include <stdio.h>

using namespace flEngine;
using namespace flEngine::Platform;
using namespace flEngine::Util;
using namespace flEngine::Threads;
using namespace flEngine::Math;

class EditorApplication : public flEngine::Application
{
public:
  Window* pWindow = nullptr;
  Window* pWindow2 = nullptr;

  Ref<Graphics::API> pGraphics;
  Ref<Graphics::DeviceState> pState;
  Ref<Graphics::Program> pProgram;
  Ref<Graphics::Texture2D> pTexture;
  Ref<Graphics::Sampler> pSampler;
  Ref<Graphics::VertexArray> pGeometry;
  Ref<Graphics::WindowRenderTarget> pFirstTarget;
  Ref<Graphics::WindowRenderTarget> pSecondTarget;
  Ref<Graphics::Material> pMaterial;

  virtual bool OnStartup() override
  {
    // Create a window
    pWindow  = flNew Window("Window 1", Window::Flag_Visible, Window::DM_Windowed);
    pWindow2 = flNew Window("Window 2", Window::Flag_Visible, Window::DM_Windowed);

    pGraphics = MakeRef(Graphics::API::Create("OpenGL", pWindow), false);
    pState    = MakeRef(pGraphics->GetState(), true);

    pFirstTarget  = MakeRef(pWindow->GetRenderTarget(), true);
    pSecondTarget = MakeRef(pGraphics->CreateWindowRenderTarget(pWindow2, nullptr), false);

    pProgram = MakeRef(pGraphics->CreateProgram(), false);
    pProgram->SetShaderFromFile("../../Engine/assets/shader-library/textured.frag",  Graphics::ProgramStage_Fragment);
    pProgram->SetShaderFromFile("../../Engine/assets/shader-library/transform.vert", Graphics::ProgramStage_Vertex);
    pProgram->Compile();

    pTexture = MakeRef(pGraphics->CreateTexture2D(Graphics::PixelFormat_RGBA, Graphics::PixelComponentType_UNorm8), false);
    // Image image("C:/Users/mickb/Pictures/test.jpg");
    Image image("../../Engine/assets/texture-library/albedo/test0.jpg");
    pTexture->SetFromImage(&image);
    pTexture->GenerateMipMaps();

    pMaterial = MakeRef(pGraphics->CreateMaterial(pProgram), false);
    pMaterial->SetTexture("texture0", pTexture);
    pMaterial->SetValue("albedo0", Vec4F(1, 0, 0, 1));
    pMaterial->Apply();

    pSampler = MakeRef(pGraphics->CreateSampler(), false);
    pSampler->SetWrapMode(Graphics::WrapMode_Mirror);
    pSampler->SetFilterMinMode(Graphics::FilterMode_Linear, true);

    pGeometry = MakeRef(pGraphics->CreateVertexArray(), false);

    // Construct a simple cube
    {
      // Create vertex and index buffers
      Ref<Graphics::VertexBuffer> pPositionBuffer = MakeRef(pGraphics->CreateVertexBuffer(sizeof(float) * 3 * 8, nullptr), false);
      Ref<Graphics::VertexBuffer> pColourBuffer   = MakeRef(pGraphics->CreateVertexBuffer(sizeof(float) * 4 * 8, nullptr), false);
      Ref<Graphics::VertexBuffer> pTexcoordBuffer = MakeRef(pGraphics->CreateVertexBuffer(sizeof(float) * 2 * 8, nullptr), false);
      Ref<Graphics::IndexBuffer>  pIndexBuffer    = MakeRef(pGraphics->CreateIndexBuffer(36), false);

      // Map buffers to client memory
      Math::Vec3F* pPositions = (Math::Vec3F*)pPositionBuffer->GetBuffer()->Map(Graphics::AccessFlag_Write);
      Math::Vec4F* pColours   = (Math::Vec4F*)pColourBuffer->GetBuffer()->Map(Graphics::AccessFlag_Write);
      Math::Vec2F* pTexcoords = (Math::Vec2F*)pTexcoordBuffer->GetBuffer()->Map(Graphics::AccessFlag_Write);
      uint32_t*    pIndices   = (uint32_t*)pIndexBuffer->GetBuffer()->Map(Graphics::AccessFlag_Write);
      pPositionBuffer->SetLayout({ { "position0", Util::Type_Float32, 3 } });
      pColourBuffer->SetLayout  ({ { "colour0",   Util::Type_Float32, 4 } });
      pTexcoordBuffer->SetLayout({ { "texcoord0", Util::Type_Float32, 2 } });

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

  virtual void OnPreUpdate()
  {
  }

  virtual void OnPostUpdate()
  {
    pMaterial->SetValue("albedo0", Vec4F(abs(ctSin(clock() / 1000.0)), abs(ctCos(clock() / 1000.0)), 0, 1));
    pMaterial->Apply();
  }

  virtual void OnPreRender()
  {
    pState->SetFeatureEnabled(Graphics::DeviceFeature_DepthTest, true);

    pGeometry->Bind();
    pProgram->Bind();

    // pProgram->SetTexture("texture0", pTexture);
    // pProgram->SetSampler("texture0", pSampler);

    // Draw to the first window
    Mat4F modelMat   = Mat4F::Translation({ 0, 0, -3 }) * Mat4F::RotationY(clock() / 1000.0f);
    Mat4F projection = Mat4F::Projection(pWindow->GetWidth() / (float)pWindow->GetHeight(), 60.0f * (float)ctPi / 180.0f, 0.01f, 1000.0f);
    Mat4F mvp        = projection * modelMat;

    pFirstTarget->Bind();
    pMaterial->Bind();
    pState->SetViewport(0, 0, pFirstTarget->GetWidth(), pFirstTarget->GetHeight());

    pProgram->SetMat4("mvp", mvp);
    pGraphics->Render(Graphics::DrawMode_Triangles, true, 0, pGeometry->GetIndexCount());

    // Draw to the second window
    modelMat   = Mat4F::Translation({ 0, 0, -4 }) * Mat4F::RotationY(-clock() / 1000.0f);
    projection = Mat4F::Projection(pWindow2->GetWidth() / (float)pWindow2->GetHeight(), 60.0f * (float)ctPi / 180.0f, 0.01f, 1000.0f);
    mvp        = projection * modelMat;

    pSecondTarget->Bind();
    pState->SetViewport(0, 0, pSecondTarget->GetWidth(), pSecondTarget->GetHeight());

    pProgram->SetMat4("mvp", mvp);
    pGraphics->Render(Graphics::DrawMode_Triangles, true, 0, pGeometry->GetIndexCount());
  }

  virtual void OnPostRender()
  {
    pFirstTarget->Swap();
    pFirstTarget->Clear(0xFF000000, 1.0f);

    pSecondTarget->Swap();
    pSecondTarget->Clear(0xFF00FF00, 1.0f);
  }

  virtual bool OnEvent(flIN Platform::Event* pEvent)
  {
    ctUnused(pEvent);
    return true;
  }

  virtual bool IsRunning()
  {
    return !pWindow->ReceivedEvent(E_Wnd_Close) && !pWindow2->ReceivedEvent(E_Wnd_Close);
  }
};

flEngine::Application* flEngine::CreateApplication(char** argv, int argc)
{
  return flNew EditorApplication;
}
