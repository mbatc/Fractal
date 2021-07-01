#pragma once

#include "flInterface.h"

namespace Fractal
{
    enum DeviceFeature
    {
      DeviceFeature_DepthTest,
      DeviceFeature_StencilTest,
      DeviceFeature_ScissorTest,
      DeviceFeature_Blend,
      DeviceFeature_Count,
    };

    /**
     * @brief This class defines the interface for the graphics device state.
     */
    class flEXPORT DeviceState : public Interface
    {
    public:
      virtual bool GetFeatureEnabled(flIN DeviceFeature feature) = 0;
      virtual void SetFeatureEnabled(flIN DeviceFeature feature, flIN bool enabled) = 0;

      virtual void SetViewport(flIN int64_t x, flIN int64_t y, flIN int64_t width, flIN int64_t height) = 0;
      virtual void GetViewport(flOUT int64_t *pX = nullptr, flOUT int64_t *pY = nullptr, flOUT int64_t *pWidth = nullptr, flOUT int64_t *pHeight = nullptr) = 0;

      virtual void SetScissorRect(flIN int64_t x, flIN int64_t y, flIN int64_t width, flIN int64_t height) = 0;
      virtual void GetScissorRect(flOUT int64_t *pX = nullptr, flOUT int64_t *pY = nullptr, flOUT int64_t *pWidth = nullptr, flOUT int64_t *pHeight = nullptr) = 0;

      virtual void SetDepthRange(flIN float minDepth, flIN float maxDepth) = 0;
      virtual void GetDepthRange(flOUT float *pMinDepth, flOUT float *pMaxDepth) = 0;
    };
}
