#pragma once

#include "flHardwareBuffer.h"
#include "flAPIResource.h"

namespace Fractal
{
  class flEXPORT UniformBuffer : public APIResource
  {
  protected:
    UniformBuffer(API* pAPI);

  public:
    virtual void Bind(flIN int64_t index) = 0;
    virtual void Unbind() = 0;

    virtual HardwareBuffer* GetBuffer() = 0;
    virtual HardwareBuffer const* GetBuffer() const = 0;
  };
}
