/*---  FMath.h - Float Math Header  --------------------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Implements simple math functions for floats
 */
#ifndef __SGE_FMATH_H
#define __SGE_FMATH_H

#include <cmath>

#define TO_RADIANS(a) ((a) * FMath::DEG2RAD)
#define TO_DEGREES(a) ((a) * FMath::RAD2DEG)

namespace sge {

class FMath {
public:
    static constexpr float PI = static_cast<float>(M_PI);
    static constexpr float TAU = PI * 2.0f;
    static constexpr float HALF_PI = PI * 0.5f;

    static constexpr float E = static_cast<float>(M_E);
    static constexpr float INFTY = static_cast<float>(INFINITY);

    static constexpr float DEG2RAD = PI / 180.0f;
    static constexpr float RAD2DEG = 180.0f / PI;

    static float Min (const float a, const float b);

    static float Max (const float a, const float b);

    /**
     * Clamp float value within min/max boundaries.
     */
    static float ClampFloat (const float val, const float a, const float b);

    /**
     * Clamp integer value within min/max boundaries.
     */
    static i32 ClampInt (const i32 val, const i32 a, const i32 b);

    /**
     * Return the first power of 2 that is not less than val.
     */
    static u32 Nearest2Pow (const u32 val);

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
    static float Lerp (float ratio, float min, float max);

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

// --------------------------------------------------------------------------

inline float FMath::Min (const float a, const float b) {
    return (a < b) ? a : b;
}

inline float FMath::Max (const float a, const float b) {
    return (a > b) ? a : b;
}

inline float FMath::ClampFloat (const float val, const float a, const float b) {
    return FMath::Max(a, FMath::Min(b, val));
}

inline i32 FMath::ClampInt (const i32 val, const i32 a, const i32 b) {
    if (val < a)
        return a;

    if (val > b)
        return b;

    return val;
}

inline u32 FMath::Nearest2Pow (const u32 val) {
    u32 result = 2;
    while (result < val) {
        result <<= 1;
    }
    return result;
}

inline float FMath::ToRatio (const float val, const float min, const float max) {
    return (val - min) / (max - min);
}

inline float FMath::ClampedRatio (float val, float min, float max) {
    return ClampFloat(ToRatio(val, min, max), 0.0f, 1.0f);
}

inline float FMath::Lerp (const float ratio, const float min, const float max) {
    if (ratio <= 0.0f)
        return min;
    else if (ratio >= 1.0f)
        return max;
    else
        return min + ratio * (max - min);
}

inline float FMath::Fit (const float val, const float oMin, const float oMax, const float nMin, const float nMax) {
    return Lerp(ToRatio(val, oMin, oMax), nMin, nMax);
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

#endif /* __SGE_FMATH_H */
