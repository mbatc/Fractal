#ifndef fl_Engine_h__
#define fl_Engine_h__

// Platform
#include "platform/flEvent.h"
#include "platform/flEventQueue.h"
#include "platform/flWindow.h"

// Utility
#include "util/flTask.h"
#include "util/flTaskQueue.h"
#include "util/flImage.h"
#include "util/flColour.h"
#include "util/flType.h"
#include "flRef.h"

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
#include "graphics/flVertexArray.h"
#include "graphics/flHardwareBuffer.h"
#include "graphics/flIndexBuffer.h"
#include "graphics/flVertexBuffer.h"
#include "graphics/flUniformBuffer.h"
#include "graphics/flRenderTarget.h"
#include "graphics/flWindowRenderTarget.h"
#include "graphics/flTextureRenderTarget.h"
#include "graphics/flTexture.h"
#include "graphics/flTexture2D.h"
#include "graphics/flSampler.h"
#include "graphics/flMaterial.h"

// Application
#include "flApplication.h"

#endif // fl_Engine_h__
