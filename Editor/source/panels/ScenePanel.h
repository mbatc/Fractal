#pragma once

#include "flEngine.h"
#include "EditorModule.h"

class ScenePanel : public Fractal::Panel
{
public:
  ScenePanel(Fractal::GUIModule* pGUI);

  virtual void OnGUI() override;

private:
  Fractal::SceneManager *m_pSceneManager = nullptr;
};
