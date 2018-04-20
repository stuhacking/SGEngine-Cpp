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
#include <cfloat>

class math {
public:
    static constexpr float kPi = static_cast<float>(M_PI);
    static constexpr float kTau = kPi * 2.0f;
    static constexpr float kHalfPi = kPi * 0.5f;

    static constexpr float kE = static_cast<float>(M_E);
    static constexpr float kInfty = static_cast<float>(INFINITY);

public:
    /** Degrees to radians. */
    static constexpr float rad (const float a) { return a * (kPi / 180.0f); }

    /** Radians to degrees. */
    static constexpr float deg (const float a) { return a * (180.0f / kPi); }

    /**
     * @brief Return the smaller of two numbers.
     */
    static constexpr float min (const float a, const float b) {
        return (a < b) ? a : b;
    }

    /**
     * @brief Return the smaller of two numbers.
     */
    static constexpr int min (const int a, const int b) {
        return (a < b) ? a : b;
    }

    /**
     * @brief Return the greater of two numbers.
     */
    static constexpr float max (const float a, const float b) {
        return (a > b) ? a : b;
    }

    /**
     * @brief Return the greater of two numbers.
     */
    static constexpr int max (const int a, const int b) {
        return (a > b) ? a : b;
    }

    /**
     * Clamp float value within min/max boundaries.
     */
    static constexpr float clamp (const float val,
                                  const float a, const float b) {
        return max(a, min(b, val));
    }

    /**
     * Clamp int value within min/max boundaries.
     */
    static constexpr int clamp (const int val, const int a, const int b) {
        return max(a, min(b, val));
    }

    /**
     * Convert a value within a range to a ratio. Resulting value may
     * fall outside the 0.0f .. 1.0f range.
     */
    static constexpr float toRatio (float val, float min, float max) {
        return (val - min) / (max - min);
    }

    /**
     * Convert a value within a range to a ratio strictly clamped to
     * 0.0f .. 1.0f
     */
    static constexpr float clampRatio (float val, float min, float max) {
        return clamp(toRatio(val, min, max), 0.0f, 1.0f);
    }

    /**
     * Return the first power of 2 that is not less than val.
     */
    static int nearest2Pow (int val);

    /**
     * Linear interpolation.
     */
    static float lerp (float ratio, float min, float max);

    /**
     * Reposition a value from an <b>o</b>ld range into a <b>n</b>ew range.
     */
    static float fit (float val, float oMin, float oMax, float nMin, float nMax);

    /**
     * Sine Interpolation.
     */
    static float sinInterpolate (float min, float max, float ratio);

    /**
     * Cosine Interpolation.
     */
    static float cosInterpolate (float min, float max, float ratio);
};

// --------------------------------------------------------------------------

inline int math::nearest2Pow (const int val) {
    verify(val >= 0);

    int result = 2;
    while (result < val) {
        result <<= 1;
    }
    return result;
}

inline float math::lerp (float ratio, float min, float max) {
    if (ratio <= 0.0f)
        return min;
    else if (ratio >= 1.0f)
        return max;
    else
        return min + ratio * (max - min);
}

inline float math::fit (float val, float oMin, float oMax, float nMin,
                        float nMax) {
    return lerp(toRatio(val, oMin, oMax), nMin, nMax);
}

inline float math::sinInterpolate (const float min, const float max,
                                   const float ratio) {
    float f = ratio * math::kPi;
    f = (1.0f - sinf(f)) * 0.5f;

    return min * (1.0f - f) + max * f;
}

inline float math::cosInterpolate (const float min, const float max,
                                   const float ratio) {
    float f = ratio * math::kPi;
    f = (1.0f - cosf(f)) * 0.5f;

    return min * (1.0f - f) + max * f;
}

#include "vector2.h"
#include "vector3.h"
#include "vector4.h"
#include "vector2i.h"
#include "quaternion.h"
#include "matrix2.h"
#include "matrix3.h"
#include "matrix4.h"

#endif /* __SGE_FMATH_H */
