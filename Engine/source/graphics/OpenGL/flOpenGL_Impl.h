#ifndef fl_Graphics_OpenGL_Impl_h__
#define fl_Graphics_OpenGL_Impl_h__

#include "graphics/OpenGL/flOpenGL.h"

namespace flEngine
{
  namespace Graphics
  {
    class GLDeviceState;

    class Impl_OpenGL
    {
    public:
      void Construct(Platform::Window *pWindow, const RenderTargetOptions *pOptions);

      void SetGeometry(Geometry *pGeometry);
      void SetRenderTarget(RenderTarget *pRenderTarget);
      void SetProgram(Program *pProgram);

      DeviceState* GetState();

      void Render();

    protected:
      GLDeviceState *m_pState = nullptr;

      // Active bindings
      Program      *m_pProgram      = nullptr;
      Geometry     *m_pGeometry     = nullptr;
      RenderTarget *m_pRenderTarget = nullptr;

#if flUSING(flPLATFORM_WINDOWS)
      void *m_pGLRC = nullptr;
#endif
    };
  }
}

#endif // fl_Graphics_API_h__
