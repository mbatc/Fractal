#include "graphics/OpenGL/flGLDeviceState.h"
#include <GL/glew.h>
#include <GL/GL.h>

namespace flEngine
{
  namespace Graphics
  {
    class Impl_GLDeviceState
    {
    public:
      bool GetFeatureEnabled(DeviceFeature feature)
      {
        GLenum glFeature = GL_NONE;
        switch (feature)
        {
        case DF_Blend:       glFeature = GL_BLEND;        break;
        case DF_DepthTest:   glFeature = GL_DEPTH_TEST;   break;
        case DF_StencilTest: glFeature = GL_STENCIL_TEST; break;
        }

        GLboolean value;
        glGetBooleanv(glFeature, &value);
        return value > 0;
      }

      void SetFeatureEnabled(DeviceFeature feature, bool enabled)
      {
        GLenum glFeature = GL_NONE;
        switch (feature)
        {
        case DF_Blend:       glFeature = GL_BLEND;        break;
        case DF_DepthTest:   glFeature = GL_DEPTH_TEST;   break;
        case DF_StencilTest: glFeature = GL_STENCIL_TEST; break;
        }

        if (glFeature == GL_NONE)
          return;

        // Enable/Disable the feature
        if (enabled) glEnable(glFeature);
        else         glDisable(glFeature);
      }

      void SetViewport(int64_t x, int64_t y, int64_t width, int64_t height)
      {
        glViewport((GLint)x, (GLint)y, (GLsizei)width, (GLsizei)height);
      }

      void GetViewport(int64_t *pX, int64_t *pY, int64_t *pWidth, int64_t *pHeight)
      {
        GLint vp[4] = { 0 };
        glGetIntegerv(GL_VIEWPORT, vp);
        *pX = vp[0];
        *pY = vp[1];
        *pWidth = vp[2];
        *pHeight = vp[3];
      }

      void SetScissorRect(int64_t x, int64_t y, int64_t width, int64_t height)
      {
        glScissor((GLint)x, (GLint)y, (GLsizei)width, (GLsizei)height);
      }

      void GetScissorRect(int64_t *pX, int64_t *pY, int64_t *pWidth, int64_t *pHeight)
      {
        GLint vp[4] = { 0 };
        glGetIntegerv(GL_SCISSOR_BOX, vp);
        *pX = vp[0];
        *pY = vp[1];
        *pWidth = vp[2];
        *pHeight = vp[3];
      }

      void SetDepthRange(float minDepth, float maxDepth)
      {
        glDepthRange(minDepth, maxDepth);
      }

      void GetDepthRange(float *pMinDepth, float *pMaxDepth)
      {
        float range[2];
        glGetFloatv(GL_DEPTH_RANGE, range);
        *pMinDepth = range[0];
        *pMaxDepth = range[1];
      }

    };
  }
}

using namespace flEngine;
using namespace flEngine::Graphics;

flPIMPL_IMPL(GLDeviceState);
#define flIMPL flPIMPL(GLDeviceState)

GLDeviceState* GLDeviceState::Create()
{
  return flNew GLDeviceState;
}

bool GLDeviceState::GetFeatureEnabled(flIN DeviceFeature feature)
{
  return flIMPL->GetFeatureEnabled(feature);
}

void GLDeviceState::SetFeatureEnabled(flIN DeviceFeature feature, flIN bool enabled)
{
  flIMPL->SetFeatureEnabled(feature, enabled);
}

void GLDeviceState::SetViewport(flIN int64_t x, flIN int64_t y, flIN int64_t width, flIN int64_t height)
{
  flIMPL->SetViewport(x, y, width, height);
}

void GLDeviceState::GetViewport(flOUT int64_t *pX, flOUT int64_t *pY, flOUT int64_t *pWidth, flOUT int64_t *pHeight)
{
  flIMPL->GetViewport(pX, pY, pWidth, pHeight);
}

void GLDeviceState::SetScissorRect(flIN int64_t x, flIN int64_t y, flIN int64_t width, flIN int64_t height)
{
  flIMPL->SetScissorRect(x, y, width, height);
}

void GLDeviceState::GetScissorRect(flOUT int64_t *pX, flOUT int64_t *pY, flOUT int64_t *pWidth, flOUT int64_t *pHeight)
{
  flIMPL->GetScissorRect(pX, pY, pWidth, pHeight);
}

void GLDeviceState::SetDepthRange(flIN float minDepth, flIN float maxDepth)
{
  flIMPL->SetDepthRange(minDepth, maxDepth);
}

void GLDeviceState::GetDepthRange(flOUT float *pMinDepth, flOUT float *pMaxDepth)
{
  flIMPL->GetDepthRange(pMinDepth, pMaxDepth);
}
