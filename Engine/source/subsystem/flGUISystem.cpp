#include "subsystem/flGUISystem.h"
#include "platform/flWindow.h"
#include "input/flKeyboard.h"

#include "graphics/flAPI.h"
#include "graphics/flTexture.h"
#include "graphics/flTexture2D.h"
#include "graphics/flVertexArray.h"
#include "graphics/flVertexBuffer.h"
#include "graphics/flIndexBuffer.h"
#include "graphics/flProgram.h"
#include "graphics/flHardwareBuffer.h"
#include "graphics/flMaterial.h"
#include "graphics/flDeviceState.h"
#include "graphics/flWindowRenderTarget.h"
#include "util/flType.h"

#include "input/flMouse.h"
#include "gui/flPanel.h"
#include "math/flMath.h"
#include "flApplication.h"
#include "flRef.h"

#include "ctVector.h"

#include "imgui/imgui.h"

#include <time.h>
#include <chrono>

using namespace flEngine::Input;
using namespace flEngine::Graphics;
using namespace flEngine::Platform;

static char const *_vertSrc = R"(
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

static char const *_fragSrc = R"(
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

namespace flEngine
{
  namespace GUI
  {
    class Impl_GUISystem
    {
    public:
      void Construct(GUISystem *pSelf)
      {
        m_pSelf    = pSelf;
        m_pContext = ImGui::CreateContext();

        m_pKeyboard = pSelf->GetKeyboard();
        m_pMouse    = pSelf->GetMouse();

        // Setup back-end capabilities flags
        ImGuiIO &io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;         // We can honor GetMouseCursor() values (optional)
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;          // We can honor io.WantSetMousePos requests (optional, rarely used)
        io.BackendPlatformName = "Fractal Engine";

        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        // Keyboard mapping. ImGui will use those indices to peek into the io.KeysDown[] array that we will update during the application lifetime.
        io.KeyMap[ImGuiKey_Tab] = Input::KC_Tab;
        io.KeyMap[ImGuiKey_LeftArrow] = Input::KC_Left;
        io.KeyMap[ImGuiKey_RightArrow] = Input::KC_Right;
        io.KeyMap[ImGuiKey_UpArrow] = Input::KC_Up;
        io.KeyMap[ImGuiKey_DownArrow] = Input::KC_Down;
        io.KeyMap[ImGuiKey_PageUp] = Input::KC_PageUp;
        io.KeyMap[ImGuiKey_PageDown] = Input::KC_PageDown;
        io.KeyMap[ImGuiKey_Home] = Input::KC_Home;
        io.KeyMap[ImGuiKey_End] = Input::KC_End;
        io.KeyMap[ImGuiKey_Insert] = Input::KC_Insert;
        io.KeyMap[ImGuiKey_Delete] = Input::KC_Delete;
        io.KeyMap[ImGuiKey_Backspace] = Input::KC_Backspace;
        io.KeyMap[ImGuiKey_Space] = Input::KC_Space;
        io.KeyMap[ImGuiKey_Enter] = Input::KC_Return;
        io.KeyMap[ImGuiKey_Escape] = Input::KC_Escape;
        io.KeyMap[ImGuiKey_A] = Input::KC_A;
        io.KeyMap[ImGuiKey_C] = Input::KC_C;
        io.KeyMap[ImGuiKey_V] = Input::KC_V;
        io.KeyMap[ImGuiKey_X] = Input::KC_X;
        io.KeyMap[ImGuiKey_Y] = Input::KC_Y;
        io.KeyMap[ImGuiKey_Z] = Input::KC_Z;

        API *pGraphics = Application::Get().GetGraphicsAPI();
        m_indexBuffer  = MakeRef(pGraphics->CreateIndexBuffer(0, 0,   BufferUsage_Dynamic), false);
        m_vertexBuffer = MakeRef(pGraphics->CreateVertexBuffer(0, 0, BufferUsage_Dynamic), false);
        m_vertexArray  = MakeRef(pGraphics->CreateVertexArray(), false);

        ImDrawVert vert;
        m_vertexBuffer->SetLayout({
          { "position0", Util::Type_Float32, 2 },
          { "texcoord0", Util::Type_Float32, 2 },
          { "colour0",   Util::Type_UInt8,   4, true }
          });

        m_vertexArray->AddVertexBuffer(m_vertexBuffer);
        m_vertexArray->SetIndexBuffer(m_indexBuffer);

        io.Fonts->AddFontDefault();
        io.Fonts->Build();

        uint8_t *pPixels = nullptr;
        int w, h, bpp;
        io.Fonts->GetTexDataAsRGBA32(&pPixels, &w, &h, &bpp);
        Texture2D *pTex = pGraphics->CreateTexture2D();
        PixelBufferDesc desc;
        CreatePixelBufferDesc(&desc, PixelFormat_RGBA, PixelComponentType_UNorm8, w, h);
        pTex->Set(pPixels, &desc);
        io.Fonts->SetTexID((ImTextureID)pTex);

        m_fontTexture = MakeRef(pTex, false);

        m_shader = MakeRef(pGraphics->CreateProgram(), false);
        m_shader->SetShader(_vertSrc, ProgramStage_Vertex);
        m_shader->SetShader(_fragSrc, ProgramStage_Fragment);
        m_shader->Compile();

        m_pSelf->OnEvent(Platform::E_Kbd_ASCII, &Impl_GUISystem::OnInputChar);
      }
      
      void BeginFrame()
      {
        ImGuiIO &io = ImGui::GetIO();
        IM_ASSERT(io.Fonts->IsBuilt() && "Font atlas not built! It is generally built by the renderer back-end. Missing call to renderer _NewFrame() function? e.g. ImGui_ImplOpenGL3_NewFrame().");

        // Setup display size (every frame to accommodate for window resizing)
        Platform::Window *pWindow = Application::Get().GetMainWindow();
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
        ImGuiIO &io = ImGui::GetIO();

        // Read keyboard modifiers inputs
        io.KeyCtrl  = m_pKeyboard->GetKeyDown(KC_Control);
        io.KeyShift = m_pKeyboard->GetKeyDown(KC_Shift);
        io.KeyAlt   = m_pKeyboard->GetKeyDown(KC_Alt);
        io.KeySuper = false;
      }

      void UpdateMouse()
      {
        ImGuiIO &io = ImGui::GetIO();

        // Update OS mouse cursor with the cursor requested by imgui
        ImGuiMouseCursor mouse_cursor = io.MouseDrawCursor ? ImGuiMouseCursor_None : ImGui::GetMouseCursor();

        if (m_lastCursor != mouse_cursor)
        {
          m_lastCursor = mouse_cursor;
          UpdateMouseCursor();
        }

        io.MousePos.x = m_pMouse->GetPosition().x;
        io.MousePos.y = m_pMouse->GetPosition().y;

        io.MouseWheel  = m_pMouse->GetScrollV();
        io.MouseWheelH = m_pMouse->GetScrollH();
      }

      void UpdateMouseCursor()
      {
        // TODO: change to correct mouse cursor
      }

      void UpdateDrawBuffers(ImDrawData *pDrawData)
      {
        m_vertexBuffer->GetBuffer()->Resize(sizeof(ImDrawVert) * pDrawData->TotalVtxCount, true);
        m_indexBuffer->GetBuffer()->Resize(sizeof(ImDrawVert) * pDrawData->TotalIdxCount, true);

        if (m_vertexBuffer->GetVertexCount() == 0) return;
        if (m_indexBuffer->GetIndexCount() == 0)   return;

        ImDrawVert *pVertexData = (ImDrawVert*)m_vertexBuffer->GetBuffer()->Map(Graphics::AccessFlag_Write);
        ImDrawIdx  *pIndexData = (ImDrawIdx*)m_indexBuffer->GetBuffer()->Map(Graphics::AccessFlag_Write);

        // Concat all vertex buffers into a single array
        int64_t vertexOffset = 0;
        int64_t indexOffset  = 0;
        for (int i = 0; i < pDrawData->CmdListsCount; ++i)
        {
          ImDrawList *pDrawList = pDrawData->CmdLists[i];
          for (int const &idx : pDrawList->IdxBuffer)
            *(pIndexData++) = ImDrawIdx(idx + vertexOffset);

          int vtxCount = pDrawList->VtxBuffer.size();
          memcpy(pVertexData + vertexOffset, pDrawList->VtxBuffer.begin(), vtxCount * sizeof(ImDrawVert));
          vertexOffset += vtxCount;
        }

        m_vertexBuffer->GetBuffer()->Unmap();
        m_indexBuffer->GetBuffer()->Unmap();
      }

      bool OnKeyState(Platform::Event *pEvent)
      {
        ImGui::GetIO().KeysDown[pEvent->kbdState.keyCode] = pEvent->kbdState.isDown;

        return !ImGui::GetIO().WantCaptureKeyboard;
      }

      bool OnMouseState(Platform::Event *pEvent)
      {
        ImGui::GetIO().MouseDown[pEvent->mseState.button] = pEvent->mseState.isDown;

        return !ImGui::GetIO().WantCaptureMouse;
      } 

      bool OnInputChar(Platform::Event* pEvent)
      {
        ImGui::GetIO().AddInputCharacter(pEvent->kbdASCII.character);

        return !ImGui::GetIO().WantTextInput;
      }

      Input::Keyboard *m_pKeyboard;
      Input::Mouse    *m_pMouse;

      ImGuiContext *m_pContext = 0;
      ImGuiMouseCursor m_lastCursor = ImGuiMouseCursor_Arrow;
      ctVector<Ref<Panel>> m_panels;

      Ref<VertexBuffer> m_vertexBuffer;
      Ref<IndexBuffer>  m_indexBuffer;
      Ref<VertexArray>  m_vertexArray;
      Ref<Program>      m_shader;
      Ref<Material>     m_material;
      Ref<Texture2D>    m_fontTexture;

      ctVector<ImDrawVert> m_vertexData;
      ctVector<ImDrawIdx>  m_indexData;

      GUISystem *m_pSelf = nullptr;

      std::chrono::steady_clock::time_point m_lastTime = std::chrono::steady_clock::now();
    };

    flPIMPL_IMPL(GUISystem);

    GUISystem::GUISystem()
    {
      Impl()->Construct(this);
    }

    void GUISystem::OnUpdate()
    {
      for (Ref<Panel> &panel : Impl()->m_panels)
        panel->OnUpdate();

      Impl()->BeginFrame();

      Math::Vec2F windowSize = { GetMainWindow()->GetWidth(), GetMainWindow()->GetHeight() };

      ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);

      ImGui::Begin("DockspaceWindow", 0,
        ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize| 
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_MenuBar
      );

      ImGui::BeginMenuBar();
      if (ImGui::BeginMenu("File"))
        ImGui::EndMenu();
      ImGui::EndMenuBar();

      ImGui::SetWindowPos(ImVec2(0, 0));
      ImGui::SetWindowSize(ImVec2(windowSize.x, windowSize.y));

      ImGuiID id = ImGui::GetID("MainDockspace");
      ImGui::DockSpace(id);

      for (Ref<Panel> &panel : Impl()->m_panels)
        panel->Update();

      ImGui::End();
      ImGui::PopStyleVar(1);
      Impl()->EndFrame();
    }

    void GUISystem::OnRender()
    {
      for (Ref<Panel> &panel : Impl()->m_panels)
        panel->OnRender();

      GetMainWindow()->GetRenderTarget()->Bind();

      ImDrawData *pDrawData = ImGui::GetDrawData();

      Math::Mat4F projection = Math::Mat4F::Ortho(
        pDrawData->DisplayPos.x,
        pDrawData->DisplayPos.x + pDrawData->DisplaySize.x,
        pDrawData->DisplayPos.y,
        pDrawData->DisplayPos.y + pDrawData->DisplaySize.y,
        -1.0f, 1.0f
      );

      API *pGraphics = Application::Get().GetGraphicsAPI();
      Window *pWindow = Application::Get().GetMainWindow();

      DeviceState *pState = pGraphics->GetState();
      pState->SetFeatureEnabled(Graphics::DeviceFeature_StencilTest, true);
      pState->SetFeatureEnabled(Graphics::DeviceFeature_ScissorTest, true);
      pState->SetFeatureEnabled(Graphics::DeviceFeature_DepthTest, false);
      pState->SetFeatureEnabled(Graphics::DeviceFeature_Blend, true);
      pState->SetViewport(0, 0, pWindow->GetWidth(), pWindow->GetHeight());

      // Bind and update program
      Ref<Program> pProgram = Impl()->m_shader;
      pProgram->Bind();
      pProgram->SetMat4("projection", projection.Transpose());
      pProgram->SetInt("mainTexture", 0);

      Impl()->UpdateDrawBuffers(pDrawData);

      // Bind geometry
      Impl()->m_vertexArray->Bind();

      ImVec2 displaySize = ImGui::GetIO().DisplaySize;

      int64_t elementOffset = 0;
      for (int i = 0; i < pDrawData->CmdListsCount; ++i)
      {
        ImDrawList *pCmdList = pDrawData->CmdLists[i];
        for (ImDrawCmd const &cmd : pCmdList->CmdBuffer)
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

          pProgram->SetTexture(0, (Graphics::Texture *)cmd.TextureId);
          pGraphics->Render(Graphics::DrawMode_Triangles, true, elementOffset, cmd.ElemCount);
          elementOffset += cmd.ElemCount;
        }
      }

      pState->SetFeatureEnabled(Graphics::DeviceFeature_ScissorTest, false);
      pGraphics->GetState()->SetFeatureEnabled(Graphics::DeviceFeature_Blend, false);
      pGraphics->GetState()->SetFeatureEnabled(Graphics::DeviceFeature_DepthTest, true);
      pGraphics->GetState()->SetFeatureEnabled(Graphics::DeviceFeature_StencilTest, false);
    }

    bool GUISystem::OnStartup()
    {
      bool success = true;
      for (Ref<Panel> &panel : Impl()->m_panels)
        success &= panel->OnStartup();
      return success;
    }

    void GUISystem::OnShutdown()
    {
      for (Ref<Panel> &panel : Impl()->m_panels)
        panel->OnShutdown();
    }

    void GUISystem::OnPreUpdate()
    {
      for (Ref<Panel> &panel : Impl()->m_panels)
        panel->OnPreUpdate();
    }

    void GUISystem::OnPreRender()
    {
      for (Ref<Panel> &panel : Impl()->m_panels)
        panel->OnPreRender();
    }

    void GUISystem::OnPostUpdate()
    {
      for (Ref<Panel> &panel : Impl()->m_panels)
        panel->OnPostUpdate();
    }

    void GUISystem::OnPostRender()
    {
      for (Ref<Panel> &panel : Impl()->m_panels)
        panel->OnPostRender();
    }

    bool GUISystem::OnKeyState(Platform::Event * pEvent)
    {
      SubSystem::OnKeyState(pEvent);

      return Impl()->OnKeyState(pEvent);
    }

    bool GUISystem::OnMouseState(Platform::Event * pEvent)
    {
      SubSystem::OnMouseState(pEvent);

      return Impl()->OnMouseState(pEvent);
    }

    bool GUISystem::OnMouseScroll(Platform::Event * pEvent)
    {
      SubSystem::OnMouseScroll(pEvent);

      return !ImGui::GetIO().WantCaptureMouse;
    }

    void GUISystem::Open(Panel *pPanel)
    {
      Impl()->m_panels.push_back(MakeRef(pPanel, true));
    }
  }
}

