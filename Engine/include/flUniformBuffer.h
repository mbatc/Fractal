#pragma once

#include "flAPIResource.h"

namespace Fractal
{
  class HardwareBuffer;

  class flEXPORT UniformBuffer : public APIResource
  {
  protected:
    UniformBuffer(API* pAPI);

  public:
    /**
     * @brief Bind the uniform buffer to the active Graphics API.
     * 
     * @param [in] index The binding point index to use.
     * @param [in] storageBuffer Bind as a storage buffer instead of a uniform buffer.
     *                           TODO: Refactor binding so that API has Bind*
     *                                 functions which we pass APIResources to.
     *                                 This will eliminate parameters like this
     *                                 and make rendering code more self explanatory.
     */
    virtual void Bind(flIN int64_t index, flIN bool storageBuffer = false) = 0;
    virtual void Unbind() = 0;

    virtual HardwareBuffer* GetBuffer() = 0;
    virtual HardwareBuffer const* GetBuffer() const = 0;
  };
}
