#include "scene/flTransform.h"
#include "ctVector.h"

using namespace flEngine::Math;

namespace flEngine
{
  namespace Scene
  {
    class Impl_Transform
    {
    public:
      Vec3D position;
      Vec3D scale;
      QuatD orientation;

      Transform * pParent;
      ctVector<Ref<Transform>> children;

      Mat4D transform;
      Mat4D localTransform;
    };

    flPIMPL_IMPL(Transform);

    Math::Mat4D Transform::GetTransform()
    {
      return Impl()->transform;
    }

    Math::Vec3D Transform::GetPosition()
    {

    }

    Math::Vec3D Transform::GetScale()
    {

    }

    Math::QuatD Transform::GetOrientation()
    {

    }

    void Transform::SetTransform(Math::Mat4D transform)
    {

    }

    void Transform::SetPosition(Math::Vec3D pos)
    {

    }

    void Transform::SetScale(Math::Vec3D scale)
    {

    }

    void Transform::SetOrientation(Math::QuatD quat)
    {

    }

    Math::Mat4D Transform::GetLocalTransform()
    {

    }

    Math::Vec3D Transform::GetLocalPosition()
    {

    }

    Math::Vec3D Transform::GetLocalScale()
    {

    }

    Math::QuatD Transform::GetLocalOrientation()
    {

    }

    void Transform::SetLocalTransform(Math::Mat4D transform)
    {

    }

    void Transform::SetLocalPosition(Math::Vec3D pos)
    {

    }

    void Transform::SetLocalScale(Math::Vec3D scale)
    {

    }

    void Transform::SetLocalOrientation(Math::QuatD quat)
    {

    }

    void Transform::_SetParent(Transform * pParent)
    {
      if (Impl()->pParent)
      {
        Impl_Transform * pParentImpl = Impl()->pParent->Impl();
        for (int64_t i = 0; i < pParentImpl->children.size(); ++i)
          if (pParentImpl->children[i] == this)
          {
            pParentImpl->children.erase(i);
            break;
          }
      }

      if (pParent)
      {
        Impl()->pParent = pParent;
        Impl()->pParent->Impl()->children.push_back(MakeRef(this, true));
      }
      else
      {
        Impl()->pParent = nullptr;
      }
    }

    Transform* Transform::_GetParent()
    {
      return Impl()->pParent;
    }
  }
}

