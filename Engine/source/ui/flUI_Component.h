#ifndef flUI_Component_h__
#define flUI_Component_h__

#include "../utility/flMath.h"

namespace flEngine
{
  namespace UI
  {
    class flEXPORT Component
    {
    public:
      virtual void Update() {}
      virtual void Draw() {}

      virtual bool IsHovered() {}
      virtual bool IsPressed() {}
      virtual bool IsReleased() {}

      virtual void SetPosition(const Math::Vec2F &pos) {}
      virtual void SetSize(const Math::Vec2F &pos) {}

      virtual Math::Vec2F GetPosition() {}
      virtual Math::Vec2F GetSize() {}

    protected:
      Math::Vec2F m_position;
      Math::Vec2F m_size;
    };
  };
};

#endif // flUI_h__
