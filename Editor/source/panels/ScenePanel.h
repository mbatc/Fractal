#pragma once

#include "flEngine.h"
#include "EditorSystem.h"
#include "ctVector.h"

class ScenePanel : public flEngine::GUI::Panel
{
public:
  ScenePanel(flEngine::GUI::GUISystem* pGUI);

  virtual void OnGUI() override;

private:
  flEngine::SceneSystem *m_pSceneSystem = nullptr;
};
