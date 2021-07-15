#include "flRenderMesh.h"
#include "flAPI.h"
#include "flRef.h"

#include "ctString.h"

namespace Fractal
{
  namespace Impl
  {
    static ctVector<Ref<APIFactory>> g_apis;

    static Ref<APIFactory> FindFactory(ctString const& identifier)
    {
      for (Ref<APIFactory> const& factory : g_apis)
        if (identifier.compare(factory->GetIdentifier(), atSCO_None))
          return factory;
      return nullptr;
    }

    extern "C" {
      bool Fractal_RegisterAPI(flIN APIFactory* pFactory)
      {
        if (FindFactory(pFactory->GetIdentifier()))
          return false;

        g_apis.push_back(MakeRef(pFactory, true));
        return true;
      }

      int64_t Fractal_GetAPICount()
      {
        return g_apis.size();
      }

      char const* Fractal_GetAPIIdentifier(flIN int64_t index)
      {
        return g_apis[index]->GetIdentifier();
      }

      API* Fractal_CreateAPI(char const* apiIdentifier, Window* pWindow, RenderTargetOptions* pOptions = nullptr)
      {
        Ref<APIFactory> pFactory = FindFactory(apiIdentifier);

        return pFactory ? pFactory->Create(pWindow, pOptions) : nullptr;
      }
    }
  }
}
