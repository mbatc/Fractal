#include "graphics/flAPIResource.h"

namespace flEngine
{
  namespace Graphics
  {
    class flPIMPL_CLASS(APIResource)
    {
    public:
      API *m_pAPI = nullptr;
    };

    flPIMPL_IMPL(APIResource);

    APIResource::APIResource(API *pAPI)
    {
      Impl()->m_pAPI = pAPI;
    }

    API *APIResource::GetAPI()
    {
      return Impl()->m_pAPI;
    }
  }
}
