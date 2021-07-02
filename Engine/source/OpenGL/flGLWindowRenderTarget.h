#pragma once

#include "flWindowRenderTarget.h"
#include "flWindow.h"

namespace Fractal
{
  class PixelBuffer;

  class GLWindowRenderTarget : public WindowRenderTarget
  {
  protected:
    GLWindowRenderTarget(API* pAPI, flIN Window* pWindow, flIN const RenderTargetOptions* pOptions);

  public:
    ~GLWindowRenderTarget();

    static WindowRenderTarget* Create(API* pAPI, flIN Window* pWindow, flIN const RenderTargetOptions* pOptions);

    Window* GetWindow() const override;
    bool SetFormat(flIN RenderTargetOptions const* pOptions) override;

    int64_t GetWidth() const override;
    int64_t GetHeight() const override;

    void Clear(flIN Colour colour = 0, flIN float depth = 1, flIN int32_t stencil = 0) override;
    void ClearDepth(flIN float depth = 1.0f) override;
    void ClearColour(flIN Colour colour = 0) override;
    void ClearStencil(flIN int32_t colour = 0) override;
    void Swap() override;
    void Bind(bool read, bool draw) override;
    void* GetNativeResource() const override;

  private:
    void MakeCurrent();

    Window* m_pWindow = nullptr;

#if flUSING(flPLATFORM_WINDOWS)
    void* m_hDC = nullptr;
    bool m_pixelFormatSet = false;
    RenderTargetOptions m_currentOptions;
#endif
  };
}
