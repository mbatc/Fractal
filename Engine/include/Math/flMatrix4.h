#pragma once

#include "flVector4.h"
#include "flQuaternion.h"

namespace Fractal
{
  template <typename T>
  inline T MatrixDet2x2(T a, T b, T c, T d);
  template <typename T>
  inline T MatrixDet3x3(T a, T b, T c, T d, T e, T f, T g, T h, T i);

  template <typename T>
  class Matrix4
  {
  public:
    Matrix4(
      T _00 = 1, T _01 = 0, T _02 = 0, T _03 = 0,
      T _10 = 0, T _11 = 1, T _12 = 0, T _13 = 0,
      T _20 = 0, T _21 = 0, T _22 = 1, T _23 = 0,
      T _30 = 0, T _31 = 0, T _32 = 0, T _33 = 1);

    Matrix4(Matrix4<T>&& move);
    Matrix4(const Matrix4<T>& copy);

    template <typename T2>
    Matrix4(const Matrix4<T2>& copy);

    Matrix4<T> Transpose() const;
    Matrix4<T> Cofactors() const;
    Matrix4<T> Inverse() const;

    T Determinate() const;

    Matrix4<T> Mul(const T& rhs) const;
    Matrix4<T> Sub(const T& rhs) const;
    Matrix4<T> Add(const T& rhs) const;
    Matrix4<T> AddDiagonal(const T& rhs) const;
    Matrix4<T> Mul(const Matrix4<T>& rhs) const;
    Vector4<T> Mul(const Vector4<T>& rhs) const;
    Vector3<T> Mul(const Vector3<T>& rhs) const;
    Matrix4<T> Apply(T(*func)(const T&)) const;

    Vector3<T> GetTranslation() const;
    Vector3<T> GetRotation() const;
    Vector3<T> GetScale() const;
    Quaternion<T> GetOrientation() const;

    void Decompose(Vector3<T>* pTranslation, Vector3<T>* pRotation, Vector3<T>* pScale) const;

    static Matrix4<T> Identity();
    static Matrix4<T> Projection(const T aspect, const T FOV, const T nearPlane, const T farPlane, const T zClipNear = 0, const T zClipFar = 1);
    static Matrix4<T> Ortho(const T width, const T height, const T nearPlane, const T farPlane);
    static Matrix4<T> Ortho(const T left, const T right, const T top, const T bottom, const T nearPlane, const T farPlane);
    static Matrix4<T> RotationX(const T rads);
    static Matrix4<T> RotationY(const T rads);
    static Matrix4<T> RotationZ(const T rads);
    static Matrix4<T> Rotation(const Vector3<T>& axis, T rads);
    static Matrix4<T> Rotation(const Quaternion<T>& quat);
    static Matrix4<T> YawPitchRoll(const T yaw, const T pitch, const T roll);
    static Matrix4<T> YawPitchRoll(const Vector3<T>& ypr);
    static Matrix4<T> Translation(const Vector3<T>& translation);
    static Matrix4<T> Scale(const Vector3<T>& scale);
    static Matrix4<T> Scale(const Vector4<T>& scale);
    static Matrix4<T> ScaleUniform(const T& scale);

    Vector4<T> operator*(const Vector4<T>& rhs) const;
    Vector3<T> operator*(const Vector3<T>& rhs) const;
    Matrix4<T> operator*(const T& rhs) const;
    Matrix4<T> operator*(const Matrix4<T>& rhs) const;

    bool operator==(const Matrix4<T>& rhs) const;
    bool operator!=(const Matrix4<T>& rhs) const;
    const Matrix4<T>& operator=(const Matrix4<T>& copy);

    T& operator[](const int64_t index);
    const T& operator[](const int64_t index) const;

    union
    {
      T m[16];
      Vector4<T> row[4];
    };
  };
}

#include "flMatrix4.inl"
