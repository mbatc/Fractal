#pragma once

#include <math.h>
#include <limits>

#undef min
#undef max

namespace Fractal
{
  static constexpr double e = 2.71828182845904523536;        // e
  static constexpr double log2e = 1.44269504088896340736;    // log2(e)
  static constexpr double log10e = 0.434294481903251827651;  // log10(e)
  static constexpr double ln2 = 0.693147180559945309417;     // ln(2)
  static constexpr double ln10 = 2.30258509299404568402;     // ln(10)
  static constexpr double pi = 3.14159265358979323846;       // pi
  static constexpr double pi_2 = 1.57079632679489661923;     // pi/2
  static constexpr double pi_4 = 0.785398163397448309616;    // pi/4
  static constexpr double _1_PI = 0.318309886183790671538;   // 1/pi
  static constexpr double _2_PI = 0.636619772367581343076;   // 2/pi
  static constexpr double sqrtPi = 1.12837916709551257390;   // 2/sqrt(pi)
  static constexpr double sqrt2 = 1.41421356237309504880;    // sqrt(2)
  static constexpr double sqrt1_2 = 0.707106781186547524401; // 1/sqrt(2)

  inline constexpr double Degs2Rads(double x) { return x * 0.017453292519943295769; }
  inline constexpr double Rads2Degs(double x) { return x * 57.29577951308232087679; }
  inline constexpr float Degs2Radsf(float x) { return x * 0.017453292519943295769f; }
  inline constexpr float Rads2Degsf(float x) { return x * 57.29577951308232087679f; }

  template <typename T>
  inline T Min(const T& a)
  {
    return a;
  }

  template <typename T>
  inline T Max(const T& a)
  {
    return a;
  }

  template <typename T, typename T2, typename... Args>
  inline T Min(const T& first, const T2& second, Args... args)
  {
    T argMin = (T)Min(second, std::forward<Args>(args)...);
    return (argMin < first) ? argMin : first;
  }

  template <typename T, typename T2, typename... Args>
  inline T Max(const T& first, const T2& second, Args... args)
  {
    T argMin = (T)Max(second, std::forward<Args>(args)...);
    return (argMin > first) ? argMin : first;
  }

  template <typename T, typename T2, typename T3>
  inline T Clamp(const T& val, const T2& min, const T3& max)
  {
    return Min(max, Max(min, val));
  }

  template <typename T>
  inline T Square(const T& x)
  {
    return x * x;
  }

  template <typename T>
  inline T Sin(const T& rads)
  {
    return (T)sin(rads);
  }

  template <typename T>
  inline T Cos(const T& rads)
  {
    return (T)cos(rads);
  }

  template <typename T>
  inline T Tan(const T& rads)
  {
    return (T)tan(rads);
  }

  template <typename T>
  inline T ASin(const T& rads)
  {
    return (T)asin(rads);
  }

  template <typename T>
  inline T ACos(const T& rads)
  {
    return (T)acos(rads);
  }

  template <typename T>
  inline T ATan(const T& rads)
  {
    return (T)atan(rads);
  }

  template <typename T>
  inline T ATan2(const T& y, const T& x)
  {
    if (x == 0 && y == 0)
      return 0;
    const double rad = sqrt(x * x + y * y);
    return 2 * ATan(x <= 0 ? (rad - x) / y : y / (rad + y));
  }

  template <typename T, typename T2>
  inline T Lerp(const T& a, const T& b, const T2& time)
  {
    return a + (b - a) * (time);
  }

  template <typename InT, typename OutT>
  inline OutT Derivative(const InT& val, OutT(*func)(InT), const InT step)
  {
    return OutT(func(val + step) - func(val - step)) / (step * 2);
  }

  template <typename InT, typename OutT>
  inline OutT NthDerivative(const InT& val, OutT(*func)(InT), const int64_t& n, const InT step)
  {
    if (n <= 0)
      return Derivative(val, func, step);
    OutT rhs = NthDerivative(val + step, func, n - 1, step);
    OutT lhs = NthDerivative(val - step, func, n - 1, step);
    return OutT(rhs - lhs) / (step * 2);
  }

  template <typename T>
  inline T Sigmoid(T val)
  {
    return 1 / (1 + exp(-val));
  }

  template <typename T>
  inline T SigmoidApprox(const T& val)
  {
    static T sigLookup[] =
    {
      T(0),
      Sigmoid(T(-5)),
      Sigmoid(T(-4)),
      Sigmoid(T(-3)),
      Sigmoid(T(-2)),
      Sigmoid(T(-1)),
      Sigmoid(T(0)),
      Sigmoid(T(1)),
      Sigmoid(T(2)),
      Sigmoid(T(3)),
      Sigmoid(T(4)),
      Sigmoid(T(5)),
      T(1)
    };

    static int64_t lookupSize = sizeof(sigLookup) / sizeof(T);
    static int64_t sigMid = lookupSize / 2;

    T offset = val + sigMid;
    int64_t lower = Clamp(int64_t(offset), 0, lookupSize - 1);
    int64_t upper = Clamp(int64_t(offset + 1), 0, lookupSize - 1);
    return Lerp(sigLookup[lower], sigLookup[upper], (offset - lower));
  }

  template <typename T>
  inline T Mod(const T& a, const T& b)
  {
    return a % b;
  }

  template <>
  inline float Mod(const float& a, const float& b)
  {
    return fmodf(a, b);
  }

  template <>
  inline double Mod(const double& a, const double& b)
  {
    return fmod(a, b);
  }

  template <typename T>
  inline T NumBitsOn(const T& val)
  {
    static uint8_t lookup[16] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4};
    if (val == 0)
      return 0;
    uint8_t addr = uint8_t(val & 0x0F);
    return lookup[addr] + NumBitsOn(val >> 4);
  }

  inline float Sqrt(const float& val)
  {
    return sqrtf(val);
  }

  inline double Sqrt(const double& val)
  {
    return sqrtl(val);
  }

  inline int64_t Sqrt(const int64_t& val)
  {
    return (int64_t)sqrt((double)val);
  }

  inline int32_t Sqrt(const int32_t& val)
  {
    return (int32_t)sqrt((double)val);
  }

  inline int16_t Sqrt(const int16_t& val)
  {
    return (int16_t)sqrt((double)val);
  }

  inline int8_t Sqrt(const int8_t& val)
  {
    return (int8_t)sqrt((double)val);
  }

  inline int64_t Factorial(const int64_t& n)
  {
    return n <= 1 ? 1 : n * Factorial(n - 1);
  }
}
