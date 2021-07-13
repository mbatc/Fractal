#pragma once

#include "flMathHelpers.h"

namespace Fractal
{
  template <typename T>
  class Vector2
  {
  public:
    enum
    {
      ElementCount = 2
    };

    Vector2();
    Vector2(T val);
    Vector2(T _x, T _y);
    Vector2(const Vector2<T>& copy);
    Vector2(Vector2<T>&& move);

    template <typename T2>
    explicit Vector2(T2 val);
    template <typename T2>
    Vector2(T2 _x, T2 _y);
    template <typename T2>
    Vector2(const Vector2<T2>& copy);

    static Vector2<T> zero();
    static Vector2<T> one();

    const Vector2<T>& assign(T x, T y);
    const Vector2<T>& assign(const Vector2<T>& rhs);

    template <typename T2>
    const Vector2<T>& assign(T2 x, T2 y);
    template <typename T2>
    const Vector2<T>& assign(const Vector2<T2>& rhs);

    T* data();
    const T* data() const;
    T& operator[](int64_t index);
    const T& operator[](int64_t index) const;

    Vector2<T> operator-() const;
    Vector2<T> operator+(const Vector2<T>& rhs) const;
    Vector2<T> operator-(const Vector2<T>& rhs) const;
    Vector2<T> operator*(const Vector2<T>& rhs) const;
    Vector2<T> operator/(const Vector2<T>& rhs) const;
    Vector2<T> operator%(const Vector2<T>& rhs) const;

    const Vector2<T>& operator+=(const Vector2<T>& rhs);
    const Vector2<T>& operator-=(const Vector2<T>& rhs);
    const Vector2<T>& operator*=(const Vector2<T>& rhs);
    const Vector2<T>& operator/=(const Vector2<T>& rhs);
    const Vector2<T>& operator%=(const Vector2<T>& rhs);
    const Vector2<T>& operator=(const Vector2<T>& rhs);

    bool operator==(const Vector2<T>& rhs) const;
    bool operator!=(const Vector2<T>& rhs) const;

    Vector2<T> Add(const Vector2<T>& rhs) const;
    Vector2<T> Sub(const Vector2<T>& rhs) const;
    Vector2<T> Mul(const Vector2<T>& rhs) const;
    Vector2<T> Div(const Vector2<T>& rhs) const;

    T Mag() const;
    T Length() const;
    T Dot(const Vector2<T>& rhs) const;
    T Angle(const Vector2<T>& rhs) const;

    Vector2<T> Normalize() const;
    Vector2<T> Reflect(const Vector2<T>& norm) const;
    Vector2<T> Project(const Vector2<T>& to) const;

    // Returns a vector with where each component is the max of this and the input vectors components.
    Vector2<T> Max(const Vector2<T>& b) const;

    // Returns a vector with where each component is the min of this and the input vectors components.
    Vector2<T> Min(const Vector2<T>& b) const;

    // Returns a vector with where each component is clamped to the min/max of this and the input vectors components
    Vector2<T> Clamp(const Vector2<T>& min, const Vector2<T>& max) const;

    static T Mag(const Vector2<T>& rhs);
    static T Length(const Vector2<T>& rhs);
    static T Dot(const Vector2<T>& lhs, const Vector2<T>& rhs);
    static T Angle(const Vector2<T>& lhs, const Vector2<T>& rhs);

    static Vector2<T> Project(const Vector2<T>& vec, const Vector2<T>& to);
    static Vector2<T> Reflect(const Vector2<T>& dir, const Vector2<T>& norm);
    static Vector2<T> Normalize(const Vector2<T>& rhs);

    // Returns a vector with where each component is the max of the input vectors components.
    static Vector2<T> Max(const Vector2<T>& a, const Vector2<T>& b);

    // Returns a vector with where each component is the min of the input vectors components.
    static Vector2<T> Min(const Vector2<T>& a, const Vector2<T>& b);

    // Returns a vector with where each component is clamped to the min/max of the input vectors components
    static Vector2<T> Clamp(const Vector2<T>& vec, const Vector2<T>& min, const Vector2<T>& max);

    T* begin();
    T* end();
    const T* begin() const;
    const T* end() const;

    union
    {
      struct
      {
        T x;
        T y;
      };

      T m[ElementCount];
    };
  };

  template <typename T>
  inline T ctATan2(const Vector2<T>& pos);
  template <typename T>
  inline Vector2<T> tmlSolveQuadratic(const T& a, const T& b, const T& c);

  template <typename T>
  inline Vector2<T> operator*(const T& lhs, const Vector2<T>& rhs);
  template <typename T>
  inline Vector2<T> operator/(const T& lhs, const Vector2<T>& rhs);
}

#include "flVector2.inl"
