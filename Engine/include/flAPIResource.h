#pragma once

#include "flInterface.h"

namespace Fractal
{
  class API;

  class Impl_APIResource;

  class flEXPORT APIResource : public Interface
  {
    friend API;

    flPIMPL_DEF(APIResource);
  public:
    APIResource(API* pAPI);

    API* GetAPI();
  };
}
