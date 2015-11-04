//-*- Mode: C++ -*-
/**
 * @class FMath
 * @brief Simple Math functions.
 *
 * Created by Stuart Hacking on 07/02/2015.
 * Copyright (c) 2015 Stuart Hacking. All rights reserved.
 *
 * @author Stuart Hacking <stuhacking@gmail.com>
 */
#ifndef __SHLIB_FMath_H_
#define __SHLIB_FMath_H_

#include <cmath>

#define DEG2RAD(a) ((a) * FMath::_DEGTORAD)
#define RAD2DEG(a) ((a) * FMath::_RADTODEG)

namespace sge {

class FMath {
public:
    constexpr static const float PI = static_cast<float>(M_PI);
    constexpr static const float HALF_PI = PI * 0.5f;
    constexpr static const float TWO_PI = PI * 2.0f;

    constexpr static const float E = static_cast<float>(M_E);
    constexpr static const float INFTY = static_cast<float>(INFINITY);

    constexpr static const float _DEGTORAD = PI / 180.0f;
    constexpr static const float _RADTODEG = 180.0f / PI;

    constexpr static float Min (const float a, const float b);

    constexpr static float Max (const float a, const float b);

    /**
     * Clamp float value within min/max boundaries.
     */
    static float ClampFloat (const float val, const float a, const float b);

    /**
     * Clamp int value within min/max boundaries.
     */
    static int ClampInt (const int val, const int a, const int b);

    /**
     * Return the first power of 2 that is not less than val.
     */
    static int Nearest2Pow (const unsigned int val);

    /**
     * Convert a value within a range to a ratio. Resulting value may
     * fall outside the 0.0f .. 1.0f range.
     */
    static float ToRatio (float val, float min, float max);

    /**
     * Convert a value within a range to a ratio strictly clamped to
     * 0.0f .. 1.0f
     */
    static float ClampedRatio (float val, float min, float max);

    /**
     * Linear interpolation.
     */
    static float Lerp (float min, float max, float ratio);

    /**
     * Reposition a value from an old range into a new range.
     */
    static float Fit (float val, float oMin, float oMax, float nMin, float nMax);

    /**
     * Sine Interpolation.
     */
    static float SinInterpolate (const float min, const float max, const float ratio);

    /**
     * Cosine Interpolation.
     */
    static float CosInterpolate (const float min, const float max, const float ratio);

    /**
     * Simultaneously find the Sine and Cosine of an angle and
     * write the values into s and c.
     */
    static void SinCos (const float angle, float &s, float &c);
};

constexpr inline float FMath::Min (const float a, const float b) {
    return (a < b) ? a : b;
}

constexpr float FMath::Max (const float a, const float b) {
    return (a > b) ? a : b;
}

inline float FMath::ClampFloat (const float val, const float a, const float b) {
    return FMath::Max(a, FMath::Min(b, val));
}

inline int FMath::ClampInt (const int val, const int a, const int b) {
    if (val < a)
        return a;

    if (val > b)
        return b;

    return val;
}

inline int FMath::Nearest2Pow (const unsigned int val) {
    unsigned int result = 2;
    while (result < val) {
        result *= 2;
    }
    return result;
}

inline float FMath::ToRatio (const float val, const float min, const float max) {
    return (val - min) / (max - min);
}

inline float FMath::ClampedRatio (float val, float min, float max) {
    return ClampFloat(ToRatio(val, min, max), 0.0f, 1.0f);
}

inline float FMath::Lerp (const float min, const float max, const float ratio) {
    if (ratio <= 0.0f)
        return min;
    else if (ratio >= 1.0f)
        return max;
    else
        return min + ratio * (max - min);
}

inline float FMath::Fit (const float val, const float oMin, const float oMax, const float nMin, const float nMax) {
    return Lerp(nMin, nMax, ToRatio(val, oMin, oMax));
}

inline float FMath::SinInterpolate (const float min, const float max, const float ratio) {
    float ft = ratio * FMath::PI;
    float f = (1.0f - sinf(ft)) * 0.5f;
    return min * (1.0f - f) + max * f;
}

inline float FMath::CosInterpolate (const float min, const float max, const float ratio) {
    float ft = ratio * FMath::PI;
    float f = (1.0f - cosf(ft)) * 0.5f;
    return min * (1.0f - f) + max * f;
}

inline void FMath::SinCos (const float angle, float &s, float &c) {
    s = sinf(angle);
    c = cosf(angle);
}

} /* namespace sge */

#endif /* __SHLIB_FMath_H_ */
