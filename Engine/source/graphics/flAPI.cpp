#include "graphics/flRenderMesh.h"
#include "graphics/flAPI.h"
#include "flRef.h"

#include "ctString.h"

namespace flEngine
{
  namespace Graphics
  {
    static ctVector<Ref<APIFactory>> g_apis;

    static Ref<APIFactory> FindFactory(ctString const &identifier)
    {
      for (Ref<APIFactory> const &factory : g_apis)
        if (identifier.compare(factory->GetIdentifier(), atSCO_None))
          return factory;
      return nullptr;
    }

    bool API::RegisterAPI(flIN APIFactory *pFactory)
    {
      if (FindFactory(pFactory->GetIdentifier()))
        return false;

      g_apis.push_back(MakeRef(pFactory, true));
      return true;
    }

    int64_t API::GetAPICount()
    {
      return g_apis.size();
    }

    char const *API::GetAPIIdentifier(flIN int64_t index)
    {
      return g_apis[index]->GetIdentifier();
    }

    API *API::Create(char const *apiIdentifier, Platform::Window *pWindow, RenderTargetOptions *pOptions)
    {
      Ref<APIFactory> pFactory = FindFactory(apiIdentifier);

      return pFactory ? pFactory->Create(pWindow, pOptions) : nullptr;
    }

    RenderMesh *API::CreateRenderMesh(flIN Mesh *pMesh)
    {
      return RenderMesh::Create(this, pMesh);
    }
  }
}