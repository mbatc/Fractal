#pragma once

#include "flVector3.h"

namespace Fractal
{
  template <typename T>
  class Vector4
  {
  public:
    enum
    {
      ElementCount = 4
    };

    Vector4();
    Vector4(T val);
    Vector4(T _x, T _y, T _z, T _w);
    Vector4(const Vector3<T>& xyz, T _w);
    Vector4(T _x, const Vector3<T>& yzw);
    Vector4(T _x, T _y, const Vector2<T>& zw);
    Vector4(T _x, const Vector2<T>& yz, T _w);
    Vector4(const Vector2<T>& xy, T _z, T _w);
    Vector4(const Vector2<T>& xy, const Vector2<T>& yw);

    template <typename T2>
    explicit Vector4(T2 val);
    template <typename T2>
    Vector4(T2 _x, T2 _y, T2 _z, T2 _w);
    template <typename T2>
    Vector4(const Vector3<T2>& xyz, T2 _w);
    template <typename T2>
    Vector4(T2 _x, const Vector3<T2>& yzw);
    template <typename T2>
    Vector4(T2 _x, T2 _y, const Vector2<T2>& zw);
    template <typename T2>
    Vector4(T2 _x, const Vector2<T2>& yz, T2 _w);
    template <typename T2>
    Vector4(const Vector2<T2>& xy, T2 _z, T2 _w);
    template <typename T2>
    Vector4(const Vector2<T2>& xy, const Vector2<T2>& yw);
    template <typename T2>
    Vector4(Vector4<T2> copy);

    Vector4(const Vector4<T>& copy);
    Vector4(Vector4<T>&& move);

    static Vector4<T> zero();
    static Vector4<T> one();

    template <typename T2>
    const Vector4<T>& assign(T2 _x, T2 _y, T2 _z, T2 _w);
    template <typename T2>
    const Vector4<T>& assign(const Vector4<T2>& rhs);
    const Vector4<T>& assign(T x, T y, T z, T w);
    const Vector4<T>& assign(const Vector4<T>& rhs);

    T& operator[](const int64_t index);
    const T& operator[](const int64_t index) const;

    Vector4<T> operator-() const;
    Vector4<T> operator+(const Vector4<T>& rhs) const;
    Vector4<T> operator-(const Vector4<T>& rhs) const;
    Vector4<T> operator*(const Vector4<T>& rhs) const;
    Vector4<T> operator/(const Vector4<T>& rhs) const;
    Vector4<T> operator%(const Vector4<T>& rhs) const;
    const Vector4<T>& operator+=(const Vector4<T>& rhs);
    const Vector4<T>& operator-=(const Vector4<T>& rhs);
    const Vector4<T>& operator*=(const Vector4<T>& rhs);
    const Vector4<T>& operator/=(const Vector4<T>& rhs);
    const Vector4<T>& operator%=(const Vector4<T>& rhs);
    const Vector4<T>& operator=(const Vector4<T>& rhs);
    bool operator==(const Vector4<T>& rhs) const;
    bool operator!=(const Vector4<T>& rhs) const;

    Vector2<T> xy() const;
    Vector2<T> xz() const;
    Vector2<T> xw() const;
    Vector2<T> yz() const;
    Vector2<T> yw() const;
    Vector2<T> zw() const;
    Vector3<T> xyz() const;
    Vector3<T> xzw() const;
    Vector3<T> xyw() const;
    Vector3<T> yzw() const;

    Vector4<T> Add(const Vector4<T>& rhs) const;
    Vector4<T> Sub(const Vector4<T>& rhs) const;
    Vector4<T> Mul(const Vector4<T>& rhs) const;
    Vector4<T> Div(const Vector4<T>& rhs) const;

    T Mag() const;
    T Length() const;
    T Dot(const Vector4<T>& rhs) const;
    T Angle(const Vector4<T>& rhs) const;

    Vector4<T> Normalize() const;
    Vector4<T> Reflect(const Vector4<T>& norm) const;
    Vector4<T> Project(const Vector4<T>& to) const;

    // Returns a vector with where each component is the max of this and the input vectors components.
    Vector4<T> Max(const Vector4<T>& b) const;

    // Returns a vector with where each component is the min of this and the input vectors components.
    Vector4<T> Min(const Vector4<T>& b) const;

    // Returns a vector with where each component is clamped to the min/max of this and the input vectors components
    Vector4<T> Clamp(const Vector4<T>& min, const Vector4<T>& max) const;

    static T Mag(const Vector4<T>& rhs);
    static T Length(const Vector4<T>& rhs);
    static T Dot(const Vector4<T>& lhs, const Vector4<T>& rhs);
    static T Angle(const Vector4<T>& lhs, const Vector4<T>& rhs);

    static Vector4<T> Reflect(const Vector4<T>& dir, const Vector4<T>& norm);
    static Vector4<T> Normalize(const Vector4<T>& rhs);
    static Vector4<T> Project(const Vector4<T>& vec, const Vector4<T>& to);

    // Returns a vector with where each component is the max of the input vectors components.
    static Vector4<T> Max(const Vector4<T>& a, const Vector4<T>& b);

    // Returns a vector with where each component is the min of the input vectors components.
    static Vector4<T> Min(const Vector4<T>& a, const Vector4<T>& b);

    // Returns a vector with where each component is clamped to the min/max of the input vectors components
    static Vector4<T> Clamp(const Vector4<T>& vec, const Vector4<T>& min, const Vector4<T>& max);

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
        T w;
      };

      T m[ElementCount];
    };
  };

  template <typename T>
  inline Vector4<T> operator*(const T& lhs, const Vector4<T>& rhs);
  template <typename T>
  inline Vector4<T> operator/(const T& lhs, const Vector4<T>& rhs);

}

#include "flVector4.inl"
