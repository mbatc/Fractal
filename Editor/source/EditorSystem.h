#ifndef EditorSystem_h__
#define EditorSystem_h__

#include "flSubSystem.h"

class EditorSystem : public flEngine::SubSystem
{
public:
  EditorSystem() {}

  int64_t m_selectedNode;
};

#endif // EditorSystem_h__
