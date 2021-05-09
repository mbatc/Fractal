#ifndef fl_Engine_h__
#define fl_Engine_h__

// Platform
#include "platform/flEvent.h"
#include "platform/flEventQueue.h"
#include "platform/flWindow.h"

// Utility
#include "util/flTask.h"
#include "util/flTaskQueue.h"

// Threading
#include "threads/flThreads.h"
#include "threads/flThreadPool.h"
#include "threads/flThreadQueue.h"

// Math
#include "math/flMath.h"

// User Input
#include "input/flKeyboard.h"
#include "input/flMouse.h"
#include "input/flInputs.h"

// Graphics
#include "graphics/flAPI.h"
#include "graphics/flDeviceState.h"
#include "graphics/flProgram.h"
#include "graphics/flProgramDetails.h"
#include "graphics/flGeometry.h"
#include "graphics/flHardwareBuffer.h"
#include "graphics/flIndexBuffer.h"
#include "graphics/flVertexBuffer.h"
#include "graphics/flUniformBuffer.h"
#include "graphics/flRenderTarget.h"
#include "graphics/flWindowRenderTarget.h"
#include "graphics/flTextureRenderTarget.h"

namespace flEngine
{
  /**
   * @brief Initialize Fractals core systems.
   */
  bool flEXPORT Initialize();
}

#endif // fl_Engine_h__
