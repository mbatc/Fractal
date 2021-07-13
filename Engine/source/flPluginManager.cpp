#include "flPluginManager.h"

namespace Fractal
{
  typedef void(*PluginEvent)();

  enum PluginInterface
  {
    PluginInterface_Startup,
    PluginInterface_Shutdown,
    PluginInterface_OnUpdate,
    PluginInterface_OnRender,
    PluginInterface_OnPreUpdate,
    PluginInterface_OnPreRender,
    PluginInterface_OnPostUpdate,
    PluginInterface_OnPostRender,
    PluginInterface_Count
  };

  class Impl_Plugin
  {
  public:
    PluginEvent m_interface[PluginInterface_Count] = { 0 };
  };

  flPIMPL_IMPL(Plugin);

  class Impl_PluginManager
  {
  public:
  };

  flPIMPL_IMPL(PluginManager);
}
