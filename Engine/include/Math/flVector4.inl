
namespace Fractal
{
  template <typename T>
  inline Vector4<T>::Vector4()
    : x(0), y(0), z(0), w(0)
  {
  }

  template <typename T>
  inline Vector4<T>::Vector4(T val)
    : x(val), y(val), z(val), w(val)
  {
  }

  template <typename T>
  inline Vector4<T>::Vector4(T _x, T _y, T _z, T _w)
    : x(_x), y(_y), z(_z), w(_w)
  {
  }

  template <typename T>
  inline Vector4<T>::Vector4(const Vector3<T>& xyz, T _w)
    : x(xyz.x), y(xyz.y), z(xyz.z), w(_w)
  {
  }

  template <typename T>
  inline Vector4<T>::Vector4(T _x, const Vector3<T>& yzw)
    : x(_x), y(yzw.x), z(yzw.y), w(yzw.z)
  {
  }

  template <typename T>
  inline Vector4<T>::Vector4(T _x, T _y, const Vector2<T>& zw)
    : x(_x), y(_y), z(zw.x), w(zw.y)
  {
  }

  template <typename T>
  inline Vector4<T>::Vector4(T _x, const Vector2<T>& yz, T _w)
    : x(_x), y(yz.x), z(yz.y), w(_w)
  {
  }

  template <typename T>
  inline Vector4<T>::Vector4(const Vector2<T>& xy, T _z, T _w)
    : x(xy.x), y(xy.y), z(_z), w(_w)
  {
  }

  template <typename T>
  template <typename T2>
  inline Vector4<T>::Vector4(T2 val)
    : x((T)val), y((T)val), z((T)val), w((T)val)
  {
  }

  template <typename T>
  template <typename T2>
  inline Vector4<T>::Vector4(T2 _x, T2 _y, T2 _z, T2 _w)
    : x((T)_x), y((T)_y), z((T)_z), w((T)_w)
  {
  }

  template <typename T>
  template <typename T2>
  inline Vector4<T>::Vector4(const Vector3<T2>& xyz, T2 _w)
    : x((T)xyz.x), y((T)xyz.y), z((T)xyz.z), w((T)_w)
  {
  }

  template <typename T>
  template <typename T2>
  inline Vector4<T>::Vector4(T2 _x, const Vector3<T2>& yzw)
    : x((T)_x), y((T)yzw.x), z((T)yzw.y), w((T)yzw.z)
  {
  }

  template <typename T>
  template <typename T2>
  inline Vector4<T>::Vector4(T2 _x, T2 _y, const Vector2<T2>& zw)
    : x((T)_x), y((T)_y), z((T)zw.x), w((T)zw.y)
  {
  }

  template <typename T>
  template <typename T2>
  inline Vector4<T>::Vector4(T2 _x, const Vector2<T2>& yz, T2 _w)
    : x((T)_x), y((T)yz.x), z((T)yz.y), w((T)_w)
  {
  }

  template <typename T>
  template <typename T2>
  inline Vector4<T>::Vector4(const Vector2<T2>& xy, T2 _z, T2 _w)
    : x((T)xy.x), y((T)xy.y), z((T)_z), w((T)_w)
  {
  }

  template <typename T>
  template <typename T2>
  inline Vector4<T>::Vector4(Vector4<T2> copy)
    : x((T)copy.x), y((T)copy.y), z((T)copy.z), w((T)copy.w)
  {
  }

  template <typename T>
  inline Vector4<T>::Vector4(const Vector2<T>& xy, const Vector2<T>& yw)
    : x(xy.x), y(xy.y), z(yw.x), w(yw.y)
  {
  }

  template <typename T>
  inline Vector4<T>::Vector4(const Vector4<T>& copy)
    : x(copy.x), y(copy.y), z(copy.z), w(copy.w)
  {
  }

  template <typename T>
  inline Vector4<T>::Vector4(Vector4<T>&& move)
    : x(move.x), y(move.y), z(move.z), w(move.w)
  {
  }

  template <typename T>
  inline const Vector4<T>& Vector4<T>::assign(T _x, T _y, T _z, T _w)
  {
    x = _x;
    y = _y;
    z = _z;
    w = _w;
    return *this;
  }

  template <typename T>
  template <typename T2>
  inline const Vector4<T>& Vector4<T>::assign(T2 _x, T2 _y, T2 _z, T2 _w)
  {
    x = (T)_x;
    y = (T)_y;
    z = (T)_z;
    w = (T)_w;
    return *this;
  }

  template <typename T>
  template <typename T2>
  inline const Vector4<T>& Vector4<T>::assign(const Vector4<T2>& rhs)
  {
    x = (T)rhs.x;
    y = (T)rhs.y;
    z = (T)rhs.z;
    w = (T)rhs.w;
    return *this;
  }

  template <typename T>
  inline const Vector4<T>& Vector4<T>::assign(const Vector4<T>& rhs)
  {
    x = (T)rhs.x;
    y = (T)rhs.y;
    z = (T)rhs.z;
    w = (T)rhs.w;
    return *this;
  }

  template <typename T>
  inline T Vector4<T>::Dot(const Vector4<T>& lhs, const Vector4<T>& rhs)
  {
    return lhs.x * rhs.x +
           lhs.y * rhs.y +
           lhs.z * rhs.z +
           lhs.w * rhs.w;
  }

  template <typename T>
  inline Vector4<T> Vector4<T>::Max(const Vector4<T>& a, const Vector4<T>& b)
  {
    return Vector4<T>(Max(a.x, b.x), Max(a.y, b.y), Max(a.z, b.z), Max(a.w, b.w));
  }

  template <typename T>
  inline Vector4<T> Vector4<T>::Min(const Vector4<T>& a, const Vector4<T>& b)
  {
    return Vector4<T>(Min(a.x, b.x), Min(a.y, b.y), Min(a.z, b.z), Min(a.w, b.w));
  }

  template <typename T>
  inline Vector4<T> Vector4<T>::Clamp(const Vector4<T>& vec, const Vector4<T>& min, const Vector4<T>& max)
  {
    return Max(min, Min(vec, max));
  }

  template <typename T>
  inline Vector2<T> Vector4<T>::xy() const
  {
    return Vector2<T>(x, y);
  }

  template <typename T>
  inline Vector2<T> Vector4<T>::xz() const
  {
    return Vector2<T>(x, z);
  }

  template <typename T>
  inline Vector2<T> Vector4<T>::xw() const
  {
    return Vector2<T>(x, w);
  }

  template <typename T>
  inline Vector2<T> Vector4<T>::yz() const
  {
    return Vector2<T>(y, z);
  }

  template <typename T>
  inline Vector2<T> Vector4<T>::yw() const
  {
    return Vector2<T>(y, w);
  }

  template <typename T>
  inline Vector2<T> Vector4<T>::zw() const
  {
    return Vector2<T>(z, w);
  }

  template <typename T>
  inline Vector3<T> Vector4<T>::xyz() const
  {
    return Vector3<T>(x, y, z);
  }

  template <typename T>
  inline Vector3<T> Vector4<T>::xzw() const
  {
    return Vector3<T>(x, z, w);
  }

  template <typename T>
  inline Vector3<T> Vector4<T>::xyw() const
  {
    return Vector3<T>(x, y, w);
  }

  template <typename T>
  inline Vector3<T> Vector4<T>::yzw() const
  {
    return Vector3<T>(y, z, w);
  }

  template <typename T>
  inline Vector4<T> Vector4<T>::Add(const Vector4<T>& rhs) const
  {
    return *this + rhs;
  }

  template <typename T>
  inline Vector4<T> Vector4<T>::Sub(const Vector4<T>& rhs) const
  {
    return *this - rhs;
  }

  template <typename T>
  inline Vector4<T> Vector4<T>::Mul(const Vector4<T>& rhs) const
  {
    return *this * rhs;
  }

  template <typename T>
  inline Vector4<T> Vector4<T>::Div(const Vector4<T>& rhs) const
  {
    return *this / rhs;
  }

  template <typename T>
  inline T Vector4<T>::Mag() const
  {
    return Mag(*this);
  }

  template <typename T>
  inline T Vector4<T>::Length() const
  {
    return Length(*this);
  }

  template <typename T>
  inline T Vector4<T>::Dot(const Vector4<T>& rhs) const
  {
    return Dot(*this, rhs);
  }

  template <typename T>
  inline T Vector4<T>::Angle(const Vector4<T>& rhs) const
  {
    return Angle(*this, rhs);
  }

  template <typename T>
  inline Vector4<T> Vector4<T>::Normalize() const
  {
    return Normalize(*this);
  }

  template <typename T>
  inline Vector4<T> Vector4<T>::Reflect(const Vector4<T>& norm) const
  {
    return Reflect(*this, norm);
  }

  template <typename T>
  inline Vector4<T> Vector4<T>::Project(const Vector4<T>& to) const
  {
    return Project(*this, to);
  }

  template <typename T>
  inline Vector4<T> Vector4<T>::Max(const Vector4<T>& b) const
  {
    return Max(*this, b);
  }

  template <typename T>
  inline Vector4<T> Vector4<T>::Min(const Vector4<T>& b) const
  {
    return Min(*this, b);
  }

  template <typename T>
  inline Vector4<T> Vector4<T>::Clamp(const Vector4<T>& min, const Vector4<T>& max) const
  {
    return Clamp(*this, min, max);
  }

  template <typename T>
  inline T Vector4<T>::Mag(const Vector4<T>& rhs)
  {
    return Sqrt(Length(rhs));
  }

  template <typename T>
  inline T Vector4<T>::Length(const Vector4<T>& rhs)
  {
    return Dot(rhs, rhs);
  }

  template <typename T>
  inline T Vector4<T>::Angle(const Vector4<T>& lhs, const Vector4<T>& rhs)
  {
    return ctACos(Dot(lhs, rhs) / (Mag(lhs) * Mag(rhs)));
  }

  template <typename T>
  inline Vector4<T> Vector4<T>::Reflect(const Vector4<T>& dir, const Vector4<T>& norm)
  {
    return dir - norm * Dot(dir, norm) * 2;
  }

  template <typename T>
  inline Vector4<T> Vector4<T>::Normalize(const Vector4<T>& rhs)
  {
    return rhs / Mag(rhs);
  }

  template <typename T>
  inline Vector4<T> Vector4<T>::Project(const Vector4<T>& vec, const Vector4<T>& to)
  {
    return vec * to.Normalize();
  }

  template <typename T>
  inline Vector4<T> Vector4<T>::zero()
  {
    return Vector4<T>((T)0);
  }

  template <typename T>
  inline Vector4<T> Vector4<T>::one()
  {
    return Vector4<T>((T)1);
  }

  template <typename T>
  inline T& Vector4<T>::operator[](int64_t index)
  {
    return m[index];
  }

  template <typename T>
  inline const T& Vector4<T>::operator[](int64_t index) const
  {
    return m[index];
  }

  template <typename T>
  inline Vector4<T> Vector4<T>::operator-() const
  {
    return Vector4<T>(-x, -y, -z, -w);
  }

  template <typename T>
  inline Vector4<T> Vector4<T>::operator+(const Vector4<T>& rhs) const
  {
    return Vector4<T>(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
  }

  template <typename T>
  inline Vector4<T> Vector4<T>::operator-(const Vector4<T>& rhs) const
  {
    return Vector4<T>(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
  }

  template <typename T>
  inline Vector4<T> Vector4<T>::operator*(const Vector4<T>& rhs) const
  {
    return Vector4<T>(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
  }

  template <typename T>
  inline Vector4<T> Vector4<T>::operator/(const Vector4<T>& rhs) const
  {
    return Vector4<T>(x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w);
  }

  template <typename T>
  inline Vector4<T> Vector4<T>::operator%(const Vector4<T>& rhs) const
  {
    return Vector4<T>(x % rhs.x, y % rhs.y, z % rhs.z, w % rhs.w);
  }

  template <typename T>
  inline const Vector4<T>& Vector4<T>::operator+=(const Vector4<T>& rhs)
  {
    return assign(*this + rhs);
  }

  template <typename T>
  inline const Vector4<T>& Vector4<T>::operator-=(const Vector4<T>& rhs)
  {
    return assign(*this - rhs);
  }

  template <typename T>
  inline const Vector4<T>& Vector4<T>::operator*=(const Vector4<T>& rhs)
  {
    return assign(*this * rhs);
  }

  template <typename T>
  inline const Vector4<T>& Vector4<T>::operator/=(const Vector4<T>& rhs)
  {
    return assign(*this / rhs);
  }

  template <typename T>
  inline const Vector4<T>& Vector4<T>::operator%=(const Vector4<T>& rhs)
  {
    return assign(Mod(x, rhs.x), Mod(y, rhs.y), Mod(z, rhs.z), Mod(w, rhs.w));
  }

  template <typename T>
  inline const Vector4<T>& Vector4<T>::operator=(const Vector4<T>& rhs)
  {
    return assign(rhs);
  }

  template <typename T>
  inline bool Vector4<T>::operator==(const Vector4<T>& rhs) const
  {
    return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
  }

  template <typename T>
  inline bool Vector4<T>::operator!=(const Vector4<T>& rhs) const
  {
    return !(*this == rhs);
  }

  template <typename T>
  inline const T* Vector4<T>::end() const
  {
    return m + ElementCount;
  }

  template <typename T>
  inline const T* Vector4<T>::begin() const
  {
    return m;
  }

  template <typename T>
  inline const T* Vector4<T>::data() const
  {
    return m;
  }

  template <typename T>
  inline T* Vector4<T>::end()
  {
    return m + ElementCount;
  }

  template <typename T>
  inline T* Vector4<T>::begin()
  {
    return m;
  }

  template <typename T>
  inline T* Vector4<T>::data()
  {
    return m;
  }

  template <typename T>
  inline Vector4<T> operator*(const T& lhs, const Vector4<T>& rhs)
  {
    return rhs * lhs;
  }

  template <typename T>
  inline Vector4<T> operator/(const T& lhs, const Vector4<T>& rhs)
  {
    return Vector4<T>(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z, lhs / rhs.w);
  }
}