#include "flTransform.h"
#include "ctVector.h"

namespace Fractal
{
  class Impl_Transform
  {
  public:
    // Global transform details
    Vec3D position = Vec3D::zero();
    QuatD orientation = QuatD::Identity();
    Vec3D scale = Vec3D::one();
    Mat4D cachedTransform = Mat4D::Identity();
    Mat4D cachedInverseTransform = Mat4D::Identity();
    bool transformChanged = false;
    bool reEvaluateGlobal = false;
    bool reEvaluateGlobalInverse = false;

    // Local transform details
    Vec3D localPosition = Vec3D::zero();
    QuatD localOrientation = QuatD::Identity();
    Vec3D localScale = Vec3D::one();
    Mat4D cachedLocalTransform = Mat4D::Identity();
    Mat4D cachedInverseLocalTransform = Mat4D::Identity();
    bool reEvaluateLocal = false;
    bool localTransformChanged = false;
    bool reEvaluateLocalInverse = false;

    // Parent transform
    Transform* pParent = nullptr;

    // Children
    ctVector<Ref<Transform>> children;

    template<typename T>
    void SetLocal(T* pCurrent, T const& newValue)
    {
      reEvaluateGlobal |= *pCurrent != newValue;
      *pCurrent = newValue;
    }

    template<typename T>
    void SetGlobal(T* pCurrent, T const& newValue)
    {
      reEvaluateLocal |= *pCurrent != newValue;
      *pCurrent = newValue;
    }

    Mat4D const& GetInverseLocalTransform()
    {
      if (reEvaluateLocalInverse)
      {
        cachedInverseLocalTransform = Evaluated().GetLocalTransform().Inverse();
        reEvaluateLocalInverse = false;
      }

      return Evaluated().cachedInverseLocalTransform;
    }

    Mat4D const& GetInverseTransform()
    {
      if (reEvaluateGlobalInverse)
      {
        cachedInverseTransform = Evaluated().GetTransform().Inverse();
        reEvaluateGlobalInverse = false;
      }

      return Evaluated().cachedInverseTransform;
    }

    Mat4D const& GetLocalTransform()
    {
      if (localTransformChanged)
      {
        // Update the local transformation matrix
        cachedLocalTransform  = Mat4D::Translation(localPosition) * Mat4D::Rotation(localOrientation) * Mat4D::Scale(localScale);
        localTransformChanged = false;
        reEvaluateLocalInverse = true;
      }
      return cachedLocalTransform;
    }

    Mat4D const& GetTransform()
    {
      if (transformChanged)
      {
        // Update the global transformation matrix
        cachedTransform  = Mat4D::Translation(position) * Mat4D::Rotation(orientation) * Mat4D::Scale(scale);
        transformChanged = false;
        reEvaluateGlobalInverse = true;
      }
      return cachedTransform;
    }

    void ReEvaluateGlobal()
    {
      if (!reEvaluateGlobal)
        return;

      if (pParent)
        cachedTransform = pParent->GetTransform() * GetLocalTransform();
      else
        cachedTransform = GetLocalTransform();

      orientation = cachedTransform.GetOrientation();
      position    = cachedTransform.GetTranslation();
      scale       = cachedTransform.GetScale();
      reEvaluateGlobal = false;
    }

    void ReEvaluateLocal()
    {
      if (!reEvaluateLocal)
        return;

      if (pParent)
        cachedLocalTransform = pParent->GetInverseTransform() * GetTransform();
      else
        cachedLocalTransform = GetTransform();

      localOrientation = cachedLocalTransform.GetOrientation();
      localPosition    = cachedLocalTransform.GetTranslation();
      localScale       = cachedLocalTransform.GetScale();
      reEvaluateLocal  = false;
    }

    void SetReEvaluate(bool local)
    {
      if (local && !reEvaluateLocal)
      {
        ReEvaluateGlobal();
        reEvaluateLocal  = true;
      }
      else if (!local && !reEvaluateGlobal)
      {
        ReEvaluateLocal();
        reEvaluateGlobal = true;
      }

      for (Ref<Transform>& c : children)
        c->Impl()->SetReEvaluate(false);
    }

    Impl_Transform& Evaluated()
    {
      ReEvaluateGlobal();
      ReEvaluateLocal();
      return *this;
    }
  };

  flPIMPL_IMPL(Transform);

  Mat4D Transform::GetTransform()
  {
    return Impl()->Evaluated().GetTransform();
  }

  Mat4D Transform::GetInverseTransform()
  {
    return Impl()->Evaluated().GetInverseTransform();
  }

  Vec3D Transform::GetPosition()
  {
    return Impl()->Evaluated().position;
  }

  Vec3D Transform::GetScale()
  {
    return Impl()->Evaluated().scale;
  }

  QuatD Transform::GetOrientation()
  {
    return Impl()->Evaluated().orientation;
  }

  Mat4D Transform::GetLocalTransform()
  {
    return Impl()->Evaluated().GetLocalTransform();
  }

  Mat4D Transform::GetInverseLocalTransform()
  {
    return Impl()->Evaluated().GetInverseLocalTransform();
  }

  Vec3D Transform::GetLocalPosition()
  {
    return Impl()->Evaluated().localPosition;
  }

  Vec3D Transform::GetLocalScale()
  {
    return Impl()->Evaluated().localScale;
  }

  QuatD Transform::GetLocalOrientation()
  {
    return Impl()->Evaluated().localOrientation;
  }

  void Transform::SetTransform(flIN Mat4D transform)
  {
    SetOrientation(transform.GetOrientation());
    SetPosition(transform.GetTranslation());
    SetScale(transform.GetScale());
  }

  void Transform::SetPosition(flIN Vec3D pos)
  {
    Impl()->SetReEvaluate(true);
    Impl()->position = pos;
    Impl()->transformChanged = true;
  }

  void Transform::SetScale(flIN Vec3D scale)
  {
    Impl()->SetReEvaluate(true);
    Impl()->scale = scale;
    Impl()->transformChanged = true;
  }

  void Transform::SetOrientation(flIN QuatD quat)
  {
    Impl()->SetReEvaluate(true);
    Impl()->orientation = quat;
    Impl()->transformChanged = true;
  }

  void Transform::SetLocalTransform(flIN Mat4D transform)
  {
    SetLocalOrientation(transform.GetOrientation());
    SetLocalPosition(transform.GetTranslation());
    SetLocalScale(transform.GetScale());
  }

  void Transform::SetLocalPosition(flIN Vec3D pos)
  {
    Impl()->SetReEvaluate(false);
    Impl()->localPosition         = pos;
    Impl()->localTransformChanged = true;
  }

  void Transform::SetLocalScale(flIN Vec3D scale)
  {
    Impl()->SetReEvaluate(false);
    Impl()->localScale            = scale;
    Impl()->localTransformChanged = true;
  }

  void Transform::SetLocalOrientation(flIN QuatD quat)
  {
    Impl()->SetReEvaluate(false);
    Impl()->localOrientation      = quat;
    Impl()->localTransformChanged = true;
  }

  int64_t Transform::GetChildCount() const
  {
    return Impl()->children.size();
  }

  void Transform::SetParent(flIN Transform* pParent)
  {
    if (Impl()->pParent == pParent)
      return;

    if (Impl()->pParent)
    {
      Impl_Transform* pParentImpl = Impl()->pParent->Impl();
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

    Impl()->SetReEvaluate(false);
  }

  Transform* Transform::GetParent()
  {
    return Impl()->pParent;
  }

  Transform* Transform::GetChild(flIN int64_t index)
  {
    return Impl()->children[index].Get();
  }

  Transform const* Transform::GetParent() const
  {
    return Impl()->pParent;
  }

  Transform const* Transform::GetChild(flIN int64_t index) const
  {
    return Impl()->children[index].Get();
  }

  bool Transform::RemoveChild(flIN int64_t index)
  {
    if (index < 0 || index >= GetChildCount())
      return false;

    Transform* pTransform = Impl()->children[index];
    pTransform->SetParent(nullptr);
    return true;
  }
}

