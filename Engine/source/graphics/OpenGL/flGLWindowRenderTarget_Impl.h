#ifndef fl_Graphics_GLWindowRenderTarget_Impl_h__
#define fl_Graphics_GLWindowRenderTarget_Impl_h__

#include "graphics/OpenGL/flGLWindowRenderTarget.h"

namespace flEngine
{
  namespace Graphics
  {
    class PixelBuffer;

    class Impl_GLWindowRenderTarget : public WindowRenderTarget
    {
    public:
      ~Impl_GLWindowRenderTarget();

      void Construct(flIN Platform::Window *pWindow, flIN const RenderTargetOptions *pOptions);
      bool SetFormat(flIN const RenderTargetOptions *pOptions);

      Platform::Window* GetWindow() const;

      void Clear(flIN const Util::Colour &colour, flIN const float &depth, flIN const int32_t &stencil);
      void ClearDepth(flIN const float &depth);
      void ClearColour(flIN const Util::Colour &colour);
      void ClearStencil(flIN const int32_t &stencil);
      void Swap();
      void Bind();

      void* GetNativeHandle() const;

    protected:
      void MakeCurrent();

      Platform::Window *m_pWindow = nullptr;

#if flUSING(flPLATFORM_WINDOWS)
      void* m_hDC = nullptr;
      bool m_pixelFormatSet = false;
      RenderTargetOptions m_currentOptions;
#endif
    };
  }
}

#endif // fl_Graphics_RenderTarget_h__
