#ifndef fl_Graphics_GLDeviceState_h__
#define fl_Graphics_GLDeviceState_h__

#include "graphics/flDeviceState.h"

namespace flEngine
{
  namespace Graphics
  {
    class flPIMPL_CLASS(GLDeviceState);

    class flEXPORT GLDeviceState : public DeviceState
    {
      flPIMPL_DEF(GLDeviceState);

    public:
      static GLDeviceState* Create();

      bool GetFeatureEnabled(flIN DeviceFeature feature) override;
      void SetFeatureEnabled(flIN DeviceFeature feature, flIN bool enabled) override;

      void SetViewport(flIN int64_t x, flIN int64_t y, flIN int64_t width, flIN int64_t height) override;
      void GetViewport(flOUT int64_t *pX = nullptr, flOUT int64_t *pY = nullptr, flOUT int64_t *pWidth = nullptr, flOUT int64_t *pHeight = nullptr) override;

      void SetScissorRect(flIN int64_t x, flIN int64_t y, flIN int64_t width, flIN int64_t height) override;
      void GetScissorRect(flOUT int64_t *pX = nullptr, flOUT int64_t *pY = nullptr, flOUT int64_t *pWidth = nullptr, flOUT int64_t *pHeight = nullptr) override;

      void SetDepthRange(flIN float minDepth, flIN float maxDepth) override;
      void GetDepthRange(flOUT float *pMinDepth, flOUT float *pMaxDepth) override;
    };
  }
}

#endif // flGLDeviceState_h__
