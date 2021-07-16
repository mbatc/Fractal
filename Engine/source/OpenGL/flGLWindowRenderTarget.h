#pragma once

#include "flWindowRenderTarget.h"
#include "flWindow.h"

namespace Fractal
{
  class GLWindowRenderTarget : public WindowRenderTarget
  {
    FRACTAL_DEFAULT_INTERFACE;

  public:
    GLWindowRenderTarget(API* pAPI, flIN IWindow* pWindow, flIN const RenderTargetOptions* pOptions);
    ~GLWindowRenderTarget();

    virtual Window* GetWindow() const override;
    virtual bool SetFormat(flIN RenderTargetOptions const* pOptions) override;

    virtual int64_t GetWidth() const override;
    virtual int64_t GetHeight() const override;

    virtual void Clear(flIN Colour colour = 0, flIN float depth = 1, flIN int32_t stencil = 0) override;
    virtual void ClearDepth(flIN float depth = 1.0f) override;
    virtual void ClearColour(flIN Colour colour = 0) override;
    virtual void ClearStencil(flIN int32_t colour = 0) override;
    virtual void Swap() override;
    virtual void Bind(bool read, bool draw) override;
    virtual void* GetNativeResource() const override;

    virtual API* GetAPI() const override;

  private:
    void MakeCurrent();
    API* m_pAPI;
    IWindow* m_pWindow = nullptr;

#if flUSING(flPLATFORM_WINDOWS)
    void* m_hDC = nullptr;
    bool m_pixelFormatSet = false;
    RenderTargetOptions m_currentOptions;
#endif
  };
}
