#ifndef EditorSystem_h__
#define EditorSystem_h__

#include "flModule.h"

class EditorModule : public Fractal::Module
{
public:
  EditorModule() {}

  int64_t m_selectedNode = -1;
};

#endif // EditorSystem_h__
