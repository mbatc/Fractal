#pragma once

#include "flVector3.h"

namespace Fractal
{
  template <typename T>
  class Quaternion
  {
  public:
    Quaternion();
    Quaternion(const T& x, const T& y, const T& z, const T& w);
    Quaternion(const Vector3<T>& axis, const T& angle);
    Quaternion(const T& eulerX, const T& eulerY, const T& eulerZ);

    void Set(const T& x, const T& y, const T& z, const T& w);
    void Set(const Vector3<T>& axis, const T& angle);
    void Set(const T& eulerX, const T& eulerY, const T& eulerZ);

    static Quaternion<T> zero();
    static Quaternion<T> Identity();

    static Quaternion<T> Normalize(const Quaternion<T>& quat);
    static Quaternion<T> Inverse(const Quaternion<T>& quat);
    static Quaternion<T> Mul(const Quaternion<T>& lhs, const Quaternion<T>& rhs);
    static Quaternion<T> Mul(const Quaternion<T>& lhs, const T& rhs);
    static Quaternion<T> Add(const Quaternion<T>& lhs, const Quaternion<T>& rhs);
    static Quaternion<T> Sub(const Quaternion<T>& lhs, const Quaternion<T>& rhs);
    static Quaternion<T> Div(const Quaternion<T>& lhs, const T& rhs);

    static T AngleTo(const Quaternion<T>& from, const Quaternion<T>& to);
    static T Angle(const Quaternion<T>& quat);
    static T Length(const Quaternion<T>& quat);
    static T Mag(const Quaternion<T>& quat);
    static T Dot(const Quaternion<T>& lhs, const Quaternion<T>& rhs);

    static Vector3<T> Rotate(const Quaternion<T>& quat, const Vector3<T>& vec);
    static Vector3<T> Axis(const Quaternion<T>& quat);
    static Vector3<T> EulerAngles(const Quaternion<T>& quat);

    Quaternion<T> Slerp(const Quaternion& to, const T& factor) const;
    Quaternion<T> Normalize() const;
    Quaternion<T> Inverse() const;
    Quaternion<T> Mul(const Quaternion<T>& rhs) const;
    Quaternion<T> Mul(const T& rhs) const;
    Quaternion<T> Add(const Quaternion<T>& rhs) const;
    Quaternion<T> Sub(const Quaternion<T>& rhs) const;
    Quaternion<T> Div(const T& rhs) const;

    T AngleTo(const Quaternion<T>& to) const;
    T Angle() const;
    T Length() const;
    T Mag() const;
    T Dot(const Quaternion<T>& rhs) const;

    Vector3<T> EulerAngles() const;
    Vector3<T> Axis() const;
    Vector3<T> Rotate(const Vector3<T>& vec) const;

    bool operator==(const Quaternion<T>& rhs) const;
    bool operator!=(const Quaternion<T>& rhs) const;

    Quaternion<T> operator*(const Quaternion<T>& rhs) const;
    Quaternion<T> operator-(const Quaternion<T>& rhs) const;
    Quaternion<T> operator+(const Quaternion<T>& rhs) const;
    Quaternion<T> operator*(const T& rhs) const;
    Quaternion<T> operator/(const T& rhs) const;
    Quaternion<T> operator-() const;

    const Quaternion<T>& operator=(const Quaternion<T>& rhs);
    const Quaternion<T>& operator*=(const Quaternion<T>& rhs);
    const Quaternion<T>& operator*=(const T& rhs);

    const T& at(int64_t index) const;
    const T& operator[](int64_t index) const;
    T& at(int64_t index);
    T& operator[](int64_t index);

    const T* begin() const;
    const T* end() const;
    T* begin();
    T* end();

    T x;
    T y;
    T z;
    T w;
  };

  template <typename T>
  Quaternion<T> operator*(const Vector3<T>& lhs, const Quaternion<T>& rhs);
  template <typename T>
  Quaternion<T> operator*(const Quaternion<T>& lhs, const Vector3<T>& rhs);
}

#include "flQuaternion.inl"
