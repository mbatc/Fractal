#include "flGUIModule.h"
#include "flWindow.h"
#include "flKeyboard.h"

#include "flAPI.h"
#include "flTexture.h"
#include "flSampler.h"
#include "flTexture2D.h"
#include "flVertexArray.h"
#include "flVertexBuffer.h"
#include "flIndexBuffer.h"
#include "flProgram.h"
#include "flHardwareBuffer.h"
#include "flShaderMaterial.h"
#include "flDeviceState.h"
#include "flWindowRenderTarget.h"
#include "flType.h"

#include "flMouse.h"
#include "flPanel.h"
#include "flMath.h"
#include "flApplication.h"
#include "flRef.h"
#include "flGUIStyle.h"

#include "ctHashMap.h"
#include "ctString.h"

#include "imgui/imgui.h"

#include <time.h>
#include <chrono>
#include "flLog.h"
#include "..\include\flGUIModule.h"

static char const* _vertSrc = R"(
#version 330

in layout(location = 0) vec2 position0;
in layout(location = 1) vec2 texcoord0;
in layout(location = 2) vec4 colour0;

uniform mat4 projection;

out vec2 vs_texcoord0;
out vec4 vs_colour0;

void main()
{
  vs_colour0   = colour0;
  vs_texcoord0 = texcoord0;
  gl_Position  = projection * vec4(position0, 0, 1);
}

)";

static char const* _fragSrc = R"(
#version 330

in vec2 vs_texcoord0;
in vec4 vs_colour0;

uniform sampler2D mainTexture;

out vec4 fragColour0;

void main()
{
  fragColour0 = vs_colour0 * textureLod(mainTexture, vs_texcoord0, 0);
}

)";

namespace Fractal
{
  class Impl_GUIModule
  {
  public:
    struct Menu
    {
      ctHashMap<ctString, Menu> menus;
      ctHashMap<ctString, GUIModule::MenuCommandFunc> commands;
    };

    void Construct(GUIModule* pSelf)
    {
      m_pStyleSheet = MakeRef<GUIStyleSheet>();

      m_pSelf = pSelf;
      m_pContext = ImGui::CreateContext();

      m_pKeyboard = pSelf->GetKeyboard();
      m_pMouse = pSelf->GetMouse();

      // Setup back-end capabilities flags
      ImGuiIO& io = ImGui::GetIO();
      io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;         // We can honor GetMouseCursor() values (optional)
      io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;          // We can honor io.WantSetMousePos requests (optional, rarely used)
      io.BackendPlatformName = "Fractal Engine";

      io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

      // Keyboard mapping. ImGui will use those indices to peek into the io.KeysDown[] array that we will update during the application lifetime.
      io.KeyMap[ImGuiKey_Tab] = KC_Tab;
      io.KeyMap[ImGuiKey_LeftArrow] = KC_Left;
      io.KeyMap[ImGuiKey_RightArrow] = KC_Right;
      io.KeyMap[ImGuiKey_UpArrow] = KC_Up;
      io.KeyMap[ImGuiKey_DownArrow] = KC_Down;
      io.KeyMap[ImGuiKey_PageUp] = KC_PageUp;
      io.KeyMap[ImGuiKey_PageDown] = KC_PageDown;
      io.KeyMap[ImGuiKey_Home] = KC_Home;
      io.KeyMap[ImGuiKey_End] = KC_End;
      io.KeyMap[ImGuiKey_Insert] = KC_Insert;
      io.KeyMap[ImGuiKey_Delete] = KC_Delete;
      io.KeyMap[ImGuiKey_Backspace] = KC_Backspace;
      io.KeyMap[ImGuiKey_Space] = KC_Space;
      io.KeyMap[ImGuiKey_Enter] = KC_Return;
      io.KeyMap[ImGuiKey_Escape] = KC_Escape;
      io.KeyMap[ImGuiKey_A] = KC_A;
      io.KeyMap[ImGuiKey_C] = KC_C;
      io.KeyMap[ImGuiKey_V] = KC_V;
      io.KeyMap[ImGuiKey_X] = KC_X;
      io.KeyMap[ImGuiKey_Y] = KC_Y;
      io.KeyMap[ImGuiKey_Z] = KC_Z;

      API* pGraphics = Application::Get().GetGraphicsAPI();
      m_indexBuffer = MakeRef(pGraphics->CreateIndexBuffer(0, 0, BufferUsage_Dynamic), false);
      m_vertexBuffer = MakeRef(pGraphics->CreateVertexBuffer(0, 0, BufferUsage_Dynamic), false);
      m_vertexArray = MakeRef(pGraphics->CreateVertexArray(), false);

      ImDrawVert vert;
      m_vertexBuffer->SetLayout({
        { 0, Type_Float32, 2 },
        { 1, Type_Float32, 2 },
        { 2, Type_UInt8,   4, true }
        });

      m_vertexArray->AddVertexBuffer(m_vertexBuffer);
      m_vertexArray->SetIndexBuffer(m_indexBuffer);

      ImFontConfig config;
      config.OversampleH = 1;
      config.OversampleV = 1;
      io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/segoeui.ttf", 16, 0, 0);
      io.Fonts->Build();

      uint8_t* pPixels = nullptr;
      int w, h, bpp;
      io.Fonts->GetTexDataAsRGBA32(&pPixels, &w, &h, &bpp);
      Texture2D* pTex = pGraphics->CreateTexture2D();
      PixelBufferDesc desc;
      CreatePixelBufferDesc(&desc, PixelFormat_RGBA, PixelComponentType_UNorm8, w, h);
      pTex->Set(pPixels, &desc);
      io.Fonts->SetTexID((ImTextureID)pTex);

      m_fontTexture = MakeRef(pTex, false);


      m_pShader = MakeRef(pGraphics->CreateProgram(), false);
      m_pShader->SetShader(_vertSrc, ProgramStage_Vertex);
      m_pShader->SetShader(_fragSrc, ProgramStage_Fragment);
      m_pShader->Compile();

      m_pSampler = MakeRef(pGraphics->CreateSampler(), false);
      m_pSampler->SetFilterMinMode(FilterMode_Linear, false);
      m_pSampler->SetFilterMagMode(FilterMode_Nearest);

      m_pSelf->OnEvent(E_Kbd_ASCII, &Impl_GUIModule::OnInputChar);
    }

    void BeginFrame()
    {
      ImGuiIO& io = ImGui::GetIO();
      IM_ASSERT(io.Fonts->IsBuilt() && "Font atlas not built! It is generally built by the renderer back-end. Missing call to renderer _NewFrame() function? e.g. ImGui_ImplOpenGL3_NewFrame().");

      // Setup display size (every frame to accommodate for window resizing)
      Window* pWindow = Application::Get().GetMainWindow();
      io.DisplaySize = ImVec2((float)pWindow->GetWidth(), (float)pWindow->GetHeight());

      // Setup time step
      auto currentTime = std::chrono::steady_clock::now();
      io.DeltaTime = (float)(currentTime - m_lastTime).count() / 1000000000ll;
      m_lastTime = currentTime;

      UpdateKeyboard();
      UpdateMouse();

      // Update game controllers (if enabled and available)
      // UpdateGamepads();

      ImGui::NewFrame();
    }

    void EndFrame()
    {
      ImGui::Render();
    }

    void UpdateKeyboard()
    {
      ImGuiIO& io = ImGui::GetIO();

      // Read keyboard modifiers inputs
      io.KeyCtrl = m_pKeyboard->GetKeyDown(KC_Control);
      io.KeyShift = m_pKeyboard->GetKeyDown(KC_Shift);
      io.KeyAlt = m_pKeyboard->GetKeyDown(KC_Alt);
      io.KeySuper = false;
    }

    void UpdateMouse()
    {
      ImGuiIO& io = ImGui::GetIO();

      // Update OS mouse cursor with the cursor requested by imgui
      ImGuiMouseCursor mouse_cursor = io.MouseDrawCursor ? ImGuiMouseCursor_None : ImGui::GetMouseCursor();

      if (m_lastCursor != mouse_cursor)
      {
        m_lastCursor = mouse_cursor;
        UpdateMouseCursor();
      }

      io.MousePos.x = m_pMouse->GetPosition().x;
      io.MousePos.y = m_pMouse->GetPosition().y;

      io.MouseWheel = m_pMouse->GetScrollV();
      io.MouseWheelH = m_pMouse->GetScrollH();
    }

    void UpdateMouseCursor()
    {
      // TODO: change to correct mouse cursor
    }

    void UpdateDrawBuffers(ImDrawData* pDrawData)
    {
      m_vertexBuffer->GetBuffer()->Resize(sizeof(ImDrawVert) * pDrawData->TotalVtxCount, true);
      m_indexBuffer->GetBuffer()->Resize(sizeof(ImDrawIdx) * pDrawData->TotalIdxCount, true);

      if (m_vertexBuffer->GetVertexCount() == 0) return;
      if (m_indexBuffer->GetIndexCount() == 0)   return;

      ImDrawVert* pVertexData = (ImDrawVert*)m_vertexBuffer->GetBuffer()->Map(AccessFlag_Write);
      ImDrawIdx* pIndexData = (ImDrawIdx*)m_indexBuffer->GetBuffer()->Map(AccessFlag_Write);

      // Concat all vertex buffers into a single array
      int64_t vertexOffset = 0;
      int64_t indexOffset = 0;
      for (int i = 0; i < pDrawData->CmdListsCount; ++i)
      {
        ImDrawList* pDrawList = pDrawData->CmdLists[i];
        for (int const& idx : pDrawList->IdxBuffer)
          *(pIndexData++) = ImDrawIdx(idx + vertexOffset);

        int vtxCount = pDrawList->VtxBuffer.size();
        memcpy(pVertexData + vertexOffset, pDrawList->VtxBuffer.begin(), vtxCount * sizeof(ImDrawVert));
        vertexOffset += vtxCount;
      }

      m_vertexBuffer->GetBuffer()->Unmap();
      m_indexBuffer->GetBuffer()->Unmap();
    }

    bool OnKeyState(Event* pEvent)
    {
      ImGui::GetIO().KeysDown[pEvent->kbdState.keyCode] = pEvent->kbdState.isDown;

      return !ImGui::GetIO().WantCaptureKeyboard;
    }

    bool OnMouseState(Event* pEvent)
    {
      ImGui::GetIO().MouseDown[pEvent->mseState.button] = pEvent->mseState.isDown;

      return !ImGui::GetIO().WantCaptureMouse;
    }

    bool OnInputChar(Event* pEvent)
    {
      ImGui::GetIO().AddInputCharacter(pEvent->kbdASCII.character);

      return !ImGui::GetIO().WantTextInput;
    }

    void DrawMenu(ctString const& name, Menu* pMenu)
    {
      if (ImGui::BeginMenu(name.c_str()))
      {
        // Draw commands
        for (auto& kvp : pMenu->commands)
          if (ImGui::MenuItem(kvp.m_key.c_str()))
            kvp.m_val();

        // Draw the sub menus
        for (auto& kvp : pMenu->menus)
          DrawMenu(name, &kvp.m_val);
        ImGui::EndMenu();
      }
    }

    Keyboard* m_pKeyboard;
    Mouse* m_pMouse;

    ImGuiContext* m_pContext = 0;
    ImGuiMouseCursor m_lastCursor = ImGuiMouseCursor_Arrow;
    ctVector<Ref<Panel>> m_panels;

    Ref<VertexBuffer> m_vertexBuffer;
    Ref<IndexBuffer>  m_indexBuffer;
    Ref<VertexArray>  m_vertexArray;
    Ref<Program>      m_pShader;
    Ref<Sampler>      m_pSampler;
    Ref<ShaderMaterial> m_material;
    Ref<Texture2D>    m_fontTexture;

    ctVector<ImDrawVert> m_vertexData;
    ctVector<ImDrawIdx>  m_indexData;

    GUIModule* m_pSelf = nullptr;
    Ref<GUIStyleSheet> m_pStyleSheet;

    std::chrono::steady_clock::time_point m_lastTime = std::chrono::steady_clock::now();

    ctHashMap<ctString, Menu> m_menus;
  };

  flPIMPL_IMPL(GUIModule);

  GUIModule::GUIModule()
  {
    Impl()->Construct(this);
  }

  void GUIModule::AddMenuItem(flIN char const* name, flIN MenuCommandFunc func)
  {
    ctVector<ctString> path = ctString::_split(name, '/', true);

    flErrorIf(path.size() < 2, "There must be at least 2 items in the menu command path. (e.g. file/save)");

if (path.size() >= 2)
{
  Impl_GUIModule::Menu* pDest = nullptr;
  for (int64_t i = 0; i < path.size() - 1; ++i)
    pDest = &Impl()->m_menus.GetOrAdd(path[i]);

  if (pDest && !pDest->commands.Contains(path.back()))
    pDest->commands.Add(path.back(), func);
  else
    flError("Menu command '%s' already exists", name);
}
}

GUIStyleSheet* GUIModule::GetStyle()
{
  return Impl()->m_pStyleSheet;
}

GUIStyleSheet const* GUIModule::GetStyle() const
{
  return Impl()->m_pStyleSheet;
}

void GUIModule::OnUpdate()
{
  for (Ref<Panel>& panel : Impl()->m_panels)
    panel->OnUpdate();

  Impl()->BeginFrame();

  Vec2F windowSize = { GetMainWindow()->GetWidth(), GetMainWindow()->GetHeight() };


  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
  {
    GUIStyleScope globalStyle(Impl()->m_pStyleSheet);

    if (ImGui::Begin("MainDockspace", 0,
                     ImGuiWindowFlags_NoBringToFrontOnFocus |
                     ImGuiWindowFlags_NoMove |
                     ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoTitleBar |
                     ImGuiWindowFlags_MenuBar
                    ))
    {

      if (ImGui::BeginMenuBar())
      {
        for (auto& menu : Impl()->m_menus)
          Impl()->DrawMenu(menu.m_key, &menu.m_val);
        ImGui::EndMenuBar();
      }

      ImGuiID id = ImGui::GetID("Dockspace");
      ImGui::DockSpace(id);

      ImGui::SetWindowPos(ImVec2(0, 0));
      ImGui::SetWindowSize(ImVec2(windowSize.x, windowSize.y));
      for (Ref<Panel>& panel : Impl()->m_panels)
      {
        GUIStyleScope panelStyle(panel->GetStyle());
        panel->Update();
      }
    }
    ImGui::End();
  }
  ImGui::PopStyleVar(1);

  Impl()->EndFrame();
}

void GUIModule::OnRender()
{
  for (Ref<Panel>& panel : Impl()->m_panels)
    panel->OnRender();

  GetMainWindow()->GetRenderTarget()->Bind();

  ImDrawData* pDrawData = ImGui::GetDrawData();

  Mat4F projection = Mat4F::Ortho(
                       pDrawData->DisplayPos.x,
                       pDrawData->DisplayPos.x + pDrawData->DisplaySize.x,
                       pDrawData->DisplayPos.y,
                       pDrawData->DisplayPos.y + pDrawData->DisplaySize.y,
                       -1.0f, 1.0f
                     );

  API* pGraphics = Application::Get().GetGraphicsAPI();
  Window* pWindow = Application::Get().GetMainWindow();

  DeviceState* pState = pGraphics->GetState();
  pState->SetFeatureEnabled(DeviceFeature_StencilTest, true);
  pState->SetFeatureEnabled(DeviceFeature_ScissorTest, true);
  pState->SetFeatureEnabled(DeviceFeature_DepthTest, false);
  pState->SetFeatureEnabled(DeviceFeature_Blend, true);
  pState->SetViewport(0, 0, pWindow->GetWidth(), pWindow->GetHeight());

    // Bind and update program
  Ref<Program> pProgram = Impl()->m_pShader;
  pProgram->Bind();
  pProgram->SetMat4("projection", projection.Transpose());
  pProgram->SetInt("mainTexture", 0);
  pProgram->SetSampler(0, Impl()->m_pSampler);

  Impl()->UpdateDrawBuffers(pDrawData);

  // Bind geometry
  Impl()->m_vertexArray->Bind();

  ImVec2 displaySize = ImGui::GetIO().DisplaySize;

  int64_t elementOffset = 0;
  for (int i = 0; i < pDrawData->CmdListsCount; ++i)
  {
    ImDrawList* pCmdList = pDrawData->CmdLists[i];
    for (ImDrawCmd const& cmd : pCmdList->CmdBuffer)
    {
        ImVec4 glClipRect;
        glClipRect.x = cmd.ClipRect.x;
        glClipRect.y = displaySize.y - cmd.ClipRect.w;
        glClipRect.z = cmd.ClipRect.z - cmd.ClipRect.x;
        glClipRect.w = cmd.ClipRect.w - cmd.ClipRect.y;

        pGraphics->GetState()->SetScissorRect(
          (int64_t)glClipRect.x,
          (int64_t)glClipRect.y,
          (int64_t)glClipRect.z,
          (int64_t)glClipRect.w);

        pProgram->SetTexture(0, (Texture *)cmd.TextureId);
        pGraphics->Render(DrawMode_Triangles, true, elementOffset, cmd.ElemCount);
        elementOffset += cmd.ElemCount;
      }
  }

  pState->SetFeatureEnabled(DeviceFeature_ScissorTest, false);
  pState->SetFeatureEnabled(DeviceFeature_Blend, false);
  pState->SetFeatureEnabled(DeviceFeature_DepthTest, true);
  pState->SetFeatureEnabled(DeviceFeature_StencilTest, false);

  // Unbind the vertex array
  Impl()->m_vertexArray->Unbind();
}

bool GUIModule::OnStartup()
{
  bool success = true;
  for (Ref<Panel>& panel : Impl()->m_panels)
    success &= panel->OnStartup();
  return success;
}

void GUIModule::OnShutdown()
{
  for (Ref<Panel>& panel : Impl()->m_panels)
    panel->OnShutdown();
}

void GUIModule::OnPreUpdate()
{
  for (Ref<Panel>& panel : Impl()->m_panels)
    panel->OnPreUpdate();
}

void GUIModule::OnPreRender()
{
  for (Ref<Panel>& panel : Impl()->m_panels)
    panel->OnPreRender();
}

void GUIModule::OnPostUpdate()
{
  for (Ref<Panel>& panel : Impl()->m_panels)
    panel->OnPostUpdate();
}

void GUIModule::OnPostRender()
{
  for (Ref<Panel>& panel : Impl()->m_panels)
    panel->OnPostRender();
}

bool GUIModule::OnKeyState(Event* pEvent)
{
  Module::OnKeyState(pEvent);

  return Impl()->OnKeyState(pEvent);
}

bool GUIModule::OnMouseState(Event* pEvent)
{
  Module::OnMouseState(pEvent);

  return Impl()->OnMouseState(pEvent);
}

bool GUIModule::OnMouseScroll(Event* pEvent)
{
  Module::OnMouseScroll(pEvent);

  return !ImGui::GetIO().WantCaptureMouse;
}

void GUIModule::Open(Panel* pPanel)
{
  Impl()->m_panels.push_back(MakeRef(pPanel, true));
}
}

