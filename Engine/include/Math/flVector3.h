#pragma once

#include "flVector2.h"

namespace Fractal
{
  template <typename T>
  class Vector3
  {
  public:
    enum
    {
      ElementCount = 3
    };

    Vector3();
    Vector3(T val);
    Vector3(T _x, T _y, T _z);
    Vector3(T _x, const Vector2<T>& yz);
    Vector3(const Vector2<T>& xy, T _z);
    Vector3(const Vector3<T>& copy);
    Vector3(Vector3<T>&& move);

    template <typename T2>
    Vector3(T2 _x, T2 _y, T2 _z);
    template <typename T2>
    Vector3(T2 _x, const Vector2<T2>& yz);
    template <typename T2>
    Vector3(const Vector2<T2>& xy, T2 _z);
    template <typename T2>
    Vector3(Vector3<T2> copy);
    template <typename T2>
    explicit Vector3(T2 val);

    static Vector3<T> zero();
    static Vector3<T> one();

    template <typename T2>
    const Vector3<T>& assign(T2 _x, T2 _y, T2 _z);
    template <typename T2>
    const Vector3<T>& assign(const Vector3<T2>& rhs);

    const Vector3<T>& assign(T _x, T _y, T _z);
    const Vector3<T>& assign(const Vector3<T>& rhs);

    T& operator[](int64_t index);
    const T& operator[](int64_t index) const;

    Vector3<T> operator-() const;
    Vector3<T> operator+(const Vector3<T>& rhs) const;
    Vector3<T> operator-(const Vector3<T>& rhs) const;
    Vector3<T> operator*(const Vector3<T>& rhs) const;
    Vector3<T> operator/(const Vector3<T>& rhs) const;
    Vector3<T> operator%(const Vector3<T>& rhs) const;

    const Vector3<T>& operator+=(const Vector3<T>& rhs);
    const Vector3<T>& operator-=(const Vector3<T>& rhs);
    const Vector3<T>& operator*=(const Vector3<T>& rhs);
    const Vector3<T>& operator/=(const Vector3<T>& rhs);
    const Vector3<T>& operator%=(const Vector3<T>& rhs);
    const Vector3<T>& operator=(const Vector3<T>& rhs);

    bool operator==(const Vector3<T>& rhs) const;
    bool operator!=(const Vector3<T>& rhs) const;

    Vector2<T> xy() const;
    Vector2<T> xz() const;
    Vector2<T> yz() const;

    T Mag() const;
    T Length() const;
    T Dot(const Vector3<T>& rhs) const;
    T Angle(const Vector3<T>& rhs) const;

    Vector3<T> Add(const Vector3<T>& rhs) const;
    Vector3<T> Sub(const Vector3<T>& rhs) const;
    Vector3<T> Mul(const Vector3<T>& rhs) const;
    Vector3<T> Div(const Vector3<T>& rhs) const;

    Vector3<T> Normalize() const;
    Vector3<T> Reflect(const Vector3<T>& norm) const;
    Vector3<T> Cross(const Vector3<T>& rhs) const;
    Vector3<T> Project(const Vector3<T>& to) const;

    // Returns a vector with where each component is the max of this and the input vectors components.
    Vector3<T> Max(const Vector3<T>& b) const;

    // Returns a vector with where each component is the min of this and the input vectors components.
    Vector3<T> Min(const Vector3<T>& b) const;

    // Returns a vector with where each component is clamped to the min/max of this and the input vectors components
    Vector3<T> Clamp(const Vector3<T>& min, const Vector3<T>& max) const;

    static T Mag(const Vector3<T>& rhs);
    static T Length(const Vector3<T>& rhs);
    static T Dot(const Vector3<T>& lhs, const Vector3<T>& rhs);
    static T Angle(const Vector3<T>& lhs, const Vector3<T>& rhs);

    static Vector3<T> Normalize(const Vector3<T>& rhs);
    static Vector3<T> Cross(const Vector3<T>& lhs, const Vector3<T>& rhs);
    static Vector3<T> Reflect(const Vector3<T>& dir, const Vector3<T>& norm);
    static Vector3<T> Project(const Vector3<T>& vec, const Vector3<T>& to);

    // Returns a vector with where each component is the max of the input vectors components.
    static Vector3<T> Max(const Vector3<T>& a, const Vector3<T>& b);

    // Returns a vector with where each component is the min of the input vectors components.
    static Vector3<T> Min(const Vector3<T>& a, const Vector3<T>& b);

    // Returns a vector with where each component is clamped to the min/max of the input vectors components
    static Vector3<T> Clamp(const Vector3<T>& vec, const Vector3<T>& min, const Vector3<T>& max);

    T* begin();
    T* end();
    const T* begin() const;
    const T* end() const;

    T* data();
    const T* data() const;

    union
    {
      struct
      {
        T x;
        T y;
        T z;
      };

      T m[ElementCount];
    };
  };

  template <typename T>
  inline Vector3<T> operator*(const T& lhs, const Vector3<T>& rhs);
  template <typename T>
  inline Vector3<T> operator/(const T& lhs, const Vector3<T>& rhs);
}

#include "flVector3.inl"
