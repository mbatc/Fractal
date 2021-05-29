#ifndef EditorCamera_h__
#define EditorCamera_h__

#include "flRef.h"
#include "graphics/flAPI.h"
#include "graphics/flTextureRenderTarget.h"

class EditorCamera
{
public:
  EditorCamera()
  {
    m_renderTarget = MakeRef(Application::Get().GetGraphicsAPI()->CreateTextureRenderTarget(), false);
  }

  Ref<TextureRenderTarget> m_renderTarget;
};

#endif // EditorCamera_h__
