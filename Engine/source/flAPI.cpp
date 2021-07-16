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

  }
}

extern "C" {
  bool Fractal_RegisterAPI(flIN Fractal::APIFactory* pFactory)
  {
    if (Fractal::Impl::FindFactory(pFactory->GetIdentifier()))
      return false;

    Fractal::Impl::g_apis.push_back(MakeRef(pFactory, true));
    return true;
  }

  int64_t Fractal_GetAPICount()
  {
    return Fractal::Impl::g_apis.size();
  }

  char const* Fractal_GetAPIIdentifier(flIN int64_t index)
  {
    return Fractal::Impl::g_apis[index]->GetIdentifier();
  }

  Fractal::API* Fractal_CreateAPI(char const* apiIdentifier, Fractal::IWindow* pWindow, Fractal::RenderTargetOptions* pOptions = nullptr)
  {
    Fractal::Ref<Fractal::APIFactory> pFactory = Fractal::Impl::FindFactory(apiIdentifier);

    return pFactory ? pFactory->Create(pWindow, pOptions) : nullptr;
  }
}