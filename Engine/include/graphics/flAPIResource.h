#ifndef flAPIResource_h__
#define flAPIResource_h__

#include "../flInterface.h"

namespace flEngine
{
  namespace Graphics
  {
    class API;

    class flPIMPL_CLASS(APIResource);

    class flEXPORT APIResource : public Interface
    {
      friend API;

      flPIMPL_DEF(APIResource);
    public:
      APIResource(API *pAPI);

      API * GetAPI();
    };
  }
}

#endif // flAPIResource_h__
