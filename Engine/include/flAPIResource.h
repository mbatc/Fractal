#pragma once

#include "flInterface.h"

namespace Fractal
{
  class API;

  class flEXPORT APIResource : public Interface
  {
  public:
    virtual API* GetAPI() const = 0;
  };
}
