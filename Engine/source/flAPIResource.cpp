#include "flAPIResource.h"

namespace Fractal
{
    class Impl_APIResource
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
