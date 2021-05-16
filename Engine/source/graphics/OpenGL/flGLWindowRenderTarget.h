#ifndef fl_Graphics_GLWindowRenderTarget_h__
#define fl_Graphics_GLWindowRenderTarget_h__

#include "graphics/flWindowRenderTarget.h"
#include "platform/flWindow.h"

namespace flEngine
{
  namespace Graphics
  {
    class PixelBuffer;

    class GLWindowRenderTarget : public WindowRenderTarget
    {
    protected:
      GLWindowRenderTarget(API *pAPI, flIN Platform::Window *pWindow, flIN const RenderTargetOptions *pOptions);

    public:
      ~GLWindowRenderTarget();

      static WindowRenderTarget * Create(API *pAPI, flIN Platform::Window *pWindow, flIN const RenderTargetOptions *pOptions);

      Platform::Window* GetWindow() const override;
      bool SetFormat(flIN RenderTargetOptions const * pOptions) override;

      int64_t GetWidth() const override;
      int64_t GetHeight() const override;

      void Clear(flIN Util::Colour colour = 0, flIN float depth = 1, flIN int32_t stencil = 0) override;
      void ClearDepth(flIN float depth = 1.0f) override;
      void ClearColour(flIN Util::Colour colour = 0) override;
      void ClearStencil(flIN int32_t colour = 0) override;
      void Swap() override;
      void Bind(bool read, bool draw) override;
      void * GetNativeResource() const override;

    private:
      void MakeCurrent();

      Platform::Window *m_pWindow = nullptr;

#if flUSING(flPLATFORM_WINDOWS)
      void *m_hDC = nullptr;
      bool m_pixelFormatSet = false;
      RenderTargetOptions m_currentOptions;
#endif
    };
  }
}

#endif // fl_Graphics_RenderTarget_h__
