#include "flApplicationBehaviour.h"

namespace flEngine
{
  bool ApplicationBehaviour::OnStartup()    { return true; }
  void ApplicationBehaviour::OnShutdown()   {}
  void ApplicationBehaviour::OnUpdate()     {}
  void ApplicationBehaviour::OnRender()     {}
  void ApplicationBehaviour::OnPreUpdate()  {}
  void ApplicationBehaviour::OnPreRender()  {}
  void ApplicationBehaviour::OnPostUpdate() {}
  void ApplicationBehaviour::OnPostRender() {}
}
