#ifndef flEngine_h__
#define flEngine_h__

// Fractal Engine public API for dynamic linking
//
// To expose functionality in the engine, a pure virtual interface
// should be created in the relevant namespace. This interface should
// export a Create() function that returns a pointer to the interface
// implementation.

#include "utility/flMath.h"
#include "utility/flUtil_AABB.h"
#include "utility/flUtil_OBB.h"
#include "utility/flUtil_Rect.h"

#include "graphics/flGraphics.h"

#include "project/flProject.h"

#include "scene/flScene.h"
#include "scene/flScene_Node.h"
#include "scene/flScene_Component.h"

#include "ui/flUI.h"
#include "ui/flUI_Button.h"
#include "ui/flUI_TextBox.h"
#include "ui/flUI_Checkbox.h"
#include "ui/flUI_ComboBox.h"
#include "ui/flUI_Component.h"


#endif // flEngine_h__
