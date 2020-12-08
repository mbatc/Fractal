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
      void Construct(flIN Platform::Window *pWindow, flIN RenderTargetOptions *pOptions);
      bool SetFormat(flIN RenderTargetOptions *pOptions);

      Platform::Window* GetWindow() const;

    protected:
      Platform::Window *m_pWindow = nullptr;

#if flUSING(flPLATFORM_WINDOWS)
      void* m_hDC = nullptr;
#endif
    };
  }
}

#endif // fl_Graphics_RenderTarget_h__
