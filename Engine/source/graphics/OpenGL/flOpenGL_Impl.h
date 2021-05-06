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

      void SetGeometry(Geometry *pGeometry, int64_t indexBuffer);
      void SetRenderTarget(RenderTarget *pRenderTarget);
      void SetProgram(Program *pProgram);

      DeviceState* GetState();

      void Render(DrawMode drawMode, bool indexed, uint64_t elementOffset, uint64_t elementCount);

    protected:
      GLDeviceState *m_pState = nullptr;

      // Active bindings
      Program      *m_pProgram      = nullptr;
      Geometry     *m_pGeometry     = nullptr;
      RenderTarget *m_pRenderTarget = nullptr;
      int64_t       m_indexBuffer   = -1;
#if flUSING(flPLATFORM_WINDOWS)
      void *m_pGLRC = nullptr;
#endif
    };
  }
}

#endif // fl_Graphics_API_h__
