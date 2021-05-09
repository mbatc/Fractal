#include "flEngine.h"
#include <stdio.h>

using namespace flEngine;
using namespace flEngine::Platform;
using namespace flEngine::Util;
using namespace flEngine::Threads;
using namespace flEngine::Math;

int main(char **argv, int argc)
{
  flEngine::Initialize();

  // Create a window
  Window window("Has Inputs", Window::Flag_Visible, Window::DM_Windowed);
  Window window2("Has Inputs", Window::Flag_Visible, Window::DM_Windowed);
  
  Graphics::API *pGraphics = Graphics::API::Create("OpenGL", &window);
  Graphics::DeviceState* pState = pGraphics->GetState();

  Graphics::WindowRenderTarget *pFirstTarget = window.GetRenderTarget();
  Graphics::WindowRenderTarget *pSecondTarget = pGraphics->CreateWindowRenderTarget(&window2, nullptr);

  Graphics::Program *pProgram = pGraphics->CreateProgram();
  pProgram->SetShaderFromFile("../../Engine/assets/shader-library/textured.frag", Graphics::ProgramStage_Fragment);
  pProgram->SetShaderFromFile("../../Engine/assets/shader-library/transform.vert", Graphics::ProgramStage_Vertex);

  Graphics::Texture2D *pTexture = pGraphics->CreateTexture2D(Graphics::PixelFormat_RGBA, Graphics::PixelComponentType_UInt8);
  // Image image("C:/Users/mickb/Pictures/test.jpg");
  Image image("../../Engine/assets/texture-library/albedo/test0.jpg");
  pTexture->SetFromImage(&image);

  Graphics::Texture2D *pTexture2 = pGraphics->CreateTexture2D(Graphics::PixelFormat_RGBA, Graphics::PixelComponentType_UInt8);
  // Image image("C:/Users/mickb/Pictures/test.jpg");
  Image image2("../../Engine/assets/texture-library/albedo/test1.jpg");
  pTexture2->SetFromImage(&image2);

  pTexture->GenerateMipMaps();
  pTexture2->GenerateMipMaps();

  Graphics::Geometry* pGeometry = pGraphics->CreateGeometry();
  // Construct a simple cube
  {
    // Create vertex and index buffers
    Graphics::VertexBuffer* pPositionBuffer = pGraphics->CreateVertexBuffer(Type_Float32, 3, 8, nullptr);
    Graphics::VertexBuffer* pColourBuffer   = pGraphics->CreateVertexBuffer(Type_Float32, 4, 8, nullptr);
    Graphics::VertexBuffer* pTexcoordBuffer = pGraphics->CreateVertexBuffer(Type_Float32, 2, 8, nullptr);
    Graphics::IndexBuffer*  pIndexBuffer    = pGraphics->CreateIndexBuffer(36);

    // Map buffers to client memory
    Math::Vec3F* pPositions = (Math::Vec3F*)pPositionBuffer->GetBuffer()->Map(Graphics::AccessFlag_Write);
    Math::Vec4F* pColours   = (Math::Vec4F*)pColourBuffer->GetBuffer()->Map(Graphics::AccessFlag_Write);
    Math::Vec2F* pTexcoords = (Math::Vec2F*)pTexcoordBuffer->GetBuffer()->Map(Graphics::AccessFlag_Write);
    uint32_t* pIndices      = (uint32_t*)pIndexBuffer->GetBuffer()->Map(Graphics::AccessFlag_Write);

    // Set vertex data
    pPositions[0] = { -1, -1, -1 };  pColours[0] = { 1, 0, 0, 1 }; pTexcoords[0] = {0, 0};
    pPositions[1] = { -1, -1,  1 };  pColours[1] = { 0, 1, 0, 1 }; pTexcoords[1] = {1, 0};
    pPositions[2] = {  1, -1,  1 };  pColours[2] = { 0, 0, 1, 1 }; pTexcoords[2] = {1, 1};
    pPositions[3] = {  1, -1, -1 };  pColours[3] = { 1, 0, 0, 1 }; pTexcoords[3] = {0, 1};
    pPositions[4] = { -1,  1, -1 };  pColours[4] = { 0, 1, 0, 1 }; pTexcoords[4] = {1, 1};
    pPositions[5] = { -1,  1,  1 };  pColours[5] = { 0, 0, 1, 1 }; pTexcoords[5] = {0, 1};
    pPositions[6] = {  1,  1,  1 };  pColours[6] = { 1, 0, 0, 1 }; pTexcoords[6] = {0, 0};
    pPositions[7] = {  1,  1, -1 };  pColours[7] = { 0, 1, 0, 1 }; pTexcoords[7] = {1, 0};

    // Set index data
    // Bottom        // Front         // Left          // Back          // Right         // Top
    pIndices[0] = 0; pIndices[6]  = 0; pIndices[12] = 1; pIndices[18] = 2; pIndices[24] = 3; pIndices[30] = 4;
    pIndices[1] = 1; pIndices[7]  = 4; pIndices[13] = 5; pIndices[19] = 6; pIndices[25] = 7; pIndices[31] = 5;
    pIndices[2] = 2; pIndices[8]  = 7; pIndices[14] = 4; pIndices[20] = 5; pIndices[26] = 6; pIndices[32] = 6;
    pIndices[3] = 0; pIndices[9]  = 0; pIndices[15] = 1; pIndices[21] = 2; pIndices[27] = 3; pIndices[33] = 4;
    pIndices[4] = 2; pIndices[10] = 7; pIndices[16] = 4; pIndices[22] = 5; pIndices[28] = 6; pIndices[34] = 6;
    pIndices[5] = 3; pIndices[11] = 3; pIndices[17] = 0; pIndices[23] = 1; pIndices[29] = 2; pIndices[35] = 7;

    // Unmap the buffers
    pPositionBuffer->GetBuffer()->Unmap();
    pColourBuffer->GetBuffer()->Unmap();
    pTexcoordBuffer->GetBuffer()->Unmap();
    pIndexBuffer->GetBuffer()->Unmap();

    // Add buffers to the geometry
    pGeometry->AddVertexBuffer("position0", pPositionBuffer);
    pGeometry->AddVertexBuffer("colour0", pColourBuffer);
    pGeometry->AddVertexBuffer("texcoord0", pTexcoordBuffer);
    pGeometry->AddIndexBuffer(pIndexBuffer);

    // Release buffers
    pPositionBuffer->DecRef();
    pColourBuffer->DecRef();
    pIndexBuffer->DecRef();
  }

  printf("Shader Inputs: \n");

  for (int64_t i = 0; i < pProgram->GetUniformCount(); ++i)
    printf("  Uniform: %s\n", pProgram->GetUniformName(i));

  for (int64_t i = 0; i < pProgram->GetUniformBufferCount(); ++i)
    printf("  Uniform Buffer: %s\n", pProgram->GetUniformBufferName(i));

  for (int64_t i = 0; i < pProgram->GetTextureCount(); ++i)
    printf("  Sampler: %s\n", pProgram->GetTextureName(i));

  for (int64_t i = 0; i < pProgram->GetAttributeCount(); ++i)
    printf("  Attribute: %s\n", pProgram->GetAttributeName(i));

  // Get window input interfaces
  Input::Mouse    *pMouse    = window.GetMouse();
  Input::Keyboard *pKeyboard = window.GetKeyboard();

  Input::Mouse    globalMouse;
  Input::Keyboard globalKbd;
  
  pState->SetFeatureEnabled(Graphics::DeviceFeature_DepthTest, true);

  while (!window.ReceivedEvent(E_Wnd_Close)) // Check if the window has requested a close
  {
    Inputs::Update(); // Push input events

    Mat4F modelMat = Mat4F::Translation({0, 0, -3}) * Mat4F::RotationY(clock() / 1000.0f);
    Mat4F projection = Mat4F::Projection(window.GetWidth() / (float)window.GetHeight(), 60.0f * (float)ctPi / 180.0f, 0.01f, 1000.0f);
    Math::Mat4F mvp = projection * modelMat;

    pGraphics->SetGeometry(pGeometry);
    pGraphics->SetProgram(pProgram);

    // Draw to the first window
    pFirstTarget->Clear(0xFF000000, 1.0f);
    pGraphics->SetRenderTarget(pFirstTarget);
    pState->SetViewport(0, 0, pFirstTarget->GetWidth(), pFirstTarget->GetHeight());

    pProgram->SetUniform("mvp", &mvp, Type_Float32, 16);
    pProgram->SetTexture("texture0", pTexture);
    pProgram->SetTexture("texture1", pTexture2);

    pGraphics->Render(Graphics::DrawMode_Triangles, true);
    pFirstTarget->Swap();

    // Draw to the second window
    modelMat = Mat4F::Translation({ 0, 0, -4 }) * Mat4F::RotationY(-clock() / 1000.0f);
    projection = Mat4F::Projection(window2.GetWidth() / (float)window2.GetHeight(), 60.0f * (float)ctPi / 180.0f, 0.01f, 1000.0f);
    mvp = projection * modelMat;

    pSecondTarget->Clear(0xFF00FF00, 1.0f);
    pGraphics->SetRenderTarget(pSecondTarget);
    pState->SetViewport(0, 0, pSecondTarget->GetWidth(), pSecondTarget->GetHeight());
    pProgram->SetUniform("mvp", &mvp, Type_Float32, 16);
    
    pGraphics->Render(Graphics::DrawMode_Triangles, true);
    pSecondTarget->Swap();
  }

  return 0;
}
