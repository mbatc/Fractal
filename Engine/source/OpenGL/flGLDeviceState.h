#pragma once

#include "flDeviceState.h"

namespace Fractal
{
    class GLDeviceState : public DeviceState
    {
      GLDeviceState();
    public:

      static GLDeviceState* Create();

      bool GetFeatureEnabled(DeviceFeature feature) override;
      void SetFeatureEnabled(DeviceFeature feature, bool enabled) override;

      void SetViewport(int64_t x, int64_t y, int64_t width, int64_t height) override;
      void GetViewport(int64_t *pX = nullptr, int64_t *pY = nullptr, int64_t *pWidth = nullptr, int64_t *pHeight = nullptr) override;

      void SetScissorRect(int64_t x, int64_t y, int64_t width, int64_t height) override;
      void GetScissorRect(int64_t *pX = nullptr, int64_t *pY = nullptr, int64_t *pWidth = nullptr, int64_t *pHeight = nullptr) override;

      void SetDepthRange(float minDepth, float maxDepth) override;
      void GetDepthRange(float *pMinDepth, float *pMaxDepth) override;
    };
}
