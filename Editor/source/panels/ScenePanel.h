#pragma once

#include "flEngine.h"
#include "EditorModule.h"

class ScenePanel : public flEngine::GUI::Panel
{
public:
  ScenePanel(flEngine::GUI::GUIModule* pGUI);

  virtual void OnGUI() override;

private:
  flEngine::SceneManager *m_pSceneManager = nullptr;
};
