#include "graphics/OpenGL/flGLDeviceState.h"
#include <GL/glew.h>
#include <GL/GL.h>

namespace flEngine
{
  namespace Graphics
  {
    GLDeviceState *GLDeviceState::Create()
    {
      return flNew GLDeviceState;
    }

    bool GLDeviceState::GetFeatureEnabled(DeviceFeature feature)
    {
      GLenum glFeature = GL_NONE;
      switch (feature)
      {
      case DeviceFeature_Blend:       glFeature = GL_BLEND;        break;
      case DeviceFeature_DepthTest:   glFeature = GL_DEPTH_TEST;   break;
      case DeviceFeature_StencilTest: glFeature = GL_STENCIL_TEST; break;
      }

      GLboolean value;
      glGetBooleanv(glFeature, &value);
      return value > 0;
    }

    void GLDeviceState::SetFeatureEnabled(DeviceFeature feature, bool enabled)
    {
      GLenum glFeature = GL_NONE;
      switch (feature)
      {
      case DeviceFeature_Blend:       glFeature = GL_BLEND;        break;
      case DeviceFeature_DepthTest:   glFeature = GL_DEPTH_TEST;   break;
      case DeviceFeature_StencilTest: glFeature = GL_STENCIL_TEST; break;
      }

      if (glFeature == GL_NONE)
        return;

      // Enable/Disable the feature
      if (enabled) glEnable(glFeature);
      else         glDisable(glFeature);
    }

    void GLDeviceState::SetViewport(int64_t x, int64_t y, int64_t width, int64_t height)
    {
      glViewport((GLint)x, (GLint)y, (GLsizei)width, (GLsizei)height);
    }

    void GLDeviceState::GetViewport(int64_t *pX, int64_t *pY, int64_t *pWidth, int64_t *pHeight)
    {
      GLint vp[4] = { 0 };
      glGetIntegerv(GL_VIEWPORT, vp);
      *pX = vp[0];
      *pY = vp[1];
      *pWidth = vp[2];
      *pHeight = vp[3];
    }

    void GLDeviceState::SetScissorRect(int64_t x, int64_t y, int64_t width, int64_t height)
    {
      glScissor((GLint)x, (GLint)y, (GLsizei)width, (GLsizei)height);
    }

    void GLDeviceState::GetScissorRect(int64_t *pX, int64_t *pY, int64_t *pWidth, int64_t *pHeight)
    {
      GLint vp[4] = { 0 };
      glGetIntegerv(GL_SCISSOR_BOX, vp);
      *pX = vp[0];
      *pY = vp[1];
      *pWidth = vp[2];
      *pHeight = vp[3];
    }

    void GLDeviceState::SetDepthRange(float minDepth, float maxDepth)
    {
      glDepthRange(minDepth, maxDepth);
    }

    void GLDeviceState::GetDepthRange(float *pMinDepth, float *pMaxDepth)
    {
      float range[2];
      glGetFloatv(GL_DEPTH_RANGE, range);
      *pMinDepth = range[0];
      *pMaxDepth = range[1];
    }
  }
}
