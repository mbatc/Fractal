
namespace Fractal
{
  template <typename T>
  inline Quaternion<T>::Quaternion(const Vector3<T>& axis, const T& angle) { Set(axis, angle); }

  template <typename T>
  inline Quaternion<T>::Quaternion(const T& eulerX, const T& eulerY, const T& eulerZ) { Set(eulerX, eulerY, eulerZ); }

  template <typename T>
  inline Quaternion<T>::Quaternion()
    : x(0), y(0), z(0), w(1)
  {
  }

  template <typename T>
  inline Quaternion<T>::Quaternion(const T& x, const T& y, const T& z, const T& w)
    : x(x), y(y), z(z), w(w)
  {
  }

  template <typename T>
  inline void Quaternion<T>::Set(const T& _x, const T& _y, const T& _z, const T& _w)
  {
    x = _x;
    y = _y;
    z = _z;
    w = _w;
  }

  template <typename T>
  inline void Quaternion<T>::Set(const Vector3<T>& axis, const T& angle)
  {
    T dist = axis.Mag();
    T s = Sin(angle * T(0.5)) / dist;
    Set(axis.x * s, axis.y * s, axis.z * s, Cos(angle * T(0.5)));
  }

  template <typename T>
  inline void Quaternion<T>::Set(const T& eulerX, const T& eulerY, const T& eulerZ)
  {
    double cy = Cos(eulerY * 0.5);
    double sy = Sin(eulerY * 0.5);
    double cp = Cos(eulerX * 0.5);
    double sp = Sin(eulerX * 0.5);
    double cr = Cos(eulerZ * 0.5);
    double sr = Sin(eulerZ * 0.5);

    w = cy * cp * cr + sy * sp * sr;
    x = cy * cp * sr - sy * sp * cr;
    y = sy * cp * sr + cy * sp * cr;
    z = sy * cp * cr - cy * sp * sr;
  }

  template <typename T>
  inline Quaternion<T> Quaternion<T>::zero()
  {
    return Quaternion<T>(0, 0, 0, 0);
  }

  template <typename T>
  inline Quaternion<T> Quaternion<T>::Identity()
  {
    return Quaternion<T>(0, 0, 0, 1);
  }

  template <typename T>
  inline Quaternion<T> Quaternion<T>::Normalize(const Quaternion<T>& quat)
  {
    return quat / Mag(quat);
  }

  template <typename T>
  inline Quaternion<T> Quaternion<T>::Inverse(const Quaternion<T>& quat)
  {
    return Quaternion<T>(-quat.x, -quat.y, -quat.z, quat.w);
  }

  template <typename T>
  inline Quaternion<T> Quaternion<T>::Mul(const Quaternion<T>& lhs, const Quaternion<T>& rhs)
  {
    return Quaternion<T>(
             lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y,
             lhs.w * rhs.y + lhs.y * rhs.w + lhs.z * rhs.x - lhs.x * rhs.z,
             lhs.w * rhs.z + lhs.z * rhs.w + lhs.x * rhs.y - lhs.y * rhs.x,
             lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z);
  }

  template <typename T>
  inline Quaternion<T> Quaternion<T>::Mul(const Quaternion<T>& lhs, const T& rhs)
  {
    return Quaternion<T>(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs);
  }

  template <typename T>
  inline Quaternion<T> Quaternion<T>::Add(const Quaternion<T>& lhs, const Quaternion<T>& rhs)
  {
    return Quaternion<T>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
  }

  template <typename T>
  inline Quaternion<T> Quaternion<T>::Sub(const Quaternion<T>& lhs, const Quaternion<T>& rhs)
  {
    return Quaternion<T>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
  }

  template <typename T>
  inline Quaternion<T> Quaternion<T>::Div(const Quaternion<T>& lhs, const T& rhs)
  {
    T reciprocal = T(1) / rhs;
    return Mul(lhs, reciprocal);
  }

  template <typename T>
  inline T Quaternion<T>::AngleTo(const Quaternion<T>& from, const Quaternion<T>& to)
  {
    T s = Sqrt(from.Length() * to.Length());
    if (abs(s) < std::numeric_limits<T>::min())
      return 0;
    return 2 * ACos(Dot(to) / s);
  }

  template <typename T>
  inline T Quaternion<T>::Angle(const Quaternion<T>& quat)
  {
    return T(2) * ctACos(quat.w);
  }

  template <typename T>
  inline T Quaternion<T>::Length(const Quaternion<T>& quat)
  {
    return Dot(quat, quat);
  }

  template <typename T>
  inline T Quaternion<T>::Mag(const Quaternion<T>& quat)
  {
    return ctSqrt(Length(quat));
  }

  template <typename T>
  inline T Quaternion<T>::Dot(const Quaternion<T>& lhs, const Quaternion<T>& rhs)
  {
    return lhs.x * rhs.x +
           lhs.y * rhs.y +
           lhs.z * rhs.z +
           lhs.w * rhs.w;
  }

  template <typename T>
  inline Vector3<T> Quaternion<T>::Rotate(const Quaternion<T>& quat, const Vector3<T>& vec)
  {
    Quaternion<T> q = quat * vec;
    q *= quat.Inverse();
    return Vector3<T>(q.x, q.y, q.z);
  }

  template <typename T>
  inline Vector3<T> Quaternion<T>::Axis(const Quaternion<T>& quat)
  {
    T s_sqr = T(1) - Square(quat.w);
    T s = T(1) / Sqrt(s_sqr);
    if (s < std::numeric_limits<T>::min())
      return Vector3<T>(1, 0, 0);
    return Vector3<T>(quat.x * s, quat.y * s, quat.z * s);
  }

  template <typename T>
  inline Vector3<T> Quaternion<T>::EulerAngles(const Quaternion<T>& quat)
  {
    Vector3<T> euler;
    // roll (x-axis rotation)
    double sinr_cosp = +2.0 * (quat.w * quat.x + quat.y * quat.z);
    double cosr_cosp = +1.0 - 2.0 * (quat.x * quat.x + quat.y * quat.y);
    euler.z = ATan2(sinr_cosp, cosr_cosp);

    // pitch (y-axis rotation)
    double sinp = +2.0 * (quat.w * quat.y - quat.z * quat.x);
    if (fabs(sinp) >= 1)
      euler.x = copysign(pi_2, sinp); // use 90 degrees if out of range
    else
      euler.x = ASin(sinp);

    // yaw (z-axis rotation)
    double siny_cosp = +2.0 * (quat.w * quat.z + quat.x * quat.y);
    double cosy_cosp = +1.0 - 2.0 * (quat.y * quat.y + quat.z * quat.z);
    euler.y = ATan2(siny_cosp, cosy_cosp);
    return euler;
  }

  template <typename T>
  inline Quaternion<T> Quaternion<T>::Slerp(const Quaternion<T>& to, const T& factor) const
  {
    Quaternion<T> result = *this;

    T mag = Sqrt(Length() * to.Length());
    if (mag > std::numeric_limits<T>::min())
    {
      const T product = Dot(to) / mag;
      const T absProduct = abs(product);

      if (absProduct < T(1) - std::numeric_limits<T>::min())
      {
        const T theta = ACos(absProduct);
        const T d = Sin(theta);
        if (d > 0)
        {
          T sign = product < 0 ? -1 : 1;
          T s0 = Sin((T(1) - factor) * theta) / d;
          T s1 = Sin(sign * factor * theta) / d;
          result.Set(
            x * s0 + to.x * s1,
            y * s0 + to.y * s1,
            z * s0 + to.z * s1,
            w * s0 + to.w * s1);
        }
      }
    }
    return result;
  }

  template <typename T>
  inline bool Quaternion<T>::operator==(const Quaternion<T>& rhs) const
  {
    return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
  }

  template <typename T>
  inline bool Quaternion<T>::operator!=(const Quaternion<T>& rhs) const
  {
    return !(*this == rhs);
  }

  template <typename T>
  inline Quaternion<T> Quaternion<T>::operator-() const
  {
    return Quaternion<T>(-x, -y, -z, -w);
  }

  template <typename T>
  inline const Quaternion<T>& Quaternion<T>::operator=(const Quaternion<T>& rhs)
  {
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    w = rhs.w;
    return *this;
  }

  template <typename T>
  inline Quaternion<T> operator*(const Vector3<T>& lhs, const Quaternion<T>& rhs)
  {
    return Quaternion<T>(
             +lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y,
             +lhs.y * rhs.w + lhs.z * rhs.x - lhs.x * rhs.z,
             +lhs.z * rhs.w + lhs.x * rhs.y - lhs.y * rhs.x,
             -lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z);
  }

  template <typename T>
  inline Quaternion<T> operator*(const Quaternion<T>& lhs, const Vector3<T>& rhs)
  {
    return Quaternion<T>(
             lhs.w * rhs.x + lhs.y * rhs.z - lhs.z * rhs.y,
             lhs.w * rhs.y + lhs.z * rhs.x - lhs.x * rhs.z,
             lhs.w * rhs.z + lhs.x * rhs.y - lhs.y * rhs.x,
             -lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z);
  }

  template <typename T>
  inline Quaternion<T> Quaternion<T>::Normalize() const
  {
    return Normalize(*this);
  }

  template <typename T>
  inline Quaternion<T> Quaternion<T>::Inverse() const
  {
    return Inverse(*this);
  }

  template <typename T>
  inline Quaternion<T> Quaternion<T>::Mul(const Quaternion<T>& rhs) const
  {
    return Mul(*this, rhs);
  }

  template <typename T>
  inline Quaternion<T> Quaternion<T>::Mul(const T& rhs) const
  {
    return Mul(*this, rhs);
  }

  template <typename T>
  inline Quaternion<T> Quaternion<T>::Add(const Quaternion<T>& rhs) const
  {
    return Add(*this, rhs);
  }

  template <typename T>
  inline Quaternion<T> Quaternion<T>::Sub(const Quaternion<T>& rhs) const
  {
    return Sub(*this, rhs);
  }

  template <typename T>
  inline Quaternion<T> Quaternion<T>::Div(const T& rhs) const
  {
    return Div(*this, rhs);
  }

  template <typename T>
  inline T Quaternion<T>::AngleTo(const Quaternion<T>& to) const
  {
    return AngleTo(*this, to);
  }

  template <typename T>
  inline T Quaternion<T>::Angle() const
  {
    return Angle(*this);
  }

  template <typename T>
  inline T Quaternion<T>::Length() const
  {
    return Length(*this);
  }

  template <typename T>
  inline T Quaternion<T>::Mag() const
  {
    return Mag(*this);
  }

  template <typename T>
  inline T Quaternion<T>::Dot(const Quaternion<T>& rhs) const
  {
    return Dot(*this, rhs);
  }

  template <typename T>
  inline Vector3<T> Quaternion<T>::EulerAngles() const
  {
    return EulerAngles(*this);
  }

  template <typename T>
  inline Vector3<T> Quaternion<T>::Axis() const
  {
    return Axis(*this);
  }

  template <typename T>
  inline Vector3<T> Quaternion<T>::Rotate(const Vector3<T>& vec) const
  {
    return Rotate(*this, vec);
  }

  template <typename T>
  inline Quaternion<T> Quaternion<T>::operator*(const Quaternion<T>& rhs) const
  {
    return Mul(rhs);
  }

  template <typename T>
  inline Quaternion<T> Quaternion<T>::operator-(const Quaternion<T>& rhs) const
  {
    return Sub(rhs);
  }

  template <typename T>
  inline Quaternion<T> Quaternion<T>::operator+(const Quaternion<T>& rhs) const
  {
    return Add(rhs);
  }

  template <typename T>
  inline Quaternion<T> Quaternion<T>::operator*(const T& rhs) const
  {
    return Mul(rhs);
  }

  template <typename T>
  inline Quaternion<T> Quaternion<T>::operator/(const T& rhs) const
  {
    return Div(rhs);
  }

  template <typename T>
  inline const Quaternion<T>& Quaternion<T>::operator*=(const Quaternion<T>& rhs)
  {
    return *this = Mul(rhs);
  }

  template <typename T>
  inline const Quaternion<T>& Quaternion<T>::operator*=(const T& rhs)
  {
    return *this = Mul(rhs);
  }

  template <typename T>
  inline const T& Quaternion<T>::at(int64_t index) const
  {
    return (&x)[index];
  }

  template <typename T>
  inline const T& Quaternion<T>::operator[](int64_t index) const
  {
    return at(index);
  }

  template <typename T>
  inline T& Quaternion<T>::at(int64_t index)
  {
    return (&x)[index];
  }

  template <typename T>
  inline T& Quaternion<T>::operator[](int64_t index)
  {
    return at(index);
  }

  template <typename T>
  inline const T* Quaternion<T>::begin() const
  {
    return &x;
  }

  template <typename T>
  inline const T* Quaternion<T>::end() const
  {
    return &w + 1;
  }

  template <typename T>
  inline T* Quaternion<T>::begin()
  {
    return &x;
  }

  template <typename T>
  inline T* Quaternion<T>::end()
  {
    return &w + 1;
  }
}