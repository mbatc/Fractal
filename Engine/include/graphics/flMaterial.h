#ifndef fl_Graphics_Material_h__
#define fl_Graphics_Material_h__

#include "flInterface.h"
#include "math/flMath.h"

namespace flEngine
{
  namespace Graphics
  {
    class Program;

    class flEXPORT Material : public Interface
    {
    public:
      virtual void Bind() = 0;

      virtual bool SetValue(flIN char const* name, flIN float value) = 0;
      virtual bool SetValue(flIN char const* name, flIN float const * pValues, flIN int64_t componentCount) = 0;
      virtual bool SetTexture(flIN char const * name) = 0;

      inline bool SetValue(char const* name, Math::Vec2F const& value) {
        return SetValue(name, value.begin(), 2);
      }

      inline bool SetValue(char const* name, Math::Vec3F const& value) {
        return SetValue(name, value.begin(), 3);
      }

      inline bool SetValue(char const* name, Math::Vec4F const& value) {
        return SetValue(name, value.begin(), 4);
      }
    };
  }
}


#endif // flMaterial_h__
